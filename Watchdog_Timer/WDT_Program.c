/*
 * WDT_Program.c
 *
 *  Created on: Jul 19, 2023
 *      Author: Dell
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WDT_Config.h"
#include "WDT_Interface.h"
#include "WDT_Private.h"
#include "WDT_Register.h"

void WDT_voidWDTEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}
void WDT_voidWDTDisable(void)
{
	/*The disable sequence*/
	/*First: we write logic one to both WDE and WDTOE*/
	WDTCR=0b00011000;
	/*Secondly we will write zero to WDE(and putting 0 to WDTOE wouldnt hurt)*/
	WDTCR=0;

}
u8 WDT_voidSleep(u8 Copy_u8SleepTime)
{
	u8 Local_u8ErrorCode=OK;
	if(Copy_u8SleepTime<8)
	{
		/*Bit masking sequence
		 * 1- clear the required bits
		 * 2- put the required value in it*/
		WDTCR &= 0b11111000;
		WDTCR |=Copy_u8SleepTime;

	}
	else
	{
		Local_u8ErrorCode=NOT_OK;
	}
	return Local_u8ErrorCode;


}
