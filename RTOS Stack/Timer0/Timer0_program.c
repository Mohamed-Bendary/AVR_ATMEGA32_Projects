/*
 * Timer0_program.c
 *
 *  Created on: Jun 29, 2023
 *      Author: Dell
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"



#include "Timer0_register.h"
#include "Timer0_private.h"
#include "Timer0_config.h"
#include "Timer0_interface.h"

/*GLobal pointer to function to send the user function to the ISR*/
void (*TIMER0_PtrtoCompareMatchISR) (void)=NULL;
/*Set the compare match Value function*/
void TIMER0_voidSetCMPMatchVal(u8 Copy_u8CMPMatchVal)
{
OCR0=Copy_u8CMPMatchVal;

}


void TIMERO_voidTimer0Init(void)
{
#if TIMER0_MODE==CTC_MODE
	/*set the working mode of the wave generation to the CTC mode*/
	SET_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);

	/*Setting the clock prescaller to 8*/
	CLR_BIT(TCCR0,TCCR0_CS02);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS00);
	//Set the compare match value in the function above
	/*Enable he compare match value interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

#elif TIMER0_MODE==OVERFLOW_MODE
	CLR_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);

#elif TIMER0_MODE==Fast_PWM_mode
	/*Clear the FOC0 pin when working on PWM mode*/
	CLR_BIT(TCCR0,TCCR0_FOC0);
    /*Set the waveform generation pins to work on fast PWM mode*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	/*Select the non inverting mode in the PWM mode*/
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);
	/*Select the prescaler to 64*/
	CLR_BIT(TCCR0,TCCR0_CS02);
	SET_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS00);

#endif
}


u8 TIMER0_voidSetCallBack (void (*Copy_pvUserFunc) (void))
{
	u8 Local_u8ErrorCode=OK;
	if(Copy_pvUserFunc!=NULL)
	{
		/*Send the user function address to the global pointer to be used in the ISR */
		TIMER0_PtrtoCompareMatchISR=Copy_pvUserFunc;
	}
	else
	{
		Local_u8ErrorCode=NOT_OK;
	}
	return Local_u8ErrorCode;
}

/*The ISR is number 11-1=10 in the vector table*/
/*This ISR is for the compare match which is Set at 250*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(TIMER0_PtrtoCompareMatchISR!=NULL)
	{
		/*Excute the user implemented function in main.c*/
		TIMER0_PtrtoCompareMatchISR();
	}
}


