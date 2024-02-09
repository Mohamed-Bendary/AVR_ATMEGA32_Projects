/*
 * LCD_config.h
 *
 *  Created on: Dec 4, 2022
 *      Author: Dell
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
/*LCD control port*/
#define LCD_Control_Port  DIO_u8PORTD
/*LCD data port*/
#define LCD_Data_Port     DIO_u8PORTC
/*LCD register pin*/
#define LCD_RS_PIN DIO_u8PIN5
/*LCD Read/Write pin*/
#define LCD_RW_PIN DIO_u8PIN6
/*LCD Enable pin*/
#define LCD_E_PIN DIO_u8PIN7

#endif /* LCD_CONFIG_H_ */
