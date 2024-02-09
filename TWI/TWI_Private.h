/*
 * TWI_Private.h
 *
 *  Created on: Jul 30, 2023
 *      Author: Dell
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define START_ACK                          0x08  //Start acknowledge
#define REP_START_ACK                      0x10  //Repeated Start acknowledge
#define SLAVE_ADD_AND_WR_ACK               0x18  //Slave address with write
#define SLAVE_ADD_AND_RD_ACK               0x40  //Slave address with read
#define MSTR_WR_BYTE_ACK                   0x28  //master write byte
#define MSTR_RD_BYTE_WITH_ACK              0x50  //master read byte with acknowledge
#define MSTR_RD_BYTE_WITH_NACK             0x58  //master read byte with Not acknowledge
#define SLAVE_ADD_RCVD_RD_REQ              0xA8  //Slave address received read request
#define SLAVE_ADD_RCVD_WR_REQ              0x60  //Slave address received write request
#define SLAVE_DATA_RECIEVED                0x80  //slave data received
#define SLAVE_BYTE_TRANSMITTED             0xB8  //slave byte transmitted
#endif /* TWI_PRIVATE_H_ */
