
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "SPI_Interface.h"


void main(void)
{
	/*MOSI input for slave*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_INPUT);

	/*MISO is output for slave*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_OUTPUT);

	/*SCK is input for slave*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_INPUT);

	/*the led configuration */
	DIO_voidSetPinDirection(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_OUTPUT);

	/*Initialize the SPI peripheral*/
	SPI_voidInit();
	u8 Local_u8RecievedData=0;
	while(1)
	{
		/*Receiving the (10) from master and sending garbage 20 to master
		 * that the master shall ignore*/
		Local_u8RecievedData=SPI_voidTranceieveData(20);
		_delay_ms(500);
		if(Local_u8RecievedData == 10)
		{
			//Turn on the LED and turn it off after 1 second
			DIO_voidSetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);
			_delay_ms(1000);
			DIO_voidSetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
		}
	}
}
