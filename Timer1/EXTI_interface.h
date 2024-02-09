/*
 * EXTI_interface.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Dell
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_
//INT0 initialization
void EXTI_voidINT0Init(void);
//INT1 initialization
void EXTI_voidINT1Init(void);
//INT2 initialization
void EXTI_voidINT2Init(void);


//u8 EXTI_voidINT0Init(u8 copy_u8SenseControl);



//Global interrupt (GIE)
//Enable
void GIE_voidEnable(void);

//Disbale
void GIE_voidDisable(void);

/*Set call back funtion*/
u8 EXTI_u8SetCallBack(void (*Copy_pvUserFunc) (void));


#endif /* EXTI_INTERFACE_H_ */
