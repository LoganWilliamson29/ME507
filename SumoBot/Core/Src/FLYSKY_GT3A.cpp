/*
 * FLYSKY_GT3A.cpp
 *
 *  Created on: Jul 28, 2022
 *      Author: Logan Williamson
 */

#include "FLYSKY_GT3A.h"
#include "STM32F4xx_HAL.h"

// Default Constructor
FlySky::FlySky(void)
{

}

// Initializing Constructor
FlySky::FlySky(TIM_HandleTypeDef*	_htim,
				uint32_t 			_STR_CH,
				uint32_t 			_THR_CH,
				uint8_t 			_THR_Edge,
				uint8_t				_STR_Edge,
				uint16_t 			_STR_Val1,
				uint16_t 			_STR_Val2,
				uint16_t 			_THR_Val1,
				uint16_t 			_THR_Val2)
{

}
void FlySky::Get_Widths(void)
/*License
 * Controllers Tech (2020) Measuring Pulse Width [Source Code]. https://controllerstech.com/input-capture-in-stm32/
 */
{
	if (htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
	{
		if ((THR_Edge==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7))==1)
		{
			THR_Val1 = HAL_TIM_ReadCapturedValue(htim,THR_CH);
			THR_Edge = 1;
		}
		else if ((THR_Edge==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7))==0)
		{
			THR_Val2 = HAL_TIM_ReadCapturedValue(htim,THR_CH);
			if (THR_Val2 > THR_Val1)
			{
				THR_Width = (THR_Val2 - THR_Val1);
			}
			else if (THR_Val1 > THR_Val2)
			{
				THR_Width = ((0xffff - THR_Val1) + THR_Val2);
			}
			THR_Edge = 0;
		}
	}
	if (htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if ((STR_Edge==0)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6))==1)
		{
			STR_Val1 = HAL_TIM_ReadCapturedValue(htim,STR_CH);
			STR_Edge = 1;
		}
		else if ((STR_Edge==1)&&(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6))==0)
		{
			STR_Val2 = HAL_TIM_ReadCapturedValue(htim,STR_CH);
			if (STR_Val2 > STR_Val1)
			{
				STR_Width = (STR_Val2 - STR_Val1);
			}
			else if (STR_Val1 > STR_Val2)
			{
				STR_Width = ((0xffff - STR_Val1) + STR_Val2);
			}
			STR_Edge = 0;
		}
	}

}
