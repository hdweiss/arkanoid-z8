#include <stdio.h>
#include "ansi.h"
#include "statemachine.h"
#include "fixpoint_arr.h"
#include "arkanoid_objects.h"
#include "arkanoid_functions.h"

#define STRKCHAR 220
#define BRCKCHAR 219
#define BALLCHAR 'o'
#define BRCKLEN 8
#define BRCKHGH 2

#define TO8(a) (a << 8)   //temporary

/* ******************************* POINTS SYSTEM ******************************* */
/*
 * The points system is made up of four functions. The points_sys is the main
 * function which has the static variable int points. Hence the variable is set using
 * this particular function. However three other functions have been made to
 * interface with the programmer. add_points, get_points and set_points.
 */
 
int points_sys(int set, int value)
{
	static int points;
	
	if (set==1)
		points=value;
	else if (set==2)
		points+=value;
	
	return points;
}

void add_points(int value)
{
	points_sys(2,value);
}

int get_points()
{
	return points_sys(0,0);
}

void set_points(int value)
{
	points_sys(1,value);
}

/* ******************************* LIVES SYSTEM ******************************* */
/*
 * This system works much the same way as the points system. The programmer should
 * use the functions sub_lives, get_lives and set_lives to alter the static variable
 * lives in lives_sys.
*/

int lives_sys(int set, int value)
{
	static int lives;
	
	if (set==1)
		lives=value;
	else if (set==2)
		lives-=value;
	
	return lives;
}

void sub_lives(int value)
{
	lives_sys(2,value);
}

int get_lives()
{
	return lives_sys(0,0);
}

void set_lives(int value)
{
	lives_sys(1,value);
}

/* ******************************* INITIATION AND DRAWING ********************* */

void draw_blocks(brick_t (*bricks)[], int amount)
{
/* Draws all blocks in the given array on the screen. amounts must be equal to the
 * amount of blocks in the array.
 */
	int i, j;
	
		for(i=0; i < amount; i++)
		{
			fgcolor( (*bricks)[i].colour );
		
			for(j=0; j<BRCKHGH; j++)
			{
			gotoxy((*bricks)[i].pos.x , (*bricks)[i].pos.y+j);
			drawdirect(BRCKCHAR, 'r', BRCKLEN);
			}
		}
	
	fgcolor(0);					//changes the foreground colour back to black
	
}



void draw_striker(striker_t *striker)
{
/* This function draws the striker, provided a pointer to it */

	gotoxy( (*striker).pos.x , (*striker).pos.y );
	drawdirect( STRKCHAR, 'r', 5 );
}



void draw_ball(ball_t *ball)
{
/* Draws the ball given by a pointer in the function argument.
 *
 * It must be remembered, that the ball's position is stored in
 * 24.8 format, why temporary variables are used to find its
 * 32.0 position (the screen coordinates are represented by
 * whole numbers).
 *
 */
 
	long tmp_x, tmp_y;
	
	tmp_x = fix_round(ball->pos.x,8,0);
	tmp_y = fix_round(ball->pos.y,8,0);

	gotoxy( tmp_x , tmp_y );
	drawdirect(BALLCHAR,'r',1);
}

/* ******************************* MOTION SYSTEM ****************************** */

void move_striker(striker_t *striker, char direction)
{
/* Moves the striker one position in the given direction. The graphical representation
 * of the striker is also updated. This is carried out by filling one pixel coordinate
 * in the move direction and emptying the tailing pixel.
 *
 */
	
	if (direction=='l' && (*striker).pos.x>2 )				// striker is moved to the left
	{
	
		gotoxy( (*striker).pos.x-1 , (*striker).pos.y);
		drawdirect(STRKCHAR, 'l', 1);
		gotoxy( (*striker).pos.x + 4, (*striker).pos.y);
		del('l',1);
		
		(*striker).pos.x -=1;								// position updated
	}
	else if (direction=='r' && (*striker).pos.x<75)			// striker is moved to the right
	{
		
		gotoxy( (*striker).pos.x , (*striker).pos.y);
		del('r',1);
		gotoxy( (*striker).pos.x + 5, (*striker).pos.y);
		drawdirect(STRKCHAR, 'r', 1);
		
		(*striker).pos.x +=1;								// position updated
	}

}

