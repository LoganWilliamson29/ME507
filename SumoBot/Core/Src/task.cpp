/*
 * task.cpp
 *
 *  Created on: Jul 28, 2022
 *      Author: caleb
 */


#include "task.h"

// List of the state functions
task_fct_t task_list[]   = {&task_S0,
							&task_S1};

// Create a struct to hold relevant information about the task
task_cfg_t task;


void task_init(void)
{
	task.state = 0;
	task.runs = 0;
}

// Run the current state, then increment the run counter.
void task_run(void)
{
	task_list[task.state]();
	task.runs++;
}

void task_S0(void)
{
	// State 0 stuff. Remember to transition to state 1
	// at some point.
}

void task_S1(void)
{
	// State 1 stuff. Remember to transition out at some point.
}
