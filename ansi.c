#include <stdio.h>             	// special encore serial i/o routines

#define ESC 0x1B


void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color      
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);  
}



/* ---------------------------------------------------------------
   --------------------------------------------------------------- */

/* Clearer skærmen og sætter cursoren i (0,0) */
void clearscr()
{
	printf("%c[2J",ESC);
}


/* Sletter indtil cursor-positionen */
void clreol()
{
	printf("%c[K",ESC);
}

/* Flytter cursoren til (x,y) */
void gotoxy(int x, int y)
{
	printf("%c[%d;%dH",ESC,y,x);
}

/* Flytter cursoren i en retning
	
	direction
	---------------------------
	u	-	up
	d	-	down
	l	-	left
	r	-	right
	---------------------------
*/
void move(char direction, int distance)
{
	char course;

	switch( direction )
	{
		case 'u':	course='A';
					break;

		case 'd':	course='B';
					break;

		case 'r':	course='C';
					break;
		
		case 'l':	course='D';
					break;
	}

	printf("%c[%d%c", ESC, distance, course);
}


/* Styrer om tekst skal skrives understreget
	0	-	uden
	1	-	med
*/
void underline(int on)
{
	printf("%c[%dm",ESC, -20*(on-1)+4);
}

/* Styrer aktiveringen af blink
	0	-	uden
	1	-	med
*/
void blink(int on)
{
	printf("%c[%dm",ESC, -20*(on-1)+5);
}

/* Styrer inverteringen af forgrunds- og baggrundsfarven
	0	-	ikke-inverteret
	1	-	inverteret
*/
void reverse(int on)
{
	printf("%c[%dm",ESC, -20*(on-1)+7);
}



/* ---------------------------------------------------------------
   --------------------------------------------------------------- */



/* Gemmer cursorpositionen */
void savecursor()
{
printf("%c[s",ESC);
}

/* Flytter cursoren til den gemte position */
void cursorreturn()
{
printf("%c[u",ESC);
}

/* Beregner l¾ngden af string*/
int stringlen(char string[])
{
	int i=0;
	
	while(string[i]!=0) {i++;}
	return(i);
}

/* Skriver det angivne tegn z gange i en retning

	direction
	--------------------
	u	-	up
	d	-	down
	l	-	left
	r	-	right

*/
void drawdirect(char character, char direction, int distance)
{
	int i=1;
	
	while(i<=distance)
	{
		printf("%c",character);
		move('l',1);
		move(direction,1);
		i++;
	}
}

void del(char direction, int distance)
{
	drawdirect(32,direction,distance);
}



/* ---------------------------------------------------------------
   --------------------------------------------------------------- */



/*
Tegner en ramme med øverste venstre hjørne (x1,y1) og nederste højre hjørne(x2,y2).
Rammen gives en titel, der sættes med title.
	
	titlearea								borderstyle
	-------------------------------------------------------------------------------
	'l'	-	langt titelområde				1	-	dobbelt kant
	's'	-	kort titelområde				2	-	enkelt kant

	blinking
	-------------------------------------------------------------------------------
	0	-	Titlen blinker ikke
	1	-	Titlen blinker

*/

void frame(int x1, int x2, int y1, int y2, char title[], char titlearea, int borderstyle, int blinking)
{
	int xsz, ysz;	// vinduets st¿rrelse i x- henholdsvis y-retning
	char st[8];		// stiltype. Se beskrivelse nedenfor

	/*
	st:  		{	[0]venstre ¿verste hj¿rne,
					[1]h¿jre ¿verste hj¿rne,
					[2]h¿jre nederste hj¿rne,
					[3]venstre nederste hj¿rne,
					[4]horisontal bj¾lke,
					[5]vertikal bj¾lke,
					[6]venstre titelkant,
					[7]h¿jre titelkant
				}
	*/

	switch(borderstyle)
	{
		case 1: /* dobbelt kant */
				st[0]=201; st[1]=187; st[2]=188; st[3]=200; st[4]=205;
				st[5]=186; st[6]=185; st[7]=204;
				break;

		case 2: /* enkelt kant */
				st[0]=218; st[1]=191; st[2]=217; st[3]=192; st[4]=196;
				st[5]=179; st[6]=180; st[7]=195;
				break;
	}
	

	xsz=x2-x1+1;	//
	ysz=y2-y1+1;	// vinduets størrelse beregnes
	
	
	// Den nuv¾rende cursorposition gemmes.
	savecursor();

	// cursoren flyttes til (x1,y1) - herfra tegnes vinduet med uret rundt.

	gotoxy(x1,y1);
	drawdirect(st[0],'r',1);		// venstre ¿verste hj¿rne
	drawdirect(st[6],'r',1);		// venstre titelkant
	drawdirect(219,'r',1);			// tomt f¿rste titelfelt

	// Titlen skrives
	reverse(1);
	blink(blinking);
	printf("%s",title);
	blink(0);
	reverse(0);

	
	
	if (titlearea=='s')
	{
		drawdirect(219,'r',1);			// tomt sidste titelfelt
		drawdirect(st[7],'r',1);		// h¿jre titelkant
		drawdirect(st[4],'r', xsz-stringlen(title)-6); // ¿verste kant tegnes
	}
	else
	{
		drawdirect(219,'r',xsz-stringlen(title)-5);	// ¿verste kant tegnes
		drawdirect(st[7],'r',1);		// h¿jre titelkant
	}

	drawdirect(st[1],'d',1);		// h¿jre ¿verste hj¿rne
	drawdirect(st[5],'d',ysz-2);	// h¿jre kant
	drawdirect(st[2],'l',1);		// h¿jre nederste hj¿rne
	drawdirect(st[4],'l',xsz-2);	// nederste kant
	drawdirect(st[3],'u',1);		// venstre nederste hj¿rne
	drawdirect(st[5],'u',ysz-2);	// venstre kant

	// cursoren afleveres ved den oprindelige position
	cursorreturn();
}
