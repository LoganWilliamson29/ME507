/*
 * DRV8876.cpp
 *
 *  Created on: Jul 27, 2022
 *      Author: Logan Williamson
 */

#include "DRV8876.h"
#include "STM32F4xx_HAL.h"

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
			 int16_t            _level)
{

}
//Motor enable method
void motor::enable(void)
{
	HAL_GPIO_WritePin(nSLEEP,
					  nSLEEP_Pin,
					  GPIO_PIN_SET);
}
//Motor disable method
void motor::disable(void)
{
	HAL_GPIO_WritePin(nSLEEP,
					  nSLEEP_Pin,
					  GPIO_PIN_RESET);
}

//Motor duty cycle setting method
void motor::set_level(int32_t level)
{
	if (level<-4800)
	{
		level = -4800;
	}
	else if (level>4800)
	{
		level = 4800;
	}
	if (level>=0)
	{
		__HAL_TIM_SET_COMPARE(htim, TIM_EN, level);
		HAL_GPIO_WritePin(GPIO_PH, GPIO_PH_Pin, GPIO_PIN_SET);
	}
	else if (level<0)
	{
		__HAL_TIM_SET_COMPARE(htim, TIM_EN, level);
		HAL_GPIO_WritePin(GPIO_PH, GPIO_PH_Pin, GPIO_PIN_RESET);
	}
}
