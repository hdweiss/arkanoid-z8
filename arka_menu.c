/*
 *	This file provides the menu for the Arkanoid game as well as the state machine function.
 */

#include <stdio.h>
#include "menus.h"
#include "statemachine.h"


void game_menu()
{
	char c_inp;
	
	menu_t arkmenu;
	menu_init(&arkmenu, "Arkanoid!!! v0.5");
	
	menu_add(&arkmenu, "New game", 2);
	menu_add(&arkmenu, "Hall of Fame", 3);
	menu_add(&arkmenu, "Instructions", 5);
	menu_add(&arkmenu, "Quit", 110);
	
	menu_show(&arkmenu);
	
	
	
	while(getstate()==1)
	{
		c_inp = getchar();
	
		switch(c_inp)
		{
			case 's':
				menu_next(&arkmenu);
				break;
				
			case 'a':
				menu_prev(&arkmenu);
				break;
	
			case 'd':
				menu_select(&arkmenu);
				break;
		}
	}
	
	
}
