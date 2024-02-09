/*
 * Timer1_interface.h
 *
 *  Created on: Jul 5, 2023
 *      Author: Dell
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_
/**initialize the timer1 with the required mode*/
void TIMER1_voidTimer1Init(void);
/*Set the cmopare match value to be used*/
void TIMER1_voidSetCMPMatchVal(u16 Copy_u8CMPMatchVal);
/*Set the overflow value(Top) if needed else it will be 2 power 16(resolution)*/
void TIMER1_voidSetTopValue(u16 Copy_u8TopVal);
/*Call back mechanism to excute the ISR based on the function used in main.c*/
u8 TIMER1_voidSetCallBack_CMP_ISR (void (*Copy_pvUserFunc) (void));





                 /******ICU part*******/
/*ICU part*/
#define ICU_RISSING_EDGE                                0
#define ICU_FALLING_EDGE                                1

void ICU_voidInit(void);
u8 ICU_u8EdgeSelect(u8 Copy_u8EdgeSelect);
u16  ICU_InputCaptureRead(void);
void ICU_EnableInterrupt(void);
void ICU_DisableInterrupt(void);
u8 TIMER1_voidSetCallBack_ICU_ISR (void (*Copy_pvUserFunc) (void));
#endif /* TIMER1_INTERFACE_H_ */
