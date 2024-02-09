/*
 * main.c
 *
 *  Created on: Mar 16, 2023
 *      Author: Dell
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include <util/delay.h>
#include <avr/io.h>

void IR_SystemOff_ON(void);

 u8 Local_u8IRData;
 void main(void)
 {


	 EXTI_voidINT0Init();
	 GIE_voidEnable();


DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_OUTPUT);

DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_INPUT);

EXTI_u8SetCallBack(&IR_SystemOff_ON);
while (1)
{



}

 }
void IR_SystemOff_ON(void)
{

Local_u8IRData=DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8PIN2);
if(Local_u8IRData==DIO_u8PIN_HIGH)
 {
 DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_HIGH);

 }
else
 {
 DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_LOW);

 }
}

