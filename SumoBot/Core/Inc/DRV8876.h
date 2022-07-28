/*
 * DRV8876.h
 *
 *  Created on: Jul 27, 2022
 *      Author: Logan Williamson
 */

#ifndef INC_DRV8876_H_
#define INC_DRV8876_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

struct Motor
{
	TIM_HandleTypeDef* 		htim;			/* HAL Handle struct for PWM Timer*/
	GPIO_TypeDef* 			GPIO_PH;		/* GPIO direction control pin*/
	uint16_t 				GPIO_PH_Pin;	/*Pin number associated with GPIO_PH GPIO object*/
	uint32_t				TIM_EN;			/* Timer PWM duty cycle control pin*/

	GPIO_TypeDef* 			nSLEEP;			/* HAL Handle struct for GPIO Port*/
	uint16_t 				nSLEEP_Pin;	   	/* Pin number associated with EN GPIO pin*/

	int8_t 					level;			/*Signed 8-bit PWM (scaled-down) duty cycle*/
} typedef Motor_t;

void	enable(Motor_t* motor);
void	disable(Motor_t* motor);
void	set_level(Motor_t* motor,int32_t level);

#endif /* INC_MOTOR_DRIVER_H_ */
#endif /* INC_DRV8876_H_ */
