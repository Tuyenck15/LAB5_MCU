/*
 * timer.h
 *
 *  Created on: Dec 9, 2024
 *      Author: Admin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define NUM_OF_TIMERS 	2  				// Number of Timers to use

extern int TIME_CYCLE;					// Time cycle

extern int timer_flag[NUM_OF_TIMERS];

void setTimer(int index, int duration);
void clearTimer(int index);
void timerRun();

#endif /* INC_TIMER_H_ */
