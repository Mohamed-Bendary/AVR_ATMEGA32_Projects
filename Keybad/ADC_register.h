/*
 * ADC_register.h
 *
 *  Created on: Mar 21, 2023
 *      Author: Dell
 */

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX *((volatile u8*)0x27)

#define ADMUX_REFS1  7
#define ADMUX_REFS0  6
#define ADMUX_ADLAR  5
#define ADMUX_MUX4   4
#define ADMUX_MUX3   3
#define ADMUX_MUX2   2
#define ADMUX_MUX1   1
#define ADMUX_MUX0   0



#define ADCSRA *((volatile u8*)0x26)

#define ADCSRA_ADEN   7
#define ADCSRA_ADSC   6
#define ADCSRA_ADATE  5
#define ADCSRA_ADIF   4
#define ADCSRA_ADIE   3
#define ADCSRA_ADPS2  2
#define ADCSRA_ADPS1  1
#define ADCSRA_ADPS0  0


#define ADCH  *((volatile u8*)0x25)
#define ADCL  *((volatile u8*)0x24)

#define SFIOR *((volatile u8*)0x50)
#define SFIOR_ADTS2     7
#define SFIOR_ADTS1     6
#define SFIOR_ADTS0     5

//General interrupt Enable
#define SREG    *((volatile u8*)0x5F)
#define SREG_I    7   //hya deh al bit al mohma bta3to


#endif /* ADC_REGISTER_H_ */
