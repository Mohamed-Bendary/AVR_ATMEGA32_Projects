/*
 * Keypad_config.h
 *
 *  Created on: Oct 7, 2022
 *      Author: Mohamed Hashim Attiya Said
 */


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/*To configure the whole keybad in one port*/
#define KEYPAD_PORT			            	DIO_u8PORTA

/*To configure the rows and columns in separate ports*/
#define KEYPAD_CLOUMNS_PORT				    DIO_u8PORTA
#define KEYPAD_ROWS_PORT					DIO_u8PORTB


#define KEY_PAD_COLUMN0_PIN		DIO_u8PIN0
#define KEY_PAD_COLUMN1_PIN		DIO_u8PIN1
#define KEY_PAD_COLUMN2_PIN		DIO_u8PIN2
#define KEY_PAD_COLUMN3_PIN		DIO_u8PIN3

#define KEY_PAD_ROW0_PIN		DIO_u8PIN0
#define KEY_PAD_ROW1_PIN		DIO_u8PIN1
#define KEY_PAD_ROW2_PIN		DIO_u8PIN2
#define KEY_PAD_ROW3_PIN		DIO_u8PIN3




								//				   ÷
#define KEYPAD_ARR_VAL			{{'1' ,'2' , '3', '4'}, {'5', '6', '7', '8'}, {'9', '0', '+', '-'}, {'*', '/', '%', '='}}



#endif /* KEYPAD_CONFIG_H_ */

