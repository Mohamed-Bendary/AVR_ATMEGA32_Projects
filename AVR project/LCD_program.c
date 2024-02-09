/*
 * LCD_program.c
 *
 *  Created on: Dec 4, 2022
 *      Author: Dell
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include <avr/delay.h>

#include"DIO_interface.h"

#include"LCD_interface.h"
#include"LCD_config.h"
#include"LCD_private.h"
void LCD_voidSendCommand(u8 Copy_u8Command)
{
	/*NOTE:ana ha3mel al port wel pin direction fel Init function*/
	/*to send command, put RS to low(0)*/


	DIO_voidSetPinValue(LCD_Control_Port,LCD_RS_PIN,DIO_u8PIN_LOW);// 7ATET AL RS be zero
	/*to get to write mode, u have to et RW to low(0)*/
	DIO_voidSetPinValue(LCD_Control_Port,LCD_RW_PIN,DIO_u8PIN_LOW);
	/*7ot b2a al command al user hayb3to fel data port(D0---D7)*/
	DIO_voidSetPortValue(LCD_Data_Port,Copy_u8Command);
	/*4a8al al enable---HIGH-delay-low*/
	DIO_voidSetPinValue(LCD_Control_Port,LCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);//han3raf leh 2 millisecond 2odam
	DIO_voidSetPinValue(LCD_Control_Port,LCD_E_PIN,DIO_u8PIN_LOW);
}

void LCD_voidSendCharacter(u8 Copy_u8Character)
{
	/*to send data, put RS to high(1)*/

	DIO_voidSetPinValue(LCD_Control_Port,LCD_RS_PIN,DIO_u8PIN_HIGH);// 7ATET AL RS be zero
	/*to get to write mode, u have to et RW to low(0)*/
	DIO_voidSetPinValue(LCD_Control_Port,LCD_RW_PIN,DIO_u8PIN_LOW);
	/*7ot b2a al data al user hayb3to fel data port(D0---D7)*/
	DIO_voidSetPortValue(LCD_Data_Port,Copy_u8Character);
	/*4a8al al enable*/
	DIO_voidSetPinValue(LCD_Control_Port,LCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);//han3raf leh 2 millisecond 2odam
	DIO_voidSetPinValue(LCD_Control_Port,LCD_E_PIN,DIO_u8PIN_LOW);



}
void LCD_voidInit(void)//hena ha7ot al direction bta3 pins al data wel control
{
	/*ha5aly al data pins output, hya keda 3la tol ayan kan hatla3 commands wla data*/
	DIO_voidSetPortDirection(LCD_Data_Port,DIO_u8PORT_OUTPUT);
	/*ha5aly bardo al control pins kol wa7da output,bla4 a5aly al control port kolo output 34an dol 3 pins momkn ast3mel nafs al port al 5 pins al ba2yeen fe 7aga tanya*/
	DIO_voidSetPinDirection(LCD_Control_Port,LCD_RS_PIN,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_Control_Port,LCD_RW_PIN,DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_Control_Port,LCD_E_PIN,DIO_u8PIN_OUTPUT);
	/*to initalize LCD (from data sheet)first is to wait(delay)more than 30ms after the power is on*/
_delay_ms(40);
/*In 8 bit initialization (data sheet) we have to send commands of 0b0011NFxx(Ma4ro7a fel kashkol)
 *N:Number of lines, 0:for 1 line, 1:for two lines
 *F:Font size, 0:for 5*8 ,1:for 5*11
 *x:Dont care (0 or 1 doesnt matter)*/
  LCD_voidSendCommand(0b00111000);
  /*Initialize display on-off
   *D:display 0:disable 1: enable
   *C:cursor 0: disable 1: enable
   *B: blinking cursor : 0: fixed 1: blinking  */
  LCD_voidSendCommand(0b00001100);
/*To clear display(tenadaf ale etkatab 2abl keda)*/
  LCD_voidSendCommand(0b00000001);

}
void LCD_voidPosition(u8 Copy_u8RowPos,u8 Copy_u8ColPos){
	u8 Local_u8Address;
	/*Setting the address location if the user wants to set the posion in the first row*/
	if(Copy_u8RowPos==0){
		Local_u8Address=Copy_u8ColPos;

	}
	/*Setting the address location if the user wants to set the posion in the second row*/
	else if(Copy_u8RowPos==1){
		Local_u8Address=Copy_u8ColPos+0x40;
	}
	/*ana keda 3rf al location na2es ab3to lel LCD ,mawgoda fel datasheet ezay ab3t al address lel DDRAM*/
	//ma4o7a fel ka4kol
	LCD_voidSendCommand(Local_u8Address+128);
	}



/*String is an array of charachters, and the last charachter is (/0)
 */
void LCD_voidSendString(char*Copy_pcString){

	u8 Local_u8Counter;
	while(Copy_pcString[Local_u8Counter]!='\0')
	{
		LCD_voidSendCharacter(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}

}


void LCD_voidDrawSpecialCharachter(u8*Copy_pu8Pattern,u8 Copy_u8LocationNum,u8 Copy_u8RowNum,u8 Copy_u8ColNum)
{
/*Accessing the CGRAM address*/
	u8 Local_u8CGRAMAddress,Local_u8Counter;
	Local_u8CGRAMAddress=Copy_u8LocationNum*8;//ma4ro7a fel ka4kol
	/*Accesing CGRAM of lcd by command 0b01xxxxxx*/
LCD_voidSendCommand(Local_u8CGRAMAddress+64);
/*Write the pattern on CGRAM*/
/*zy makont ba3mel fel string ha3mel hena , bas al fekra ane hawa2f al loop 3nd (((8))) ale howa max bytes in a location in the CGRAM fal user masaln e5tar location 0 fa2a5ro feh 8 charachters ale homa 8 bytes*/
for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
{
LCD_voidSendCharacter(Copy_pu8Pattern[Local_u8Counter]);
}
/*Keda e7na 7atena al pattern fe location mo3yn fel CGRAM, fa na2esna bas neb3at al pattern lel DDRAM 34an n7oto fel LCD */
/*kona fo2 3malna command 34an ne access al CGRAM 34an ne access al DDRAM lazem command tany,,wel set position feha asln al command dah*/
LCD_voidPosition(Copy_u8RowNum,Copy_u8ColNum);
LCD_voidSendCharacter(Copy_u8LocationNum);
}

void LCD_voidClear(void)
{

	LCD_voidSendCommand(0b00000001);
}
