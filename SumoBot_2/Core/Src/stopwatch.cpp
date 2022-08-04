/*
 * stopwatch.cpp
 *
 *  Created on: Jul 27, 2022
 *      Author: caleb
 */


#include "stopwatch.h"

stopwatch::stopwatch(stream_t ser_port_)
				:ser_port (ser_port_)
{

}


void stopwatch::start(void)
{
	ser_port << "Starting stopwatch..." << ENDL;

	start_ticks = HAL_GetTick();
}

uint32_t stopwatch::end(void)
{
	end_ticks = HAL_GetTick();

	diff = end_ticks - start_ticks;
	ser_port << diff << " ms have elapsed." << ENDL;

	return diff;
}