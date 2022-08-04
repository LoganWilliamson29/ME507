/*
 * AITRIP_IR_Sensor.h
 *
 *  Created on: Jul 29, 2022
 *      Author: caleb
 */

#ifndef INC_IR_SENSOR_H_
#define INC_IR_SENSOR_H_

#include "stdint.h"
//#include "stdio.h"
//#include "stm32f4xx_hal.h"



class IR_Sensor
{

private:
	uint32_t 	trigPin;

public:
	IR_Sensor(void);		// Default constructor
	//void IR_Sensor(uint32_t 	trigPin_);	// Initialization constructor
};



#endif /* INC_IR_SENSOR_H_ */