/*
 * testingTask.cpp
 *
 *  Created on: Jul 28, 2022
 *      Author: caleb
 */


#include <taskTesting.h>
#include "stream.h"



	// List of the state functions
	task_fcn_t taskTesting::task_list[]   = {&S0,
								&S1};

	// Create a struct to hold relevant information about the task
	task_cfg_t taskTesting::task_struct;

	uint32_t 	sampleVal = 55;

	void taskTesting::init(void)
	{
		taskTesting::task_struct.state = 0;
		taskTesting::task_struct.runs = 0;


	}

	// Run the current state, then increment the run counter.
	void taskTesting::run(void)
	{
		taskTesting::task_list[task_struct.state]();
		taskTesting::task_struct.runs++;
	}

	void S0(void)
	{
		// Read from all the sensors
		task_struct.state = 1;
	}

	void S1(void)
	{
		// print results
		ser_port << "The sample value is: " << sampleVal;

		// Return to the read state (0)
		task_struct.state = 0;

	}
