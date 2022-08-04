/*
 * testingTask.cpp
 *
 *  Created on: Jul 28, 2022
 *      Author: caleb
 */


#include <taskTesting.h>
#include "stream.h"


// List of the state functions
task_fcn_t taskTesting_list[]   = {&taskTesting_S0,
								   &taskTesting_S1};

// Create a struct to hold relevant information about the task
task_cfg_t taskTesting;

uint32_t 	sampleVal = 55;

void taskTesting_init(void)
{
	taskTesting.state = 0;
	taskTesting.runs = 0;

}

// Run the current state, then increment the run counter.
void taskTesting_run(void)
{
	taskTesting_list[taskTesting.state]();
	taskTesting.runs++;
}

void taskTesting_S0(void)
{
	// Read from all the sensors
	taskTesting.state = 1;
}

void taskTesting_S1(void)
{
	// print results


	// Return to the read state (0)
	taskTesting.state = 0;

}
