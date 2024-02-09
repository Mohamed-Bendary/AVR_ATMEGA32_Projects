/*

 * Moving name.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Dell
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD_interface.h"
#include<avr/delay.h>
void main(){

	LCD_voidInit();
	u8 ArabicLetterA[8]={
				0b00000000,
				0b00010000,
				0b00010000,
				0b00010000,
				0b00010000,
				0b00010000,
				0b00010000,
				0b00010000,
		};
	u8 Bendo_3ade[8]={
			0b00000100,
			0b00001010,
			0b00001010,
			0b00000100,
			0b00001110,
			0b00000100,
			0b00001010,
			0b00010001,
	};
	LCD_voidPosition(0,0);
	LCD_voidSendString("Hi iam bendo");
	LCD_voidDrawSpecialCharachter(Bendo_3ade,0,0,14);
	_delay_ms(3000);
	LCD_voidSendCommand(0b00000001);
	u8 Bendo_2ablmayshoot[8]={
			0b00000100,
			0b00001010,
			0b00001010,
			0b00000100,
			0b00001110,
			0b00000100,
			0b00001010,
			0b00001001,
	};
	u8 kora1[8]={
			0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000001};
	u8 kora2[8]={
			0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000010};

	u8 kora3[8]={
			0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000100};
	u8 kora4[8]={
			0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001000};
	u8 kora5[8]={
			0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00010000};
	LCD_voidPosition(0,3);
	LCD_voidSendString("I play kora");
	LCD_voidDrawSpecialCharachter(Bendo_2ablmayshoot,2,1,14);
	LCD_voidDrawSpecialCharachter(kora5,1,1,14);
	_delay_ms(2000);
	LCD_voidSendCommand(0b00000001);

	LCD_voidDrawSpecialCharachter(Bendo_3ade,0,1,14);

	LCD_voidDrawSpecialCharachter(kora1,1,1,13);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(kora2,1,1,13);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(kora3,1,1,13);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(kora4,1,1,13);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(kora5,1,1,13);
	_delay_ms(500);

	LCD_voidDrawSpecialCharachter(kora1,1,1,12);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(kora2,1,1,12);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(kora3,1,1,12);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(kora4,1,1,12);
	_delay_ms(500);
	LCD_voidDrawSpecialCharachter(ArabicLetterA,2,1,12);
_delay_ms(100);
LCD_voidSendCommand(0b00000001);

LCD_voidSendString("GOAL!!!!!");













	/*u8 ArabicLetterM[8]={
				0b00000000,
				0b00001110,
				0b00001110,
				0b00001110,
				0b00001000,
				0b00001000,
				0b00001000,
				0b00001000,
		};

		u8 ArabicLetterH[8]={
				0b00000000,
				0b00000000,
				0b00001110,
				0b00000010,
				0b00011110,
				0b00000000,
				0b00000000,
				0b00000000,
		};

		u8 ArabicLetterD[8]={
				0b00000000,
				0b00000000,
				0b00000010,
				0b00000010,
				0b00001110,
				0b00000000,
				0b00000000,
				0b00000000,
		};
		u8 ArabicLetterN[8]={
				0b00000000,
				0b00000000,
				0b00001010,
				0b00000010,
				0b00001110,
				0b00000000,
				0b00000000,
				0b00000000,
		};
		u8 ArabicLetterB[8]={
				0b00000000,
				0b00000000,
				0b00010010,
				0b00010010,
				0b00011110,
				0b00000000,
				0b00001100,
				0b00000000,
		};
		u8 ArabicLetterA[8]={
				0b00000000,
				0b00000100,
				0b00000100,
				0b00000100,
				0b00000100,
				0b00000100,
				0b00000100,
				0b00000000,
		};
		u8 ArabicLetterR[8]={
				0b00000000,
				0b00000001,
				0b00000001,
				0b00000011,
				0b00000110,
				0b00001100,
				0b00011000,
				0b00000000,
		};
		u8 ArabicLetterY[8]={
				0b00000000,
				0b00000000,
				0b00000011,
				0b00000010,
				0b00010010,
				0b00010010,
				0b00011110,
				0b00000000,
		};
//moving name
		for(int i=0;i<16;i++)
		{
			u8 Row_Num=0;
			if(i%2==0)
			{
				Row_Num=0;
				LCD_voidDrawSpecialCharachter(ArabicLetterM,0,Row_Num,(15-i));
				LCD_voidDrawSpecialCharachter(ArabicLetterH,1,Row_Num,(14-i));
				LCD_voidDrawSpecialCharachter(ArabicLetterM,0,Row_Num,(13-i));
				LCD_voidDrawSpecialCharachter(ArabicLetterD,2,Row_Num,(12-i));
				_delay_ms(1000);
				LCD_voidSendCommand(0b00000001);

			}
			else if(i%2!=0)
			{
				Row_Num=1;
				LCD_voidDrawSpecialCharachter(ArabicLetterM,0,Row_Num,(15-i));
				LCD_voidDrawSpecialCharachter(ArabicLetterH,1,Row_Num,(14-i));
				LCD_voidDrawSpecialCharachter(ArabicLetterM,0,Row_Num,(13-i));
				LCD_voidDrawSpecialCharachter(ArabicLetterD,2,Row_Num,(12-i));
				_delay_ms(1000);
				LCD_voidSendCommand(0b00000001);

			}

		}
   }
	 */


	/*printing my name*/

	/*LCD_voidDrawSpecialCharachter(ArabicLetterM,0,0,15);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterH,1,0,14);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterM,0,0,13);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterD,2,0,12);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterB,3,0,10);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterN,4,0,9);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterD,2,0,8);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterA,5,0,7);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterR,6,0,6);
    _delay_ms(500);
    LCD_voidDrawSpecialCharachter(ArabicLetterY,7,0,5);

	 */


}

