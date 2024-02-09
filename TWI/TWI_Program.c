
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TWI_Registers.h"
#include "TWI_Private.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"



/*Master init, you have to send the address of the master in case it turns into a slave*/
void TWI_voidMasterInit(u8 Copy_u8NodeAddress)
{
	/*Settig the SCL frequency to 400kps(equation from page 173)*/
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);
	TWBR=2;

	/*Puttig the Master address,and eliminating the reserved addresess==> 0 & 1111xxx*/
	if((Copy_u8NodeAddress!=0)||(Copy_u8NodeAddress<119))
	{
		/*Shifting 1 to the left because the SA is the most 7 significant bits*/
		TWAR=Copy_u8NodeAddress << 1;
	}
	/*Enable the Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable the general Call*/
	SET_BIT(TWAR,TWAR_TWGCE);

	/*Enable the TWI interrupt,DONT FORGET TO ENABLE THE GLOBAL INTERRUPT*/
	//SET_BIT(TWCR,TWCR_TWIE);

	/*Enable the TWI peripheral*/
	SET_BIT(TWCR,TWCR_TWEN);
}

/*Slave init*/
void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	/*Putting the Slave address*/
	/*Shifting 1 to the left because the SA is the most 7 significant bits*/
	TWAR=Copy_u8SlaveAddress << 1;

	/*Enable the TWI peripheral*/
	SET_BIT(TWCR,TWCR_TWEN);

}

/*Send start condition*/
TWI_ErrorCode_t TWI_SendStartCondition(void)
{

	TWI_ErrorCode_t Local_ErrorStatus= NoError;
	/*Send the start conditon*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*ma3loma mohma: 2abl mal start maybda2 al flag aslan bykon marfo3 f34an
	 * al start yetbe3et lazem tclear aflag, we ba3d mal start yetbe3t al flag hytrefe3 tany
	 * wel status code hatwsal, we ba3d keda tegahez al SA+R/W ,clear flag we eb3at al SA+R/W*/

	/*Clearing the flag to send the start condition */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the flag is raised*/
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	/*Check the status code is equal to the start or not*/
	if((TWSR & 0b11111000) != START_ACK) //bit masking bit 2:0
	{
		Local_ErrorStatus=StartError;
	}
	else
	{
		/*Do nothing*/

	}

	return Local_ErrorStatus;
}

/*Send repeated start condition*/
/*same as start condition but with change of ACK*/
TWI_ErrorCode_t TWI_SendRepeatedStartCondition(void)
{
	TWI_ErrorCode_t Local_ErrorStatus= NoError;

	/*Send the repeated start conditon*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*ma3loma mohma: 2abl mal start maybda2 al flag aslan bykon marfo3 f34an
	 * al start yetbe3et lazem tclear aflag, we ba3d mal start yetbe3t al flag hytrefe3 tany
	 * wel status code hatwsal, we ba3d keda tegahez al SA+R/W ,clear flag we eb3at al SA+R/W*/

	/*Clearing the flag to send the start condition */
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the flag is raised to know that the process is done*/
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	/*Check the status code is equal to the start or not*/
	if((TWSR & 0b11111000) != REP_START_ACK) //bit masking bit 2:0
	{
		Local_ErrorStatus=RepeatedStartError;
	}
	else
	{
		/*Do nothing*/

	}

	return Local_ErrorStatus;


}

/*Send Slave address with write*/
TWI_ErrorCode_t TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorCode_t Local_ErrorStatus= NoError;

	/*Clearing the start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Sending the TWDR the slave address and Write condtion(0)*/
	TWDR=Copy_u8SlaveAddress << 1;
	CLR_BIT(TWDR,0);

	/*CLear the flag to send the SLA+W*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the flag is raised to know that the process is done*/
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	/*Check for SLA+W status*/
	if((TWSR & 0b11111000) != SLAVE_ADD_AND_WR_ACK) //bit masking bit 2:0
	{
		Local_ErrorStatus=SlaveAddWithWriteError;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_ErrorStatus;
}

/*Send Slave address with Read*/
TWI_ErrorCode_t TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{

	TWI_ErrorCode_t Local_ErrorStatus= NoError;

	/*Clearing the start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Sending the TWDR the slave address and read condtion(1)*/
	TWDR=Copy_u8SlaveAddress << 1;
	SET_BIT(TWDR,0);

	/*CLear the flag to send the SLA+R*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the flag is raised to know that the process is done*/
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	/*Check for SLA+R status*/
	if((TWSR & 0b11111000) != SLAVE_ADD_AND_RD_ACK) //bit masking bit 2:0
	{
		Local_ErrorStatus=SlaveAddWithReadError;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_ErrorStatus;


}

/* Master Send data byte*/
TWI_ErrorCode_t TWI_SendDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrorCode_t Local_ErrorStatus= NoError;

	/*Sending the TWDR the Data byte*/
	TWDR=Copy_u8DataByte;

	/*CLear the flag to send the Data Byte*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the flag is raised to know that the process is done*/
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	/*Check for Master writng data byte status*/
	if((TWSR & 0b11111000) != MSTR_WR_BYTE_ACK) //bit masking bit 2:0
	{
		Local_ErrorStatus=MstrWriteDataError;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_ErrorStatus;


}

/*Master receive data byte (sent from slave)
 * Note that i will return the error code, and the received data is
 * saved in a pointer, so send the address of the variable you want to recieve the
 * data in*/

TWI_ErrorCode_t TWI_RecieveDataByte(u8* Copy_pu8DataByte)
{
	TWI_ErrorCode_t Local_ErrorStatus= NoError;

	/*CLear the flag to start the receiving process of the Data Byte*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Wait until the flag is raised to know that the receiving process is done*/
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	/*Check for MSTR received data with ACK status*/
	if((TWSR & 0b11111000) != MSTR_RD_BYTE_WITH_ACK) //bit masking bit 2:0
	{
		Local_ErrorStatus=MstrReadDataError;
	}
	else
	{
		/*if it received the data correctly==> load the received data in TWDR to the user*/
		*Copy_pu8DataByte=TWDR;
	}
	return Local_ErrorStatus;


}

/*Send stop condition*/
void TWI_SendStopCondition(void)
{

     /*Sending the stop condtion*/
	/* Note that this bit is cleared automatically so dont worry for future
	 * Sending procedure to be stopped again by this bit*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Clearing the flag to send the Stop condition*/
	SET_BIT(TWCR,TWCR_TWINT);

	//Note that there is no ACK in the status code to be checked
}


