/*
 * EXTI_config.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Dell
 */

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*options
 * 1-ENABLE
 * 2-DISABLE
 * */
# define INT0_EN_STATE INT0_ENABLE
# define INT1_EN_STATE INT1_ENABLE
# define INT2_EN_STATE INT2_ENABLE
/*Sense control options
 * 1-INT0_LOW_LEVEL
 * 2-INT0_ON_CHANGE
 * 3-INT0_FALLING_EDGE
 * 4-INT0_RISSING_EDGE
 *
 * */

#define INT0_SENSE_CONTROL   INT0_FALLING_EDGE
#define INT1_SENSE_CONTROL   INT1_FALLING_EDGE
#define INT2_SENSE_CONTROL   INT2_RISSING_EDGE

#endif /* EXTI_CONFIG_H_ */
