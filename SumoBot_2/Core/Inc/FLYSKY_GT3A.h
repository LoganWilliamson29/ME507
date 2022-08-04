/*
 * FLYSKY_GT3A.h
 *
 *  Created on: Jul 28, 2022
 *      Author: logan
 */

#ifndef INC_FLYSKY_GT3A_H_
#define INC_FLYSKY_GT3A_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

class FlySky
{
private:
	TIM_HandleTypeDef*		htim;				//HAL timer handle for PWM timer
	uint32_t 				STR_CH;				// Input timer channel 1 pin callout
	uint32_t 				THR_CH;				// Input timer channel 2 pin callout
	uint8_t 				THR_Edge; 			// Throttle channel rising versus falling edge tracker
	uint8_t					STR_Edge;			// Steering channel rising versus falling edge tracker
	uint16_t 				STR_Val1;			// Latched tim_ch_a rising edge timer value upon interrupt callback
	uint16_t 				STR_Val2;			// Latched tim_ch_a falling edge time value upon interrupt callback
	uint16_t 				THR_Val1;			// Latched tim_ch_a rising edge timer value upon interrupt callback
	uint16_t 				THR_Val2;			// Latched tim_ch_a falling edge time value upon interrupt callback

public:
	FlySky(void);								// Prototype for default constructor
	FlySky(TIM_HandleTypeDef*	htim,			// Prototype for initializing constructor
			uint32_t 			STR_CH,
			uint32_t 			THR_CH,
			uint8_t 			THR_Edge,
			uint8_t				STR_Edge,
			uint16_t 			STR_Val1,
			uint16_t 			STR_Val2,
			uint16_t 			THR_Val1,
			uint16_t 			THR_Val2);
	void Get_Widths(void);						// Prototype for positive width calculation of steering and throttle channels
			uint16_t			STR_Width;		// Pulse width of steering signal, channel 1
			uint16_t			THR_Width;		// Pulse width of throttle signal, channel 2

};

#endif /* INC_FLYSKY_GT3A_H_ */