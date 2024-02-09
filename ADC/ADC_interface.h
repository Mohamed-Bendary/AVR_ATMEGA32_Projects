/*
 * ADC_interface.h
 *
 *  Created on: Mar 21, 2023
 *      Author: Dell
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
//initialize ADC
void ADC_voidADCInit(void);

/*Get the channel read,be careful that the channels is from 0 to7*/
u8 ADC_u8GetChannelReadSynch(u8 copy_u8Channel);
/*Another function i n asynch approach, where i take from user the channel,
 * The address of the notification function
 * The address of the variable to put the ADC result in it*/
u8 ADC_u8GetChannelReadAsynch(u8 copy_u8Channel,void (*Copy_pvNotificationfunc) (void),u8 *Copy_pu8ADCRead);


#endif /* ADC_INTERFACE_H_ */
