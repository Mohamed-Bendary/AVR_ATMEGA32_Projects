/*
 * TWI_Interface.h
 *
 *  Created on: Jul 30, 2023
 *      Author: Dell
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_
/*Put an enum to contain different error codes to be used in debuging*/
typedef enum
{
	NoError,
	StartError,
	RepeatedStartError,
	SlaveAddWithWriteError,
	SlaveAddWithReadError,
	MstrWriteDataError,
	MstrReadDataError
}TWI_ErrorCode_t;
//(t) means user defined data type



/*Master init, you have to send the address of the master in case it turns into a slave*/
void TWI_voidMasterInit(u8 Copy_u8NodeAddress);

/*Slave init*/
void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress);

/*Send start condition*/
TWI_ErrorCode_t TWI_SendStartCondition(void);

/*Send repeated start condition*/
TWI_ErrorCode_t TWI_SendRepeatedStartCondition(void);

/*Send Slave address with write*/
TWI_ErrorCode_t TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

/*Send Slave address with Read*/
TWI_ErrorCode_t TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

/* Master Send data byte*/
TWI_ErrorCode_t TWI_SendDataByte(u8 Copy_u8DataByte);

/*Master recieve data byte(sent from slave)
 * Note that i will return the error code, and the recived data is
 * saved in a pointer, so send the address of the variable you want to recieve the
 * data in*/

TWI_ErrorCode_t TWI_RecieveDataByte(u8* Copy_pu8DataByte);

/*Send stop condition*/
void TWI_SendStopCondition(void);



#endif /* TWI_INTERFACE_H_ */
