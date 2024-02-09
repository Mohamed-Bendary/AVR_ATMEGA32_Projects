/*
 * WDT_Register.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Dell
 */

#ifndef WDT_REGISTER_H_
#define WDT_REGISTER_H_

#define WDTCR                   *((volatile u8*)0x41)

#define WDTCR_WDTOE                   4
#define WDTCR_WDE                     3
#define WDTCR_WDP2                    2
#define WDTCR_WDP1                    1
#define WDTCR_WDP0                    0

#endif /* WDT_REGISTER_H_ */
