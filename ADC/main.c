/*
 * main.c
 *
 *  Created on: Jun 23, 2023
 *      Author: Dell
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LCD_interface.h"
#include <util/delay.h>

/*Ha3araf al channel value hena 34an al address bta3ha mayt8ayr4 */
u8 App_u8DigitalChannelRead=NULL;
u16 App_AnalogValue_millivolt=NULL;
u8 App_TempretureReading=NULL;


void Lamp_On (void);
void Lamp_OFF(void);
void main(void)
{
	/*Defining the lamp pin as output*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_OUTPUT);

	 /*Setting the ADC channel pin to input*/
	 DIO_voidSetPinDirection(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_INPUT);

	 /*Initializing the ADC*/
	 ADC_voidADCInit();

     /*Initiazlize the LCD*/
	 LCD_voidInit();

	 /*Clearing the LCD*/
	 LCD_voidClear();

	 /*Setting Starting position*/
	 LCD_voidPosition(0,0);
	 Lamp_On();


	while(1)
	{

    App_u8DigitalChannelRead=ADC_u8GetChannelReadSynch(7);
    App_AnalogValue_millivolt=((u32)App_u8DigitalChannelRead*5000UL)/256UL;
    App_TempretureReading=App_AnalogValue_millivolt/10;
    App_TempretureReading=App_u8DigitalChannelRead/2;
    LCD_voidWriteNum(App_TempretureReading);

     _delay_ms(1000);
LCD_voidClear();
LCD_voidPosition(0,0);
	}

}


void Lamp_On (void)
{
	DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_HIGH);
}

void Lamp_OFF(void)
{
	DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_LOW);
}
