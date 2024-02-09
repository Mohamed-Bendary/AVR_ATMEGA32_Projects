/*
 * EXTI_register.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Dell
 */

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_
//	for interrupt pins INT0&1
#define MCUCR    *((volatile u8*)0x55)
//INT0
#define MCUCR_ISC00  0
#define MCUCR_ISC01  1
//INT1
#define MCUCR_ISC10  2
#define MCUCR_ISC11  3

//for interrupt pin INT2
#define MCUCSR    *((volatile u8*)0x54)
//INT2
#define MCUCSR_ISC2  6


//peripheral(specific) interrupt enable (PIE)
#define GICR    *((volatile u8*)0x5B)
#define GICR_INT2   5
#define GICR_INT0   6
#define GICR_INT1   7

//peripheral interrupt Flag (PIF)
#define GIFR    *((volatile u8*)0x5A)
#define GIFR_INTF2     5
#define GIFR_INTF0     6
#define GIFR_INTF1     7

//generel interrupt enable (GIE)
#define SREG    *((volatile u8*)0x5F)
#define SREG_I    7   //hya deh al bit al mohma bta3to

#endif /* EXTI_REGISTER_H_ */
