#ifndef _LED_H_
#define _LED_H_

#define LED0 PEOUT |= 0x80	//ordered from left to right
#define LED1 PGOUT |= 0x80
#define LED2 PEOUT |= 0x20
#define LED3 PEOUT |= 0x40

#define COL0 PEOUT = 0x0F	//ordered from left to right
#define COL1 PEOUT = 0x17
#define COL2 PEOUT = 0x1B
#define COL3 PEOUT = 0x1D
#define COL4 PEOUT = 0x1E

#define LED_BUFFERSIZE 32
#define LEDCHAR (sizeof(char) * 5)

void led_init();
void led_setstring(char string[]);

void led_clear();
void led_on();
void led_onall();
int led_size(char i);

#endif 
