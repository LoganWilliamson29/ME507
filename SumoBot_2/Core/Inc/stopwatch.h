/*
 * stopwatch.h
 *
 *  Created on: Jul 27, 2022
 *      Author: caleb
 */

#ifndef INC_STOPWATCH_H_
#define INC_STOPWATCH_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "stream.h"


class stopwatch
{
private:
	uint32_t 	start_ticks;
	uint32_t 	end_ticks;
public:
	uint32_t	diff;
	stream_t 	ser_port;

	void start(void);
	uint32_t end(void);
	stopwatch(stream_t);

};

typedef stopwatch stopwatch_t;


#endif /* INC_STOPWATCH_H_ */
