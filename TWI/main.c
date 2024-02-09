#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include <util/delay.h>
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "TWI_Interface.h"
#include "EEPROM_Interface.h"


u8 DataToBeSentToEEPROM=5;
u8 DataToBeSentToLCD=0;
u16 Address=0x0000;
void main(void)
{
	/*setting both SCL & SDA as output*/
	DIO_voidSetPinDirection(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_OUTPUT);

	/*Initilizing the uc as a master and giving it its address*/
	TWI_voidMasterInit(0);

	/*Initializing the LCD to send the data to*/
	LCD_voidInit();

	while(1)
	{
		EEPROM_voidSendData(DataToBeSentToEEPROM,Address);
		_delay_ms(1000);
		DataToBeSentToLCD=EEPROM_u8RecieveData(Address);
		LCD_voidPosition(0,0);
		LCD_voidWriteNum(DataToBeSentToLCD);
		_delay_ms(1000);
		DataToBeSentToEEPROM++;
	}




}
