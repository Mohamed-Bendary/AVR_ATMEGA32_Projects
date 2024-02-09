/*
 * main.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Dell
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include <util/delay.h>
#include "DIO_interface.h"
#include "WDT_Interface.h"
static u8 Local_u8Counter=0;
void main(void)
{

	Local_u8Counter++;
DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_OUTPUT);
DIO_voidSetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
_delay_ms(1000);
DIO_voidSetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
WDT_voidWDTEnable();
WDT_voidSleep(WDT_SLEEPTIME_1S);
WDT_voidWDTDisable();
while(1);



}
