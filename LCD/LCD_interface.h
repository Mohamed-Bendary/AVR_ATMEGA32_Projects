/*
 * LCD_interface.h
 *
 *  Created on: Dec 4, 2022
 *      Author: Dell
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
void LCD_voidSendCommand(u8 Copy_u8Command);//deh 34an ab3at lel LCD command, we men al datasheet al command byb2a 1byte aw 8 bits(u8)
void LCD_voidSendCharacter(u8 Copy_u8Character);//deh 34an ab3at lel LCD char (7arf)

void LCD_voidInit(void);//ay 7aga ba3d keda lazem a3mlha function t3mlha initialization we bgbha mn al data sheet

void LCD_voidSendString(char*Copy_pu8String);//deh lw 3awez ab3t string kamel m4 char, we leha special case any lazem a7otha char y3ne array of characters m4 u8
void LCD_voidPosition(u8 Copy_u8RowPos,u8 Copy_u8ColPos);
void LCD_voidDrawSpecialCharachter(u8*Copy_pu8Pattern,u8 Copy_u8LocationNum,u8 Copy_u8RowNum,u8 Copy_u8ColNum);
void LCD_voidWriteNum(u32 copy_u32Number);


#endif /* LCD_INTERFACE_H_ */
