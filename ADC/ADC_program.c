/*
 * ADC_program.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Dell
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_interface.h"


/*Global Pointer to function to be used in Asynch function to hold the Notification
 * function Address*/

void (*ADC_PtrToNotificationFunc) (void)=NULL;

/*Global pointer to hold the variable to send the ADCH or ADCL to
 * when the conversion is done and the ISR will be excuted */

u8 *ADC_pu8PtrTo_ADCRead =NULL;


//initialize ADC
void ADC_voidADCInit(void)
{
	/*Choose the AVCC as a reference voltage*/
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);


	/*Enable the left adjust*/
	SET_BIT(ADMUX,ADMUX_ADLAR);

	/*Set the prescalar of our 	ADC clock to 128(divide the 8MHZ by 128)*/
	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS2);



	/*VIP NOTE:make the enabling of any peripheral the last step in the initializing*/
	/*Enable the ADC peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

/*Get the channel read,be careful that the channels is from 0 to 7*/
u8 ADC_u8GetChannelReadSynch(u8 copy_u8Channel)
{
	u32 Local_u32Counter=0;
	/*Masking*/
	/*1-Clearing the required bits*/
	ADMUX &=0b11100000;

	/*2- Set the required bits*/

	ADMUX |=copy_u8Channel;

	/*Start the conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);

	/*polling(busy wait until the conversion is done when the flag is raised or when the ADC reach timout )*/
	while((GET_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(Local_u32Counter<ADC_TIMEOUT))
	{
		Local_u32Counter++;
	}

	if(Local_u32Counter==ADC_TIMEOUT)
	{
	/*Set the error code to NOT_OK bas ana mkasel a3mlha 34an
	 * hatar a8ayr al return ano yeb2a al error code we ha7ot parameter zyada
	 * fel function ale hoa pointer 34an ab3atlo al ADCH or al ADCL
	 * 34an yet7ato fel holding variable*/
	}
	else{
	/*flag clearing*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);

	/*Finally return the output of the analog to digital conversion which is ADCH because we enabled the left adjustment*/
	return ADCH;
	}
}






/*Get read function but in Asynch form*/
u8 ADC_u8GetChannelReadAsynch(u8 copy_u8Channel,void (*Copy_pvNotificationfunc) (void),u8 *Copy_pu8ADCRead)
{
	u8 Local_u8ErrorCode=OK;
	/*chec; that the addres of the Notification func & the Addres of
	 * the ADC read holding variable are not = 0(NULL)*/
	if((Copy_pvNotificationfunc!=NULL)&&(Copy_pu8ADCRead!=NULL))
	{
		/*Put the addresses of the holding variable and the notifunction to
		 * the Globel pointers to be sent to the ISR function
		 * to excute the Notification function
		 * and to send the ADCH or the ADCL to the holding variable */
		ADC_pu8PtrTo_ADCRead=Copy_pu8ADCRead;
		ADC_PtrToNotificationFunc=Copy_pvNotificationfunc;

		/*Masking*/
		/*1-Clearing the required bits*/
		ADMUX &=0b11100000;

		/*2- Set the required bits*/
		ADMUX |=copy_u8Channel;

		/*Start the conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*Enable the ADC Interrupt complete conversion
		 * Note that ADIF is raised when the ADC conversion is done*/
		SET_BIT(SREG,SREG_I);
		SET_BIT(ADCSRA,ADCSRA_ADIE);
	}

	else
	{Local_u8ErrorCode=NOT_OK;}

	return Local_u8ErrorCode;
}

/*ISR implementation*/

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	/*send the ADC read to the Holding variable in the main.c*/
	*ADC_pu8PtrTo_ADCRead=ADCH;
	/*Excute the notification function using the global ptr to func*/
	ADC_PtrToNotificationFunc();
	/*Extra: Disable the ADC interrupt for power consumption*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}






















