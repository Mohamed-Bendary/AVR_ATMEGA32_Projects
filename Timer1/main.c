/*
 * main.c
 *
 *  Created on: Jul 5, 2023
 *      Author: Dell
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/delay.h>

#include "LCD_interface.h"
#include "Timer0_interface.h"
#include "DIO_interface.h"
#include "Timer1_interface.h"


/*****Servo application***/
/*
void main(void)
{
	/*
	//Configure the TIMER1 pwm channelA_pin
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN5,DIO_u8PIN_OUTPUT);
	//Initialize the timer1
	TIMER1_voidTimer1Init();
	//Set the top value to 20ms (20000 tick) to communicate with the servo
	TIMER1_voidSetTopValue(20000);
	while(1)
	{
		//Set the ON time to 500 to 2500 to control the servo from 0 to 180*/
	/*		TIMER1_voidSetCMPMatchVal(500);
		_delay_ms(1500);
		TIMER1_voidSetCMPMatchVal(600);
		_delay_ms(200);
		TIMER1_voidSetCMPMatchVal(700);
		_delay_ms(200);
		TIMER1_voidSetCMPMatchVal(750);
		_delay_ms(200);
		TIMER1_voidSetCMPMatchVal(1000);
		_delay_ms(200);
		TIMER1_voidSetCMPMatchVal(1250);
		_delay_ms(200);
		TIMER1_voidSetCMPMatchVal(2000);
		_delay_ms(200);
		TIMER1_voidSetCMPMatchVal(2400);
		_delay_ms(200);
		TIMER1_voidSetCMPMatchVal(2499);
		_delay_ms(1500);
	}


	 */




/*****ICU PART****/

void ICU_ISR (void);
/*GLobal variable to store the Periodic time that we will print in the LCD*/
u16 Periodic_Time=0;

/*GLobal variable to store the ON time that we will print in the LCD*/
u16 ON_Time=0;

u16 HBD=0;
void main(void)
{

	/*generate PWM  signal and read the data through ICU and put the data on LCD*/
	/*Define the PortB pin3 (OC0) of timer0 to generate PWM from it*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_OUTPUT);

	/*We will recieve the data on the (ICP)pin*/
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_INPUT);

	/*Enable the global interrupt*/
	GIE_voidEnable();

	/*Enable the timer0 on PWM mode*/
	TIMERO_voidTimer0Init();


	/*Initialize ICU unit*/
	ICU_voidInit();//RISSING EDGE

	/*Setcallback mechanism*/
	TIMER1_voidSetCallBack_ICU_ISR(ICU_ISR);

	/*LCD initialize*/
	LCD_voidInit();


	while(1)
	{

     /*wait until the readings is finished*/
		while((Periodic_Time==0)&&(ON_Time==0));
		LCD_voidPosition(0,0);
		LCD_voidSendString("PTime: ");
		LCD_voidWriteNum(Periodic_Time);
		LCD_voidPosition(1,0);
		LCD_voidSendString("OnTime: ");
		LCD_voidWriteNum(ON_Time);

	}




}
void ICU_ISR (void)
{
	static u8 Local_u8Counter=0;
	u8 Local_u8ErrorCode=OK;
	/*the times must be static because it will be erased when the function is over*/
	static u16 Local_u16First_Reading,Local_u16Second_Reading,Local_u16Third_Reading;
	Local_u8Counter++;
	/*First we will capture the point 1*/
	if(Local_u8Counter==1)
	{
		Local_u16First_Reading=ICU_InputCaptureRead();
	}
	/*Secondly we wil capture the second capture to calculate periodic time & set the edge to falling*/
	else if(Local_u8Counter==2)
	{
		Local_u16Second_Reading=ICU_InputCaptureRead();
		Periodic_Time=Local_u16Second_Reading-Local_u16First_Reading;
		Local_u8ErrorCode=ICU_u8EdgeSelect(ICU_FALLING_EDGE);
	}
	/*Finally,We will get the third reading and calculate ON time &disable the interrupt*/
	else if(Local_u8Counter==3)
	{
		Local_u16Third_Reading=ICU_InputCaptureRead();
		ON_Time=Local_u16Third_Reading-Local_u16Second_Reading;
		HBD=Local_u16Third_Reading;
		ICU_DisableInterrupt();
        //Local_u8Counter=0;

	}


}
