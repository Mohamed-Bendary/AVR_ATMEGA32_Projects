/*
 * Timer0_register.h
 *
 *  Created on: Jun 29, 2023
 *      Author: Dell
 */

#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_

#define TCCR0    *((volatile u8*)0x53)
#define TCCR0_FOC0     7
#define TCCR0_WGM00    6
#define TCCR0_COM01    5
#define TCCR0_COM00    4
#define TCCR0_WGM01    3
#define TCCR0_CS02     2
#define TCCR0_CS01     1
#define TCCR0_CS00     0



#define TCNT0    *((volatile u8*)0x52) /*Timer/counter register*/

#define OCR0    *((volatile u8*)0x5C)  /*Output compare register*/

#define TIMSK    *((volatile u8*)0x59) /*Timer/counter interrupt mask*/
#define TIMSK_OCIE0     1
#define TIMSK_TOUE0     0

#define TIFR   *((volatile u8*)0x58)
#define TIFR_OCF0  1
#define TIFR_TOV0  0

//generel interrupt enable (GIE)
#define SREG    *((volatile u8*)0x5F)
#define SREG_I    7   //hya deh al bit al mohma bta3to
#endif /* TIMER0_REGISTER_H_ */
