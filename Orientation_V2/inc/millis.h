/*
 * millis.h
 *
 *  Created on: Mar 13, 2023
 *      Author: yallo
 */

#ifndef INC_MILLIS_H_
#define INC_MILLIS_H_

extern volatile uint32_t milliseconds;

void SysTickIntHandler(void);
uint32_t millis(void);
void Systick_init();

#endif /* INC_MILLIS_H_ */
