/*
 * SPI_program.c
 *
 *  Created on: Jul 24, 2023
 *      Author: Dell
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_Registers.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"
#include "SPI_Private.h"

void SPI_voidInit(void)
{
#if SPI_MODE == SPI_MODE_MASTER


	/*The LSB of the data is transmitted first*/
	SET_BIT(SPCR,SPCR_DORD);

	/*choosing master mode*/
	SET_BIT(SPCR,SPCR_MSTR);

	/*Set the SCK frequency to fosc/64*/
	CLR_BIT(SPSR,SPSR_SPI2X);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPCR,SPCR_SPR0);

	/*Enable the peripheral*/
    SET_BIT(SPCR,SPCR_SPE);
#else if SPI_MODE == SPI_MODE_SLAVE

	/*choosing slave mode*/
	CLR_BIT(SPCR,SPCR_MSTR);

     /*NO need for adjusing the clock*/

	/*Enable the peripheral*/
	SET_BIT(SPCR,SPCR_SPE);
#endif

}

/*using synchronous approach*/
u8 SPI_voidTranceieveData (u8 Copy_u8Data)
{
	/*Send the data*/
	SPDR=Copy_u8Data;

	/*polling(busy waiting) untill the transmission is complete*/
	while(GET_BIT(SPSR,SPSR_SPIF)==0);

	/*Return the exchanged data from the slave*/
	return SPDR;
	/*No need for clearing the flag ourselves, because in datasheet the flag is cleared in
	 * two cases:
	 * 1-using interrupt (not in this case)
	 * 2-reading the SPIF flag(in line 50)&& accessing SPDR register(in line 53)*/


}
