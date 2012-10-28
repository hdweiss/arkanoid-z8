/*
 *  arka_high.c
 *
 */
 
#include <stdio.h>
#include "ansi.h"

#define BEGINX 20
#define BEGINY 7

int highscores(int putscore, int value, int index)
{
	static int scores[6];						// index 0 is used as last-game score
												// index 5 is highes score
	int i=0;
	
	if(putscore==1)
	{
		
		while(value >= scores[i+1])
		{
			scores[i]=scores[i+1];
			i++;
		}
		
		scores[i]=value;
		scores[0]=value;
		
		return scores[i];
	}
	else if(putscore==2)
	{
		scores[index]=value;
	}
	
	return scores[index];
}


char *highscorenames(int putname, char *name, int index)
{
	static char *names[6];						// index 0 is unused
												// index 5 is highes score
	int i=0;
	
	if (putname==1)
	{
		while(i<index)
		{
			names[i]=names[i+1];
			i++;
		}
		
		names[i]=name;
		
	}
	else if(putname==2)
	{
		names[index]=name;
	}
		
	
	return names[index];
}

void initscores()
{
	int i;

	for(i=0; i<=5; i++)
	{
		highscores(2, 0, i);
		highscorenames(2,"no name",i);
	}
	
}

void showscores()
{
	int i;
	
	clearscr();
	frame(1, 80, 1, 24, "Arkanoid!!!", 'l', 2, 0);
	
	gotoxy(BEGINX, BEGINY-3);
	printf("HIGHSCORES - THE HALL OF FAME - HIGHSCORES");
	
	for(i=5; i>=1; i--)
	{
		gotoxy(BEGINX, BEGINY+(5-i)*2);
		printf("%6d    %s", highscores(0, 0, i), highscorenames(0,0,i));
	}
	
	gotoxy(30, BEGINY+5*2+5);
	printf("Press d to continue");
	
	while(getchar()!='d')
	{}
	
}

void putscore(int score)
{
	int index, i;
	char kin;
	char name[30];
	
	clearscr();
	frame(1, 80, 1, 24, "Arkanoid!!!", 'l', 2, 0);
	
	index = highscores(1, score, 0);
	
	if (index > 0)
	{
		gotoxy(BEGINX, BEGINY-3);
		printf("CONGRATULATIONS! You made it to the Hall of Fame!");
		gotoxy(BEGINX, BEGINY-2);
		printf("You got a total of %d points!", score);
		gotoxy(BEGINX, BEGINY);
		printf("Type your name and end with '0':");
		
		gotoxy(BEGINX, BEGINY+1);
		
		i = 0;
		while((i < 29) && ((kin=getchar())!='0'))
		{
			name[i++]=kin;
			printf("%c",kin);
		}
		
		name[i]='\0';
		
		//highscorenames(1, &name, index);
	}
	
}