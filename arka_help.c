/*
 *  arka_help.c
 *
 */

#include "stdio.h"
#include "ansi.h"

#define MENUOFFSET 15

void showhelp()
{
    int y = 4;

	clearscr();
	frame(1, 80, 1, 24, "Arkanoid!!!", 'l', 2, 0);
	gotoxy(35, y);
	printf("Helpscreen:");

	y++;
	gotoxy(MENUOFFSET, ++y);
	printf("Menu:");
	gotoxy(MENUOFFSET, ++y);
	printf("Navigate the menus with a(up) and s(down)");
	gotoxy(MENUOFFSET, ++y);
	printf("Press d to select the marked menu item");

	y++;
	gotoxy(MENUOFFSET, ++y);
	printf("In Game:");
	gotoxy(MENUOFFSET, ++y);
	printf("Move the striker with a(left) and s(right)");
	gotoxy(MENUOFFSET, ++y);
	printf("To exit the game press q");

	y++;
	gotoxy(MENUOFFSET, ++y);
	printf("\"Start a new game\" starts a new game on level one");
	gotoxy(MENUOFFSET, ++y);
	printf("\"Hall of fame\" lists the highscores of previous games");
	gotoxy(MENUOFFSET, ++y);
	printf("\"Introduction\" displays this message");
	gotoxy(MENUOFFSET, ++y);
	printf("\"Quit\" quits the game");

	gotoxy(30, 20);
	printf("Press d to continue");

while(getchar()!='d'){}

}
