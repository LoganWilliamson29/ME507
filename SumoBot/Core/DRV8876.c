/*
 * DRV8876.c
 *
 *  Created on: Jul 27, 2022
 *      Author: Logan Williamson
 */

#include "DRV8876.h"

void enable(Motor_t* motor)
{
	HAL_GPIO_WritePin(motor->nSLEEP,
					  motor->nSLEEP_Pin,
					  GPIO_PIN_SET);
}

void disable(Motor_t* motor)
{
	HAL_GPIO_WritePin(motor->nSLEEP,
					  motor->nSLEEP_Pin,
					  GPIO_PIN_RESET);
}
void set_level(Motor_t* motor, int32_t level)
{
	if (level<-4800){
		level = -4800;
	}
	else if (level>4800){
		level = 4800;
	}
	if (level>=0){
		__HAL_TIM_SET_COMPARE(motor->htim, motor->TIM_EN, level);
		__HAL_GPIO_WritePin(motor->GPIO_PH, motor->GPIO_PH_Pin, GPIO_PIN_SET);
	}
	else if (level<0){
		__HAL_TIM_SET_COMPARE(motor->htim, motor->TIM_EN, level);
		__HAL_TIM_SET_COMPARE(motor->htim, motor->GPIO_PH_Pin, GPIO_PIN_RESET);
	}
}
