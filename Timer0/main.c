


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include<avr/delay.h>

#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "Timer0_interface.h"
void TIMER_voidToggletheLED (void);
void LedToggle(void);
void PWM_usingCTC (void);
void main (void)
{

	/******CTC mode to toggle led every 1 sec*****/
	/*u8 Local_u8ErrorCode=NULL;
	DIO_voidSetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	TIMERO_voidTimer0Init();
	Local_u8ErrorCode= TIMER0_voidSetCallBack(TIMER_voidToggletheLED);
	GIE_voidEnable();
	while(1)
	{

	}
	 */

	/*USing CTC mode to generate PWM signal*/


	/*u8 Local_u8ErrorCode=NULL;
	DIO_voidSetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_OUTPUT);
	TIMERO_voidTimer0Init();
	TIMER0_voidSetCMPMatchVal(250);
	Local_u8ErrorCode= TIMER0_voidSetCallBack(PWM_usingCTC);
	GIE_voidEnable();
	while(1)
	{

	}

	 */


	/***Using Fast PWM Mode ***/



	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_OUTPUT);
	TIMERO_voidTimer0Init();
	GIE_voidEnable();
	while(1)
	{
		for(u8 i=0;i<254;i++)
		{
			TIMER0_voidSetCMPMatchVal(i);
			_delay_ms(50);
		}
		for(u8 j=253;j>0;j--)
		{
			TIMER0_voidSetCMPMatchVal(j);
			_delay_ms(50);
		}
	}

}
/*This 2 functions to toggle the led every 1sec*/
void TIMER_voidToggletheLED (void)
{
	static u16 Counter_ToToggleLed=0;
	static u8 i=0;
	Counter_ToToggleLed++;
	if(Counter_ToToggleLed==4000)
	{
		if(i%2==0)
		{DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);}
		else if(i%2!=0)
		{DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);}
		Counter_ToToggleLed=0;
		i++;
	}

}
void LedToggle(void)
{
	static u16 Counter_ToToggleLed=0;
	static u8 Local_u8LedState=0;
	Counter_ToToggleLed++;
	if(Counter_ToToggleLed==4000)
	{
		TOG_BIT(Local_u8LedState,0);
		DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN0,Local_u8LedState);
		Counter_ToToggleLed=0;
	}

}
/*This function to manipulate PWM on 3 leds*/
void PWM_usingCTC (void)
{
	static u8 Counter_ToPWMLed=0;
	Counter_ToPWMLed++;
	if(Counter_ToPWMLed==20)
	{
		DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
	}
	else if (Counter_ToPWMLed==40)
	{
		DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
	}
	else if (Counter_ToPWMLed==60)
	{
		DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
	}
	else if (Counter_ToPWMLed==80)
	{
		DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
		Counter_ToPWMLed=0;
	}

}
