#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include "STD_types.h"
#include "BIT_math.h"
#include "Timer_int.h"
#include "DIO_int.h"
#include "GIE_int.h"

#define LED1_Pin 1
#define LED2_Pin 2
#define LED3_Pin 3
#define LEDS_PORT PORTD

 int led1_flag = 0;
 int led2_flag = 0;
 int led3_flag = 0;

ISR(TIMER0_OVF_vect) //Interrupt
{
	static int counter_LED1 = 0, counter_LED2 = 0,counter_LED3 = 0;
	counter_LED1++,counter_LED2++,counter_LED3++;
	if(counter_LED1 == 62)// LED1 toggle every 1 sec
	{
		led1_flag = 1;
		counter_LED1 = 0;
	}
	if (counter_LED2 == 62*2) // LED2 toggle every 2 sec
	{
		led2_flag = 1;
		counter_LED2 = 0;
	}
	if (counter_LED3 == 62*3) // LED3 toggle every 3 sec
	{
		led3_flag = 1;
		counter_LED3 = 0;
	}
	
	//TIMER0_void_SetTimerReg(247);
}

void Leds(void)
{
	
	if (led1_flag == 1)
	{
				TOG_BIT(LEDS_PORT,LED1_Pin); 
				led1_flag = 0;
	}
	
	else if (led2_flag == 1)
	{
				TOG_BIT(LEDS_PORT,LED2_Pin);
				led2_flag = 0;
	}
	
	else if (led3_flag == 1)
	{
		TOG_BIT(LEDS_PORT,LED3_Pin);
		led3_flag = 0;
	}
}


int main(void)
{
   DIO_voidSetPinDir(DIO_U8_PORTD,DIO_U8_PIN1,DIO_U8_OUTPUT);	
   DIO_voidSetPinDir(DIO_U8_PORTD,DIO_U8_PIN2,DIO_U8_OUTPUT);
   DIO_voidSetPinDir(DIO_U8_PORTD,DIO_U8_PIN3,DIO_U8_OUTPUT);	
   
   TIMER0_Init();
   TIMER0_SetTCNT(247);
   TIMER0_EnableOVFInt(); // PIF Interrupt
   
   
   GIE_voidEnable(); // GIE Interrupt
    while (1) 
    {
		Leds();
    }
}

