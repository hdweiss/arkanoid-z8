/*
 *  menus.h
 *
 *
 */

#ifndef _MENUS_H_
#define _MENUS_H_
#define MAX_ITEMS 8
#define TITLE_SIZE 32

typedef struct menu_s menu_t;

struct menu_s {	char title[TITLE_SIZE];
				char *items[MAX_ITEMS];
				int states[MAX_ITEMS];
				int elements;
				int current;
			  };

void menu_init(menu_t *menu, char title[TITLE_SIZE]);
void menu_add(menu_t *menu, char text[], int state);
void menu_reassign(menu_t *menu, int index, char text[], int state);
void menu_show(menu_t *menu);
void menu_next(menu_t *menu);
void menu_prev(menu_t *menu);
void menu_select(menu_t *menu);

#endif
