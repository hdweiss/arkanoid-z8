#include <sio.h>
#include <eZ8.h>
#include <string.h>
#include "led.h"
#include "charset.h"

char *videobuffer[LED_BUFFERSIZE + 4][5];	//4 extra letters for scrolling


#pragma interrupt
void drawtimer()
{
	static char i = 0, counter = 0;
	static int index = 0;
	char j = 0;
	
	if(led_size(0) > 20)		//if string is longer then 4 letters
		counter++;

	if(counter > 100)			//scrolling delay
	{
		counter = 0;
		(index >= led_size(0)) ? index = 0: index++; 		//index check - when to wrap around	
	}

	switch(i)		//set active collum
	{
		case 0: COL0; break;
		case 1: COL1; break;
		case 2: COL2; break;
		case 3: COL3; break;
		case 4: COL4; break;
	}
	
	for(j = 0; j < 4; j++)
	{

		PGOUT = *(videobuffer[j][i + index]);		//if *(videobuffer[j + index][i]) is chosen instead it scrolls one LED at a time
													//(index checks must be divided by 5)
		
		switch(j)								//choose active LED which to draw on
		{
			case 0: LED0; break;
			case 1: LED1; break;
			case 2: LED2; break;
			case 3: LED3; break;
		}
	}	
	
	(i > 4) ? i=0: i++;		//collum counter
}

void led_setstring(char string[])			//load string into 
{
	char i, j, k;

	for(i = 0; i < strlen(string) && i < LED_BUFFERSIZE; i++)			//initialize videobuffer with the correct charset value
		for(j = 0; j < 5; j++)
			videobuffer[i][j] = &character_data[string[i] - 32][j];

	
   	for(k = i; k < i+4; k++)					//set the 4 last letters to zero (makes scrolling easier)
		for(j = 0; j < 5; j++)
			videobuffer[k][j] = &character_data[0][j];

	if(strlen(string) < LED_BUFFERSIZE)
		led_size(strlen(string));				//remember size of string
		else led_size(LED_BUFFERSIZE);
}

int led_size(char i)			//global var hack to remember the size of the string in videobuffer
{
    static int size = 0;

    if(i != 0)
		size = (i * LEDCHAR);
    return size;
}

void led_init()
{
	PEADDR = 0x02;		//set alternative function (port E)
	PECTL = 0x00;
	PEADDR = 0x01;		//set datadirection to output (port E)
	PECTL = 0x00;

	PGADDR = 0x02;		//set alternative function (port G)
	PGCTL = 0x00;
	PGADDR = 0x01;		//set datadirection to output (port G)
	PGCTL = 0x00;

	T0CTL = 0x01;		//Disable Timer0 and set it to continous mode
	T0CTL |= 0x38;		//Set the prescale value
	
	T0H = 0x00;		
	T0L = 0x01;			//reset timer

	T0RH = 0x00;
//	T0RH = 0x02;
	T0RL = 0xD0;		//set reload value (0.5 ms)

	IRQ0ENH &= 0xDF;
	IRQ0ENL |= 0x20;	 //enable Timer0 interrupt, and set low priority

	T0CTL |= 0x80;		//enable Timer0
	EI();				//enable interrupts

	SET_VECTOR(TIMER0, drawtimer);		//set timer interrupt function

	led_clear();		//clear the LEDs
	led_onall();	
}



void led_clear()	//clear all LEDs
{
	PEOUT = 0x1F;
	PGOUT = 0x00;
}

void led_on()		//turns all LEDs on
{
	PEOUT = 0x00; 
	PGOUT = 0x7F;
}

void led_onall()	//draws the active registercontent on all LEDs
{
	LED0;
	LED1;
	LED2;
	LED3;
}


