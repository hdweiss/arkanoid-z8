#include <eZ8.h>
#include <sio.h>
#include "led.h"

#pragma interrupt
void button_pressed()
{
	led_setstring("hurray");
}

void button_init()
{
	led_init();

	IRQPS |= 0x80;			//set to port D
	
	IRQ1ENL |= 0x80;		//enable interrupt for button



	SET_VECTOR(P7AD, button_pressed);
	EI();
}

void main()
{
//	button_init();
	led_init();	

	while(1){
	if((PFIN & 0x40) == 0)
		{led_setstring(":)");
		while(1){
		if((PFIN & 0x80) == 0) break;}}
	else
		led_setstring(":(");
	}

}
