/*
 * Timer1_registers.h
 *
 *  Created on: Jul 5, 2023
 *      Author: Dell
 */

#ifndef TIMER1_REGISTERS_H_
#define TIMER1_REGISTERS_H_

#define TCCR1A    *((volatile u8*)0x4F)
#define TCCR1A_COM1A1     7
#define TCCR1A_COM1A0     6
#define TCCR1A_COM1B1     5
#define TCCR1A_COM1B0     4
#define TCCR1A_FOC1A      3
#define TCCR1A_FOC1B      2
#define TCCR1A_WGM11      1
#define TCCR1A_WGM10      0


#define TCCR1B    *((volatile u8*)0x4E) //bit 5 is reserved
#define TCCR1B_ICNC1     7
#define TCCR1B_ICES1     6
#define TCCR1B_WGM13     4
#define TCCR1B_WGM12     3
#define TCCR1B_CS12      2
#define TCCR1B_CS11      1
#define TCCR1B_CS10      0

#define TCNT1    *((volatile u16*)0x4C)
/*Output compare match value*/
#define OCR1A    *((volatile u16*)0x4A)
#define OCR1B    *((volatile u16*)0x48)

/*input Capture register & also used to set the top value of the overflow*/
#define ICR1    *((volatile u16*)0x46)

/*Timer interrupt mask*/
#define TIMSK    *((volatile u8*)0x59)
#define TIMSK_TICIE1    5
#define TIMSK_OCIE1A    4
#define TIMSK_OCIE1B    3
#define TIMSK_TOIE1     2

/*Timer interrupt flag*/
#define TIFR    *((volatile u8*)0x)
#define TIFR_ICF1      5
#define TIFR_OCF1A     4
#define TIFR_OCF1B     3
#define TIFR_TOV1      2



#endif /* TIMER1_REGISTERS_H_ */
