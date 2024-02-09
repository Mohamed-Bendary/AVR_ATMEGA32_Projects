/*
 * main.c
 *
 *  Created on: Jul 20, 2023
 *      Author: Dell
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "UART_Interface.h"
#include "EXTI_interface.h"

u8 APP_u8Data=NULL;
void main (void)
{

	/*Initialize the direction of our TX and RX*/

	/*RX PIN*/
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_INPUT);
	/*TX PIN*/
	DIO_voidSetPinDirection(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_OUTPUT);


	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_OUTPUT);
	/*Enabling the global interrupt*/
	GIE_voidEnable();

    /*Initialize USART*/
	UART_voidInit();

	while(1)
	{
		/*Recieve data from USB ttl*/
		//APP_u8Data=UART_u8Recieve();

		if(APP_u8Data=='A')
		{
			/*Turn on LED*/
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_HIGH);

		}
		else if(APP_u8Data=='B')
		{
			/*Turn OFF LED*/
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_LOW);


		}

		else
		{
			//Do nothing
		}

	}


}

/*Vip note that iam working on interrupt, so if u want to use polling
 * you should re activate the polling mechanism*/

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	APP_u8Data=UART_u8Recieve();
}