void move_ball(ball_t *ball, striker_t *striker, brick_t (*bricks)[], int brick_amount)
{
/* The purpose of this function is to carry out all the functions involved in the
 * moving of the ball, i.e check if ball hits a wall, bottom, brick or the striker,
 * in that case reflect the ball, eventually destroy block and add points to score
 * and of course update the graphical representation of the block.
 * 
 * Again it shall be remembered, that the ball's position is stored in 24.8 format.
 */
  
	long tmp_x, tmp_y;
	
	if (is_dead(0,0)==0)
	{
	
		//removes the ball from the screen
		gotoxy( fix_round(ball->pos.x,8,0) , fix_round(ball->pos.y,8,0) );
		del('r',1);
	
		// updates the ball position
		tmp_x = cosinus(ball->angle,8,8);
		tmp_y = sinus(ball->angle,8,8);
	
		ball->pos.x += tmp_x;
		ball->pos.y += tmp_y;
	
		// checks if ball hits anything
		bottom_hit(ball);
	
		// Only carry out the rest of this function if player isn't dead
		if (is_dead(0,0)==0)
		{
			wall_hit(ball);
			striker_hit(ball, striker);
			block_hit(ball, bricks, brick_amount);
			draw_ball(ball);
		
			//Subtracts one point from the score
			add_points(-1);
		}
	}
}


/* ******************************* REFLECTION SYSTEM ******************************* */

void block_hit(ball_t *ball, brick_t (*bricks)[], int brick_amount)
{

/* Checks if the ball has hit a block and in that case updates the ball's direction,
 * adss eventual points and destroy block.
 *
 */
 
	brick_t *brick;
	int i=0;
	
	//checks if a block is hit.
	brick = has_hit_block(ball, bricks, brick_amount);
	
	//if a block is hit
	if ( brick != NULL)
	{
		// ball is reflected on the block it has hit.
		block_reflect(ball, brick);
		
		// the ball loses 1 in status
		(brick->status)--;
		
		// if status has become 0, the block is destroyed. Status hereby provides
		// the oppertuniy to create blocks, that must be hit several times before
		// breaking and releasing points.
		
		if (brick->status == 0)
		{
		
			//delete block from screen
			while(i<BRCKHGH)
			{
				gotoxy(brick->pos.x, brick->pos.y+i);
				drawdirect(' ', 'r', BRCKLEN);
				i++;
			}
			
			//add the points to the user's total score
			add_points(brick->points);
			if (no_more_blocks(bricks,24))
				add_points(2500);
			
		}
		
	}
}


brick_t *has_hit_block(ball_t *ball, brick_t (*bricks)[], int amount)
{
/* Investigates if a block has been hit by the ball. If so, the function will return
 * a pointer to the implicated brick.
 *
 * Remember the ball's position is stored in 24.8 format.
 */
 
    int i;
	long tmp_x, tmp_y;
    
	// finds the pixel the ball's within
	tmp_x = fix_round(ball->pos.x,8,0);
	tmp_y = fix_round(ball->pos.y,8,0);
	
	//checks if a block in the given array occupies that screen pixel
    for(i=0; i < amount; i++)
    {
		//only check if the block has not already been destroyed
		if ((*bricks)[i].status!=0)
		{
			//checks if the pixel is occupied and in that case return a pointer to the block
			if (  (tmp_x >= (*bricks)[i].pos.x) && (tmp_x < (*bricks)[i].pos.x + BRCKLEN)
			   && (tmp_y >= (*bricks)[i].pos.y) && (tmp_y < (*bricks)[i].pos.y + BRCKHGH) ) 
			{
			return &(*bricks)[i];
			}
		}
	}
	
	//if no block was hit, return NULL
	return NULL;
}


