#include <stdio.h>
#include "ansi.h"
#include "arka_menu.h"
#include "arka_high.h"
#include "arka_help.h"
#include "arka_game.h"
#include "statemachine.h"

int main (int argc, const char * argv[]) 
{	
	
	setstate(1);											// state machine (statemachine.c)
	initscores();											// highscores (arka_high.c)
	
	while(getstate()!=110)
	{
		switch(getstate())
		{
			case 1:											// Menu (arka_menu.c)
				clearscr();
				game_menu();
				break;
			
			case 2:											// Game	(arka_game.c)
				clearscr();
				game_play();
				setstate(1);
				break;
			
			case 3:											// Read Highscore (arka_high.c)
				clearscr();
				showscores();
				setstate(1);
				break;
				
			case 4:											// Set Highscore (arka_high.c)
				//set highscores
				setstate(3);
				break;
			
			case 5:
				showhelp();									// Show helpscreen (arka_help.c)
				setstate(1);
				break;
				
		}

	}
	clearscr();
	return 0;
}
