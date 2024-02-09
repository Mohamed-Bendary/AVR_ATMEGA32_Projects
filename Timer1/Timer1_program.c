/*
 * Timer1_program.c
 *
 *  Created on: Jul 5, 2023
 *      Author: Dell
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "Timer1_registers.h"
#include "Timer1_private.h"
#include "Timer1_config.h"
#include "Timer1_interface.h"

/*Global pointer to function to execute the CMP based ISR*/
void (*TIMER1_PtrtoCompareMatch_ChannelA_ISR) (void)=NULL;
void (*TIMER1_PtrtoICU_ISR) (void)=NULL;

/**initialize the timer1 with the required mode*/
void TIMER1_voidTimer1Init(void)
{
#if TIMER1_MODE==FAST_PWM_MANIPULATED_TOPVALUE_MODE

	/*Choose the fast pwm mode with ICR1 top value*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*for safety, we clear FOC1A & FOC1B because we working on PWM mode*/
	CLR_BIT(TCCR1A,TCCR1A_FOC1A);
	CLR_BIT(TCCR1A,TCCR1A_FOC1B);

	/*Working on channel A*/
	/*Using the non inverted mode(clear on CMP & set on top)*/
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);

	/*Setting  the prescaller to 8*/
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);



#elif TIMER1_MODE==CTC_MODE
	/*Remember to enable the required bits in the TIMSK register*/
#elif TIMER1_MODE==NORMAL_MODE
#elif TIMER1_MODE==FAST_PWM_8BIT_MODE
#elif TIMER1_MODE==FAST_PWM_9BIT_MODE
#elif TIMER1_MODE==FAST_PWM_10BIT_MODE
#elif TIMER1_MODE==PWM_PHASE_CORRECT_8BIT_MODE
#elif TIMER1_MODE==PWM_PHASE_CORRECT_9BIT_MODE
#elif TIMER1_MODE==PWM_PHASE_CORRECT_10BIT_MODE

#endif
}
/*Set the compare match value to be used*/
void TIMER1_voidSetCMPMatchVal(u16 Copy_u8CMPMatchVal)
{
	OCR1A=Copy_u8CMPMatchVal;
}
/*Set the overflow value(Top) if needed else it will be 2 power 16(resolution)*/
void TIMER1_voidSetTopValue(u16 Copy_u8TopVal)
{
	ICR1=Copy_u8TopVal;
}
/*Call back mechanism to execute the ISR based on the function used in main.c*/
u8 TIMER1_voidSetCallBack_CMP_ISR (void (*Copy_pvUserFunc) (void))
{
	u8 Local_u8ErrorCode=OK;
	if(Copy_pvUserFunc!=NULL)
	{
		TIMER1_PtrtoCompareMatch_ChannelA_ISR=Copy_pvUserFunc;
	}

	else
	{
		Local_u8ErrorCode=NOT_OK;
	}
	return Local_u8ErrorCode;
}


/*The ISR of the Compare Match on channel A*/
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	if(TIMER1_PtrtoCompareMatch_ChannelA_ISR!=NULL)
	{
		/*Excute the user implemented function in main.c*/
		TIMER1_PtrtoCompareMatch_ChannelA_ISR();
	}
}


/****ICU Part*****/
/*initialize the ICU & chooe the edge, 0->rissing edge  1->falling edge*/
/*Dont forget to enable the GIE*/
void ICU_voidInit()
{
	/*Seting the noise canceler mode*/
	SET_BIT(TCCR1B,TCCR1B_ICNC1);

	/*Setting  the prescaller to 8*/
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS10);

	/*Settin the edge as rissing edge till it is changed by the next function*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable the input capture interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
u8 ICU_u8EdgeSelect(u8 Copy_u8EdgeSelect)
{
	u8 Local_u8ErrorCode=OK;
	/*Setting the input capture edge according to the user*/
	if(Copy_u8EdgeSelect==ICU_RISSING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8EdgeSelect==ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else
	{
		Local_u8ErrorCode=NOT_OK;
	}
	return Local_u8ErrorCode;
}
u16  ICU_InputCaptureRead(void)
{
	return ICR1;
}
void ICU_EnableInterrupt(void)
{
	SET_BIT(TIMSK,TIMSK_TICIE1);
}
void ICU_DisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

u8 TIMER1_voidSetCallBack_ICU_ISR (void (*Copy_pvUserFunc) (void))
{

	u8 Local_u8ErrorCode=OK;
	if(Copy_pvUserFunc!=NULL)
	{
		TIMER1_PtrtoICU_ISR=Copy_pvUserFunc;
	}

	else
	{
		Local_u8ErrorCode=NOT_OK;
	}
	return Local_u8ErrorCode;

}

/*The ISR of the ICU channel*/
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(TIMER1_PtrtoICU_ISR!=NULL)
	{
		/*Excute the user implemented function in main.c*/
		TIMER1_PtrtoICU_ISR();
	}
}





