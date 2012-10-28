#ifndef _ARKFUNCS_H_
#define _ARKFUNCS_H_

void add_points(int value);
int get_points();
void set_points(int value);

void sub_lives(int value);
int get_lives();
void set_lives(int value);

void draw_blocks(brick_t (*bricks)[], int amount);
void draw_ball(ball_t *ball);

void move_striker(striker_t *striker, char direction);
void move_ball(ball_t *ball, striker_t *striker, brick_t (*bricks)[], int brick_amount);

void block_hit(ball_t *ball, brick_t (*bricks)[], int brick_amount);
brick_t *has_hit_block(ball_t *ball, brick_t (*bricks)[], int amount);
void block_reflect(ball_t *ball, brick_t *brick);
void bottom_hit(ball_t *ball);
void wall_hit(ball_t *ball);
void striker_hit(ball_t *ball, striker_t *striker);

int no_more_blocks(brick_t (*bricks)[], int amount);
int zero_points();
int no_more_lives();
int is_dead(int set, int value);

void level1(brick_t (*bricks)[24]);

#endif
