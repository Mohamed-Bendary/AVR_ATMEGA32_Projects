
# include "STD_TYPES.h"
# include "BIT_MATH.h"
# include "DIO_interface.h"
# include <avr/delay.h>

void main()
{
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_OUTPUT);

	while(1)
	{
		for(u16 Local_u8counter=0;Local_u8counter<512;Local_u8counter++){
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_HIGH);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);
			_delay_ms(2);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_HIGH);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);
			_delay_ms(2);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_HIGH);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);
			_delay_ms(2);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
			DIO_voidSetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);
			_delay_ms(2);
		}
	}
}


