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
			motor(TIM_HandleTypeDef* 	_htim,		// Prototype for initializing constructor
				  uint16_t				_TIM_EN,
				  GPIO_TypeDef* 		_GPIO_PH,
				  uint16_t				_GPIO_PH_Pin,
				  GPIO_TypeDef*			_nSLEEP,
				  uint16_t				_nSLEEP_Pin,
				  int16_t         		_level);
	void	enable(void);					// Prototype for motor enable method
	void	disable(void);				// Prototype for motor disable method
	void	set_level(int32_t level);// Prototype for motor PWM pin duty cycle setting method
	int32_t 				level;					//Signed 16-bit PWM (scaled-down) level from -4800 to 4800
};



#endif /* INC_DRV8876_H_ */
