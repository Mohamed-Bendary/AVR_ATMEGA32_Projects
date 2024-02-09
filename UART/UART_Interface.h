/*
 * UART_Interface.h
 *
 *  Created on: Jul 20, 2023
 *      Author: Dell
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit(void);
void UART_u8Transmit(u8 Copy_u8TransmitData);
u8 UART_u8Recieve(void);

#endif /* UART_INTERFACE_H_ */
