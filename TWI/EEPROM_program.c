
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "EEPROM_Config.h"
#include "EEPROM_Private.h"
#include "EEPROM_Interface.h"



#include "TWI_Interface.h"

/*Here to send data from uc to EEPROM,first argument is the data you want to send
 * Second arg is where==> 000000(A1)(A0)(00000000)
 * first 6 zeros is obligary after that you choose A1&A0 of which page to write on
 * and finally you choose in the next 8 bits which byte in the page you want to write on  */
void EEPROM_voidSendData(u8 Copy_u8DataByte,u16 Copy_u16Address)
{

/*First sending the starting condition to initiate the communication between uc and EEPROM*/
TWI_SendStartCondition();

/*Sending the Slave Address+Write which will be (1010(A2)(A1)(A0) to determine:
 * which EEPROM--Which page*/
TWI_SendSlaveAddressWithWrite((0b1010000)|(A2<<2)|(Copy_u16Address>>8));

/*Sending which byte in the chosen page to write on by:
 * Casting the 16 bit address to get the least 8bits which contain which byte in the page to write on*/
TWI_SendDataByte((u8)Copy_u16Address);

/*Sending the actual data*/
TWI_SendDataByte(Copy_u8DataByte);

/*Sending the stop condtion*/
TWI_SendStopCondition();


}
/*Recieving the data from EEPROM to the uc*/
u8 EEPROM_u8RecieveData(u16 Copy_u16Address)
{
u8 Local_u8DataByte=NULL;

/*First sending the starting condition to initiate the communication between uc and EEPROM*/
TWI_SendStartCondition();

/*Before receiving you must do same procedure of EEPROM_voidSendData to select the byte you want
 * to take the data from before receiving
 * we do that because to select a certain byte in a page in EEPROM you have to do
 * 2 things which are sending which EEPROM and which page (A2,A1,A0) which
 * could be done by both TWI_SendSlaveAddressWithWrite or TWI_SendSlaveAddressWithRead
 * but the second stage of sending which byte to receive is by sending 8bits of the address of
 * the byte of which to write or receiving,,,, only could be done by the function TWI_SendDataByte
 * and this function is the follow up of the function TWI_SendSlaveAddressWithWrite
 * so you have to use this sequence :
 * 1-TWI_SendSlaveAddressWithWrite==> which EEPROM and page
 * 2-TWI_SendDataByte==> which byte in the page
 * 3- TWI_SendRepeatedStartCondition==> re starting to begin the receiving procedure after selecting the page and byte
 * 4-TWI_SendSlaveAddressWithRead==> To read from a certaing EEPROM and page
 * 5-TWI_RecieveDataByte==> receiving the data because the byte to read from is previously been selected
 * 6-Stop the communication*/
TWI_SendSlaveAddressWithWrite((0b1010000)|(A2<<2)|(Copy_u16Address>>8));


TWI_SendDataByte((u8)Copy_u16Address);


TWI_SendRepeatedStartCondition();


TWI_SendSlaveAddressWithRead((0b1010000)|(A2<<2)|(Copy_u16Address>>8));


TWI_RecieveDataByte(&Local_u8DataByte);


TWI_SendStopCondition();

return Local_u8DataByte;
}


