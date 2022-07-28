/*
 * DRV8876.cpp
 *
 *  Created on: Jul 27, 2022
 *      Author: Logan Williamson
 */

#include "DRV8876.h"
//Default constructor
motor::motor(void)
{

}

//Initializing constructor
motor::motor(TIM_HandleTypeDef* _htim,
			 uint16_t			_TIM_EN,
		  	 GPIO_TypeDef* 	 	_GPIO_PH,
			 uint16_t			_GPIO_PH_Pin,
			 GPIO_TypeDef*		_nSLEEP,
			 uint16_t			_nSLEEP_Pin,
			 int16_t            _level);

//Motor enable method
void enable(Motor_t* motor)
{
	HAL_GPIO_WritePin(motor->nSLEEP,
					  motor->nSLEEP_Pin,
					  GPIO_PIN_SET);
}
//Motor disable method
void disable(Motor_t* motor)
{
	HAL_GPIO_WritePin(motor->nSLEEP,
					  motor->nSLEEP_Pin,
					  GPIO_PIN_RESET);
}

//Motor duty cycle setting method
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