void block_reflect(ball_t *ball, brick_t *brick)
{
/* Reflects the ball on the block it has hit.
 * First it is investigated what side of the brick that been hit: bottom/top or the sides
 * and dependent on that result, the ball is reflected in a direction.
 *
 * Remember both angle and position of the ball is stored in 24.8 format.
 */
 
	long old_x, old_y;
	long val[4];
	
	int i, smallest;
	
	old_x = cosinus(ball->angle,8,8);			// The vector for the incoming angle is saved
	old_y = sinus(ball->angle,8,8);				//
	
	// The distance from the ball to each side of the block is calculated and divided by the
	// coordinate of the directional vector of the ball. The result yielding the smallest value
	// indicates the side hit by the ball.
	
	// left side
	val[0] = fix_div( (ball->pos.x - fix_round(brick->pos.x,0,8)), old_x, 8,8,8);
	// right side
	val[1] = fix_div( (ball->pos.x - fix_round(brick->pos.x + BRCKLEN,0,8)), old_x, 8,8,8);
	// top
	val[2] = fix_div( (ball->pos.y - fix_round(brick->pos.y,0,8)), old_y, 8,8,8);
	// bottom
	val[3] = fix_div( (ball->pos.y - fix_round(brick->pos.y + BRCKHGH,0,8)), old_y, 8,8,8);
	
	//the smallest result is found
	smallest=0;
	
	for(i=0; i<4; i++)
	{
		if( val[smallest]>val[i] )
			smallest = i;
	}
	
	// depending on what side was hit, the ball is reflected in a given angle.
	
	// left or right side
	if (i<3)
		ball->angle=TO8(256)-(ball->angle);
	// top or bottom
	else if(i>2)
		ball->angle=TO8(512)-(ball->angle);
	
	
	ball->pos.x -= old_x;		//ball set one move back
	ball->pos.y -= old_y;		//
	
	// The ball's angle is expressed by the smallest positive value (example: 511 instead of -1 or 1023)
	ball->angle = sp_angle(ball->angle,8,8);
}

void bottom_hit(ball_t *ball)
{
/* If the ball hits the bottom a life is subtracted from the player and the status is set to dead.
 * The
 */
	
	if (fix_round(ball->pos.y,8,0) > 23)
	{
		sub_lives(1);
		is_dead(1,1);
	}
}

void wall_hit(ball_t *ball)
{
/* If a wall is hit by the ball, the ball is reflected.
 * Remember the ball's angle and position are in 24.8 format.
 */
 
	long old_x, old_y;
	
	old_x = cosinus(ball->angle,8,8);			// The vector for the incoming angle is saved
	old_y = sinus(ball->angle,8,8);				//
	
	int wallhit = 0;
	
    if( fix_round(ball->pos.y,8,0) < 2)			//ball hits ceiling
    {
		wallhit=1;
		ball->angle = TO8(512)-(ball->angle);	//direction updated
	}
	if( fix_round(ball->pos.x,8,0) < 2)			//ball hits left wall
	{
		wallhit=1;
		ball->angle = TO8(256) - ball->angle;	//direction updated
	}
	if( fix_round(ball->pos.x,8,0) > 79)		//ball hits right wall
	{
		wallhit=1;
		ball->angle = TO8(256) - ball->angle;	//direction updated
	}
	
	if (wallhit==1)
	{
		ball->pos.x -= old_x;		//ball set one move back
		ball->pos.y -= old_y;		//
	}
	
	// The ball's angle is expressed by the smallest positive value (example: 511 instead of -1 or 1023)
	ball->angle = sp_angle(ball->angle,8,8);
}


