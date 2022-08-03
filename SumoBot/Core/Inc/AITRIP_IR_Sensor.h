/*
 * AITRIP_IR_Sensor.h
 *
 *  Created on: Jul 29, 2022
 *      Author: caleb
 */

#ifndef INC_AITRIP_IR_SENSOR_H_
#define INC_AITRIP_IR_SENSOR_H_

#include "stdio.h"



class IR_Sensor
{
private:
	uint32_t 	trigPin;

public:
				IR_Sensor(void);		// Default constructor
				IR_Sensor(uint32_t 	trigPin_);	// Initialization constructor
};



#endif /* INC_AITRIP_IR_SENSOR_H_ */
