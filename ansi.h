#ifndef _ANSI_H_
#define _ANSI_H_

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);
void resetbgcolor();
void clearscr();
void clreol();
void gotoxy(int x, int y);
void move(char direction, int distance);
void underline(int on);
void blink(int on);
void reverse(int on);
void savecursor();
void cursorreturn();
int stringlen(char string[]);
void drawdirect(char character, char direction, int distance);
void del(char direction, int distance);
void frame(int x1, int x2, int y1, int y2, char title[], char titlearea, int borderstyle, int blinking);

#endif
