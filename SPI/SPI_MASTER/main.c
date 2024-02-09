
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util/delay.h>

#include "DIO_interface.h"
#include "SPI_Interface.h"


void main(void)
{
	/*MOSI output for master*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN5,DIO_u8PIN_OUTPUT);

	/*MISO is input for master*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN6,DIO_u8PIN_INPUT);

	/*SCK is output for master*/
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN7,DIO_u8PIN_OUTPUT);

	/*Initialize the SPI peripheral*/
	SPI_voidInit();

	u8 Local_u8Recieved_data=0;
	while(1)
	{
		/*Sending 10 to slave , in the slave project it will recieve 10 but it
		 * has to send any data (garbage) to the master*/
		Local_u8Recieved_data=SPI_voidTranceieveData(10);
		_delay_ms(500);

	}


}
