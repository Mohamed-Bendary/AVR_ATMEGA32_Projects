

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

void DIO_voidSetPinDirection(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8PinDirection);//bt5lek t7ot etgah al pin out wla in fa me7taga any port we any pin we hat7ot any etgah

void DIO_voidSetPortDirection(u8 Copy_u8Port,u8 Copy_u8PortDirection);//bt5lek t7ot etgah al port kolo be kol pinato out wla in fa me7taga t7ot any port we etgahom eh out wla in


void DIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8PinValue);//bt5lek t7ot al value bta3et al pin 1,0 fa me7taga any port we any pin we al value

void DIO_voidSetPortValue(u8 Copy_u8Port,u8 Copy_u8PortValue);//bt5lek t7ot al value bta3et al port kolo be kol pinato 1,0

u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin);//bt5lek tgeb al value bta3et any pin be bkam
/*MACROS WILL BE USED INSTEAD OF MAGIC NUMBERS*/
#define DIO_u8PORTA      1
#define DIO_u8PORTB      2
#define DIO_u8PORTC      3
#define DIO_u8PORTD      4

#define DIO_u8PIN0       0
#define DIO_u8PIN1       1
#define DIO_u8PIN2       2
#define DIO_u8PIN3       3
#define DIO_u8PIN4       4
#define DIO_u8PIN5       5
#define DIO_u8PIN6       6
#define DIO_u8PIN7       7

#define DIO_u8PIN_INPUT  0
#define DIO_u8PIN_OUTPUT 1



#define DIO_u8PORT_INPUT  0x00//OR 0x0
#define DIO_u8PORT_OUTPUT  0xFF

#define DIO_u8PIN_LOW    0
#define DIO_u8PIN_HIGH   1

#define DIO_u8PORT_LOW    0x00
#define DIO_u8PORT_HIGH   0xFF

#endif
