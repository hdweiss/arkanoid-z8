#include <stdio.h>
#include "ansi.h"
// statemahine.h is only included because of last function in this file. It is normally not supposed to be there.
#include "statemachine.h"

#define MENU_X 30
#define MENU_Y 5
#define MAX_ITEMS 8
#define TITLE_SIZE 32

typedef struct menu_s menu_t;

/*
	a menu contain a title, a number of items and an integer tag.
	For each item there is a pointer to a related function.
	The related function must always have one argument:
	(menu_t *). which is intended to tell the function what menu
	called the function.
	Besides of this, a menu has two integers telling the amount of items
	and the index for the currently "chosen" item.
*/

struct menu_s {	char title[TITLE_SIZE];
				char *items[MAX_ITEMS];
				int states[MAX_ITEMS];
				int elements;
				int current;
			  };


// sets up an empty menu.
void menu_init(menu_t *menu, char title[TITLE_SIZE])
{
	int i=0;
	
	while(title[i]!=0)						//copying the title
	{
		(*menu).title[i] = title[i];
		i++;
	}
	
	(*menu).title[i]=0;						//complete title string with null-character
	
	(*menu).elements = 0;					//sets the elements integer to zero since no items in menu.
	(*menu).current = 0;					// ....
}



/*
adds an item to the menu.
*/
void menu_add(menu_t *menu, char text[], int state)
{
	if( (*menu).elements<8 )
	{
		(*menu).elements++;
		
		(*menu).items[(*menu).elements-1]=text;
		(*menu).states[(*menu).elements-1]=state;
	}
}


/*
reassings the title and function of the item on the given index.
*/
void menu_reassign(menu_t *menu, int index, char text[], int state)
{
	(*menu).items[index]=text;
	(*menu).states[index]=state;
}

/*
removes the item on the given index from the menu.
*/
void menu_remove(menu_t *menu, int index)
{
	int i=1;
	
	while(index+i < (*menu).elements)							//items are moved up on the list
	{
		(*menu).items[index+i-1]=(*menu).items[index+i];
		(*menu).states[index+i-1]=(*menu).states[index+i];
		i++;
	}
	
	(*menu).elements--;
	
	if ((*menu).current>(*menu).elements-1)
		(*menu).current = (*menu).elements-1;
	
}

/*
Creates the graphical representation of the menu.
*/

void menu_show(menu_t *menu)
{
	int i;
	
	clearscr();
	
	frame(1,80, 1,24, (*menu).title, 'l', 2, 0);	// window is drawn
	
	gotoxy(MENU_X, MENU_Y+2*(*menu).current);		// cursor is moved to the currently chose item
	drawdirect(219,'r',1);							// graphical cursor is drawn
	gotoxy(MENU_X+2, MENU_Y);						// moves the terminal cursor to the right
	
	for (i=0; i < (*menu).elements; i++)			// each item's title is written.
	{
		gotoxy(MENU_X+2, MENU_Y+2*i);
		printf( "%s", (*menu).items[i]);
	}
	
	gotoxy(1,1);
}


/*
The next menu item is chosen and the screen is updated.
*/
void menu_next(menu_t *menu)
{
	gotoxy(MENU_X, MENU_Y+2*(*menu).current);
	del('r',1);
	
	if ( (*menu).current == (*menu).elements-1 )
	{
		(*menu).current = 0;
	}
	else
	{
		(*menu).current++;
	}
	
	gotoxy(MENU_X, MENU_Y+2*(*menu).current);
	drawdirect(219,'r',1);
	gotoxy(1,1);
}


/*
The previous menu item is chosen and the screen is updated.
*/
void menu_prev(menu_t *menu)
{
	gotoxy(MENU_X, MENU_Y+2*(*menu).current);
	del('r',1);
	
	if ( (*menu).current == 0 )
	{
		(*menu).current = (*menu).elements-1;
	}
	else
	{
		(*menu).current--;
	}
	
	gotoxy(MENU_X, MENU_Y+2*(*menu).current);
	drawdirect(219,'r',1);
	gotoxy(1,1);
}

/*
The state is set to the currently chosen.

Ought not to be in this file.
*/
void menu_select(menu_t *menu)
{
	printf("setting state to %d", (*menu).states[(*menu).current]);
	setstate( (*menu).states[(*menu).current]);
}
