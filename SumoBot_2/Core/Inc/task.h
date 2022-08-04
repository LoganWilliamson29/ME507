/*
 * task.h
 *
 *  Created on: Jul 28, 2022
 *      Author: caleb
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

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
void task_init(void);
void task_run(void);
void task_S0(void);
void task_S1(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_TASK_H_ */