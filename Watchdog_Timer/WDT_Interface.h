/*
 * WDT_Interface.h
 *
 *  Created on: Jul 19, 2023
 *      Author: Dell
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

#define WDT_SLEEPTIME_16.3MS      0
#define WDT_SLEEPTIME_32.5MS      1
#define WDT_SLEEPTIME_65MS        2
#define WDT_SLEEPTIME_0.13S       3
#define WDT_SLEEPTIME_0.26S       4
#define WDT_SLEEPTIME_0.52S       5
#define WDT_SLEEPTIME_1S          6
#define WDT_SLEEPTIME_2.1S        7

void WDT_voidWDTEnable(void);
void WDT_voidWDTDisable(void);
u8 WDT_voidSleep(u8 Copy_u8SleepTime);


#endif /* WDT_INTERFACE_H_ */
