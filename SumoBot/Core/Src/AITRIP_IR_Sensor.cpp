/*
 * AITRIP_IR_Sensor.cpp
 *
 *  Created on: Jul 29, 2022
 *      Author: caleb
 */


#include "AITRIP_IR_Sensor.h"
#include "STM32F4xx_HAL.h"


// Default Constructor
IR_Sensor::IR_Sensor(void)
{

}

IR_Sensor::IR_Sensor(uint32_t trigPin_)
				:trigPin(trigPin_)
{

}

