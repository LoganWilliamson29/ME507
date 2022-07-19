/*
 * motor_driver.c
 *
 *  Created on: Jul 18, 2022
 *      Author: Logan Williamson, Caleb Savard, Cole Marin
 */


#include "motor_driver.h"

void enable(Motor_t* motor)
{
	HAL_GPIO_WritePin(motor->EN_GPIO,
					  motor->EN_Pin,
					  GPIO_PIN_SET);
}

void disable(Motor_t* motor)
{
	HAL_GPIO_WritePin(motor->EN_GPIO,
					  motor->EN_Pin,
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
		__HAL_TIM_SET_COMPARE(motor->htim, motor->tim_ch_a, level);
		__HAL_TIM_SET_COMPARE(motor->htim, motor->tim_ch_b, 0);
	}
	else if (level<0){
		__HAL_TIM_SET_COMPARE(motor->htim, motor->tim_ch_a, 0);
		__HAL_TIM_SET_COMPARE(motor->htim, motor->tim_ch_b, -level);
	}
}
