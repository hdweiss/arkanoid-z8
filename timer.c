#include <eZ8.h>
#include <sio.h>


#pragma interrupt
void timer1int()
{
	
	printf("bla\n");
    //fill in the function to be called
}


void timer1_setup(int difficulty)
{
	T1CTL = 0x01;	//Disable Timer1 and set it to continous mode
	T1CTL |= 0x38;	//Set the prescale value
	
	T1H = 0x00;		//...
	T1L = 0x01;		//reset timer

	

	if(difficulty > 0xFF)	//set timer reload value
	{
	    T1RH = difficulty - 0xFF;
	    T1RL = 0xFF;
	}
	else
	{
	    T1RH = 0x00;
	    T1RL = difficulty;
	} 

	

	IRQ0ENH |= 0x40; 	//enable Timer1 interrupt, and set nominal priority
	IRQ0ENL &= 0xBF;

	SET_VECTOR(TIMER1, timer1int);

	T1CTL |= 0x80;		//enable Timer1
	EI();				//enable interrupts
}


void timer1_toggle(char i)		//toggle timer if 0 off, else on
{
	if(i)
		T1CTL &= ~0xF0;
	else
		T1CTL |= 0xF0;
}