void striker_hit(ball_t *ball, striker_t *striker)
{
    long tmp_x, tmp_y, hit, old_x, old_y;
	
	ball->angle = sp_angle(ball->angle,8,8);
	
	tmp_x = fix_round(ball->pos.x,8,0);
	tmp_y = fix_round(ball->pos.y,8,0);
	
	if ( (tmp_y == striker->pos.y) && (0 <= tmp_x - striker->pos.x)
			&& (tmp_x < striker->pos.x+5) )
	{
	
		old_x = cosinus(ball->angle,8,8);			// The vector for the incoming angle is saved
		old_y = sinus(ball->angle,8,8);				//
	
		ball->angle = sp_angle(ball->angle,8,8);
	
		hit = tmp_x - striker->pos.x;
		
		
		switch(hit)									// reflecsion
		{
			case 0:
				if(ball->angle < TO8(128))
					ball->angle = TO8(384) + fix_div( TO8(384) - ball->angle , 3, 8, 0, 8);
				else
					ball->angle = TO8(384) + fix_mps( TO8(384) - ball->angle , 3, 8, 0, 8);
				break;
        
			case 1:
				if(ball->angle < TO8(128))
					ball->angle = TO8(384) + fix_div( TO8(384) - ball->angle , 3>>1, 8, 1, 8);
				else
					ball->angle = TO8(384) + fix_mps( TO8(384) - ball->angle , 3>>1, 8, 1, 8);
				break;
		
			case 2:
				ball->angle = TO8(512) - ball->angle;
				break;
		
			case 3:
				if(ball->angle > TO8(128))
					ball->angle = TO8(384) + fix_div( TO8(384) - ball->angle , 3>>1, 8, 1, 8);
				else
					ball->angle = TO8(384) + fix_mps( TO8(384) - ball->angle , 3>>1, 8, 1, 8);
				break;
		
			case 4:
				if(ball->angle > TO8(128))
					ball->angle = TO8(384) + fix_div( TO8(384) - ball->angle , 3, 8, 0, 8);
				else
					ball->angle = TO8(384) + fix_mps( TO8(384) - ball->angle , 3, 8, 0, 8);
				break;
		}
	
		ball->angle = sp_angle(ball->angle,8,8);
	
		ball->pos.x -= old_x;		//ball set one move back
		ball->pos.y -= old_y;		//
	
    }

}

/* ******************************* GAME CONTROL ******************************** */
int no_more_blocks(brick_t (*bricks)[], int amount)
{
/* Checks if all destructable blocks have been bestroyed.
 * If a block's status is less than 0 it is indestructable.
 * The function returns 1 for true and 0 for false.
 */
 
	int i;
	
	for(i=0; i<amount; i++)
	{
		if ( (*bricks)[i].status > 0)
			return 0;
	}
	
	return 1;
}

int zero_points()
{
/* Checks if the player has no points. This is used to make the game over in the same
 * way as if the player had no more lives. Returns 1 for true and 0 for false. 
 */

	if (get_points()<1)
		return 1;
	
	return 0;
}

int no_more_lives()
{
/* Checks if the player has no more lives. Returns 1 for true and 0 for false. 
 *
 */

	if (get_lives()<1)
		return 1;
	
	return 0;
}

int is_dead(int set, int value)
{
/* The role of this function is to set and tell the player's current status, i.e has
 * he just died? The function DOES NOT tell anything about remaining lives hence is
 * not part of the lives system.
 */
 
	static int dead;
	
	if (set==1)
		dead = value;
	
	return dead;
	
}


/* ******************************* LEVELS SYSTEM ******************************* */
void level1(brick_t (*bricks)[24])
{
/* initiates the blocks' properties to level1 configuration. The function
 * must be provided a pointer to the array holding the blocks.
 */
	int i, j;

	for(j=0; j<4; j++)
	{
		for(i=0; i<6; i++)
		{
			(*bricks)[j*6+i].pos.y=5+j*BRCKHGH;
			(*bricks)[j*6+i].pos.x=16+i*BRCKLEN;
			(*bricks)[j*6+i].status=1;
			(*bricks)[j*6+i].colour=1+((i+j)%2);
			(*bricks)[j*6+i].points=75;
		}
	}

}
