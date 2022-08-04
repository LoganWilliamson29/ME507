/*
 * testingTask.h
 *
 *  Created on: Jul 28, 2022
 *      Author: caleb
 */

#ifndef INC_TASKTESTING_H_
#define INC_TASKTESTING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"


// Structure for holding relevant information to the task
typedef struct task_cfg
{
	uint32_t state;
	uint32_t runs;
} task_cfg_t;

// Datatype for pointers to task state functions
typedef void (*task_fcn_t)(void);

// Prototypes for each task function.
void taskTesting_init(void);
void taskTesting_run(void);
void taskTesting_S0(void);
void taskTesting_S1(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_TASKTESTING_H_ */
