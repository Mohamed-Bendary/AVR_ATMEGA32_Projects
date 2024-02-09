/*
 * EEPROM_Interface.h
 *
 *  Created on: Aug 1, 2023
 *      Author: Dell
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
/**/
void EEPROM_voidSendData(u8 Copy_u8DataByte,u16 Copy_u16Address);
/**/
u8 EEPROM_u8RecieveData(u16 Copy_u16Address);


#endif /* EEPROM_INTERFACE_H_ */
