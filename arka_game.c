#include <stdio.h>
#include "statemachine.h"
#include "ansi.h"
#include "arkanoid_objects.h"
#include "arkanoid_functions.h"
#include "arka_high.h"

#define TO8(a) (a << 8)

/* **************************************************************************
 * The following three functions are not declared in the arka_game.h file
 * since access to these should only be allowed to the other two functions in
 * this file: game_play() and tmr1().
 * The reason these must have access is that tmr1() is using functions in
 * arkanoid_functions.c which need pointers to the striker, ball and bricks.
 * Hence the variables insides the three functions cannot just be declared in
 * game_play().
 *
 * ************************************************************************** */
 
striker_t *get_striker()
{
	static striker_t striker;
	return &striker;
}

ball_t *get_ball()
{
	static ball_t ball;
	return &ball;
}

brick_t *get_bricks()
{
	static brick_t bricks[24];
	return bricks;
}	


// --------------------------------- GAME PLAY ------------------------------

void tmr1()
{
// Moves the ball

	move_ball(get_ball(), get_striker(), (brick_t (*)[24])get_bricks(), 24);
	gotoxy(1,1);
}

void game_play()
{

// ********************************* INITIATION *****************************

	brick_t (*bricks)[24];												// Pointers to bricks,
	striker_t *striker;													// striker and ball
	ball_t *ball;														// are created
	char kin;
	
	bricks = (brick_t (*)[24])get_bricks();								// The pointers are given
	striker = get_striker();											// the appropriate adresses
	ball = get_ball();													//
	
	
	frame(1, 80, 1, 24, "Arkanoid!!! ", 'l', 1, 0);						// Window is drawn
	
	set_points(150);													// Points set to start value
	set_lives(3);														// Lives set to start value
	
	level1(bricks);														// Bricks initiation to level 1 configuration
	draw_blocks(bricks, 24);											// Bricks are drawn.
	
	
	while ( (no_more_lives()==0) && (no_more_blocks(bricks, 24)==0)
			&& (zero_points()==0) && (kin!='q') )
	{	
	
	// The following blocks of code reposition the striker and ball
	// when the player has lost a life.
	
		is_dead(1,0);													// Makes the player "alive"	
		
		striker->pos.x = 30;											// Striker moved to given coordinates
		striker->pos.y = 23;											//
	
		ball->pos.x = TO8(32);											// Ball initiation: position and angle
		ball->pos.y = TO8(22);											//
		ball->angle = TO8(340);											//
	
		gotoxy(2,23);													// Clears the line of the striker in
		del('r',78);													// the game window
		
		draw_striker(striker);											// Striker is (re)drawn
		draw_ball(ball);												// Ball is drawn
		gotoxy(1,1);													// cursor moved to corner
		
		while( (kin=getchar()) !='d' ){}								// await launch
		
		while( ((kin=getchar()) !='q') && (is_dead(0,0)==0)
				&& (zero_points()==0)
				&& (no_more_blocks(bricks, 24)==0))						// if 'q' is pressed, exit loop/game
		{

			if (kin =='a')												// 'a' moves striker to the left
				move_striker(striker, 'l');
				gotoxy(1,1);
		
			if (kin == 's')												// 's' moves striker to the right
			{
				move_striker(striker, 'r');
				gotoxy(1,1);
			}
		
			if (kin == 'f')												// temporarily emulates timer1
			{
				tmr1();
			}
		}
	
	}
	
	putscore(get_points());
	
}
