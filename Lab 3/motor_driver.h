/*
 * motor_driver.h
 *
 *  Created on: Jul 18, 2022
 *      Author: Logan Williamson, Caleb Savard, Cole Marin
 */

#ifndef INC_MOTOR_DRIVER_H_
#define INC_MOTOR_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

struct Motor
{
	TIM_HandleTypeDef* 		htim;		/* HAL Handle struct for PWM Timer*/
	uint32_t 				tim_ch_a;	/* PWM Timer channel A pin callout*/
	uint32_t 				tim_ch_b;	/* PWM Timer channel B pin callout*/

	GPIO_TypeDef* 			EN_GPIO;	/* HAL Handle struct for GPIO Port*/
	uint16_t 				EN_Pin;	   	/* Pin number associated with EN GPIO pin*/

	int8_t 				level;			/*Signed 8-bit PWM (scaled-down) duty cycle*/
} typedef Motor_t;

void	enable(Motor_t* motor);
void	disable(Motor_t* motor);
void	set_level(Motor_t* motor,int32_t level);

#endif /* INC_MOTOR_DRIVER_H_ */
