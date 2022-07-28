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
#include <stdint.h>
#include <string.h>
#include <iostream>

class motor
{
private:
	TIM_HandleTypeDef* 		htim;				// HAL Handle struct for PWM Timer
	GPIO_TypeDef* 			GPIO_PH;			// GPIO direction control pin port
	uint16_t 				GPIO_PH_Pin;		// Pin number associated with GPIO_PH directon control pin
	uint16_t				TIM_EN;				// Timer PWM duty cycle control pin
	GPIO_TypeDef* 			nSLEEP;				// HAL Handle struct for GPIO Port
	uint16_t 				nSLEEP_Pin;	   		// Pin number associated with EN GPIO pin
public:
		motor(void);							// Prototype for default constructor
		motor(TIM_HandleTypeDef* _htim,			// Prototype for initializing constructor
			  GPIO_TypeDef* 	 _GPIO_PH,
			  uint16_t			 _GPIO_PH_Pin,
			  uint16_t			 _TIM_EN,
			  GPIO_TypeDef*		 _nSLEEP,
			  uint16_t			 _nSLEEP_Pin,
			  int16_t            _level);
	int8_t 					level;				//Signed 8-bit PWM (scaled-down) duty cycle
} typedef Motor_t;

void	enable(Motor_t* motor);
void	disable(Motor_t* motor);
void	set_level(Motor_t* motor,int32_t level);

#endif /* INC_MOTOR_DRIVER_H_ */
#endif /* INC_DRV8876_H_ */
