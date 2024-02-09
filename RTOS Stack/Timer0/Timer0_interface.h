/*
 * Timer0_interface.h
 *
 *  Created on: Jun 29, 2023
 *      Author: Dell
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

/*first, the call back function to excute the ISR using the fuction the user will set
 * in the main.c*/
void TIMER0_voidSetCMPMatchVal(u8 Copy_u8CMPMatchVal);
void TIMERO_voidTimer0Init(void);
u8 TIMER0_voidSetCallBack (void (*Copy_pvUserFunc) (void));


#endif /* TIMER0_INTERFACE_H_ */
