#include "arkanoid_objects.h"
#include "fixpoint_arr.h"

#define TO8(a) (a << 8)

/*
brick_t strk_a[5] =
{
//pos, status, colour, points
	{ {36,23},{36,23},-1,0,0,5,219 },
	{ {37,23},{37,23},-1,0,0,5,219 },
	{ {38,23},{38,23},-1,0,0,5,219 },
	{ {39,23},{39,23},-1,0,0,5,219 },
	{ {40,23},{40,23},-1,0,0,5,219 }
}
*/



// pos
striker_t strk1 ={{30,23}};


ball_t myball  =
{
{TO8(30),TO8(22)}, TO8(0) 
};
