/*
 * EXTI_program.c
 *
 *  Created on: Mar 15, 2023
 *      Author: Dell
 */
# include "BIT_MATH.h"
# include "STD_TYPES.h"


#include "EXTI_register.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"
/*Implementing the global pointer to function */
void (*EXTI_INT0ptrtofunc) (void)=NULL;

/*****************pre-build configuration******************/

//INT0 initialization
void EXTI_voidINT0Init(void)
{
#if INT0_EN_STATE==INT0_ENABLE
	//Enable peripheral interrupt (PIE)
	SET_BIT(GICR,GICR_INT0);
#elif	INT0_EN_STATE==INT0_DISABLE
	CLR_BIT(GICR,GICR_INT0);
#else
#error "INVALID OPTION"
#endif


#if INT0_SENSE_CONTROL==INT0_FALLING_EDGE
	//Sensing interrupt of falling edge for INT0
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
	//THE flag is not into consideration because we are using the ISR approch so its automatically handled
	// global interrupt is to be activated by another function
#elif INT0_SENSE_CONTROL==INT0_LOW_LEVEL
	//Sensing interrupt of low level for INT0
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CONTROL==INT0_ON_CHANGE
	//Sensing interrupt of any logical change edge for INT0
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif INT0_SENSE_CONTROL==INT0_RISSING_EDGE
	//Sensing interrupt of rissing edge for INT0
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#else
#error "INVALID SENSE CONTROL"
#endif
}
//INT1 initialization
void EXTI_voidINT1Init(void)
{
#if INT1_EN_STATE==INT1_ENABLE
	//Enable peripheral interrupt (PIE)
	SET_BIT(GICR,GICR_INT1);
#elif	INT1_EN_STATE==INT1_DISABLE
	CLR_BIT(GICR,GICR_INT1);
#else
#error "INVALID OPTION"
#endif


#if INT1_SENSE_CONTROL==INT1_FALLING_EDGE
	//Sensing interrupt of falling edge for INT1
	SET_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);
	//THE flag is not into consideration because we are using the ISR approch so its automatically handled
	// global interrupt is to be activated by another function
#elif INT1_SENSE_CONTROL==INT1_LOW_LEVEL
	//Sensing interrupt of low level for INT1
	CLR_BIT(MCUCR,MCUCR_ISC11);
	CLR_BIT(MCUCR,MCUCR_ISC10);

#elif INT1_SENSE_CONTROL==INT1_ON_CHANGE
	//Sensing interrupt of any logical change edge for INT1
	CLR_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);
#elif INT1_SENSE_CONTROL==INT1_RISSING_EDGE
	//Sensing interrupt of rissing edge for INT1
	SET_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(MCUCR,MCUCR_ISC10);
#else
#error "INVALID SENSE CONTROL"
#endif






}
//INT2 initialization
void EXTI_voidINT2Init(void)
{


#if INT2_EN_STATE==INT2_ENABLE
	//Enable peripheral interrupt (PIE)
	SET_BIT(GICR,GICR_INT2);
#elif	INT2_EN_STATE==INT2_DISABLE
	CLR_BIT(GICR,GICR_INT2);
#else
#error "INVALID OPTION"
#endif


#if INT2_SENSE_CONTROL==INT2_FALLING_EDGE
	//Sensing interrupt of falling edge for INT2

	CLR_BIT(MCUCSR,MCUCSR_ISC2);
	//THE flag is not into consideration because we are using the ISR approch so its automatically handled
	// global interrupt is to be activated by another function

#elif INT2_SENSE_CONTROL==INT2_RISSING_EDGE
	//Sensing interrupt of rissing edge for INT2
	SET_BIT(MCUCSR,MCUCSR_ISC2);
#else
#error "INVALID SENSE CONTROL"
#endif

}

/************Post-build configuration**************/

/********just an example of a function of Init0*******/

/*u8 EXTI_voidINT0Init(u8 copy_u8SenseControl)
{
	u8 Local_u8ErrrorCode=0;
	//Enable peripheral interrupt (PIE)
	SET_BIT(GICR,GICR_INT0);

	switch (copy_u8SenseControl)
	{
	case INT0_FALLING_EDGE   : //Sensing interrupt of falling edge for INT0
		CLR_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);break;

	case INT0_LOW_LEVEL      : //Sensing interrupt of low level for INT0
		CLR_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);break;

	case INT0_ON_CHANGE      : //Sensing interrupt of any logical change edge for INT0
		SET_BIT(MCUCR,MCUCR_ISC00);
		CLR_BIT(MCUCR,MCUCR_ISC01);break;

	case INT0_RISSING_EDGE   : //Sensing interrupt of any logical change edge for INT0
		SET_BIT(MCUCR,MCUCR_ISC00);
		SET_BIT(MCUCR,MCUCR_ISC01);break;
	default:      Local_u8ErrrorCode=1; break;

	}
	return Local_u8ErrrorCode;

}

*/



//Global interrupt (GIE)
//Enable
void GIE_voidEnable(void)
{
	SET_BIT(SREG,SREG_I);
}

//Disbale
void GIE_voidDisable(void)
{
	CLR_BIT(SREG,SREG_I);
}

/*Setcallback funcition*/
u8 EXTI_u8SetCallBack(void (*Copy_pvUserFunc) (void))
{
	u8 Copy_u8LocalErrorCode=OK;
   if (Copy_pvUserFunc!=NULL)
   {
	EXTI_INT0ptrtofunc=Copy_pvUserFunc;
   }
   else
   {Copy_u8LocalErrorCode=NOT_OK;}
   return Copy_u8LocalErrorCode;
}
/*Interrupt service routine (ISR),,get the vector number from datasheet page 42,,we matsa4 tena2as 1*/
/*ISR implemention for INT0*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{

	if(EXTI_INT0ptrtofunc!=NULL)
	{
		EXTI_INT0ptrtofunc();
	}
}







