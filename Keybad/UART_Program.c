#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "UART_Interface.h"
#include "UART_Registers.h"
#include "UART_Private.h"
#include "UART_Config.h"


void UART_voidInit(void)
{
	/*Enable the Reciever*/
	SET_BIT(UCSRB,UCSRB_RXEN);

	/*Enable the transmitter*/
	SET_BIT(UCSRB,UCSRB_TXEN);

	/*Working on normal speed */
	CLR_BIT(UCSRA,UCSRA_U2X);

	/*No multiprocessor communication mode*/
	CLR_BIT(UCSRA,UCSRA_MPCM);

	/*Setting the baud rate to 9600 (UBRR=51)*/
	UBRRH_UCSRC=0b00000000;
	UBRRL=0b00110011;

	/*Enabling the interrupt on the reciving action*/
	SET_BIT(UCSRB,UCSRB_RXCIE);


	/*According to the BIT mode, we will assign same parameters which is:
	 * -Asych_mode -No parity -(1)Stop bit  -NO clock polarity */
#if UART_BIT_MODE   == UART_5_BIT_MODE
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	UBRRH_UCSRC=0b10000000;
#elif UART_BIT_MODE == UART_6_BIT_MODE
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	UBRRH_UCSRC=0b10000010;
#elif UART_BIT_MODE == UART_7_BIT_MODE
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	UBRRH_UCSRC=0b10000100;
#elif UART_BIT_MODE ==UART_8_BIT_MODE
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	UBRRH_UCSRC=0b10000110;
#elif UART_BIT_MODE ==UART_9_BIT_MODE
	SET_BIT(UCSRB,UCSRB_UCSZ2);
	UBRRH_UCSRC=0b10000110;
#endif
}


void UART_u8Transmit(u8 Copy_u8TransmitData)
{
	/*Polling until the UDR is empty b waiting till the UDRE bit is to be set*/
	while(GET_BIT(UCSRA,UCSRA_UDRE) == 0);
	/*Putting the User data into the UDR register to be sent to TXD pin*/
	UDR=Copy_u8TransmitData;

}
u8 UART_u8Recieve(void)
{
	u8 Local_u8RecievedData=0;

	/*polling till the Recieving is complete*/
	//while(GET_BIT(UCSRA,UCSRA_RXC) == 0);

	/*Sending the data in the UDR register to the user*/
	Local_u8RecievedData=UDR;

	return Local_u8RecievedData;
}
