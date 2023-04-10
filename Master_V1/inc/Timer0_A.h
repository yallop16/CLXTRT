/*
 * Timer0_A.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Admin
 */

#ifndef INC_TIMER0_A_H_
#define INC_TIMER0_A_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

//*****************************************************************************
//
// System clock rate in Hz.
//
//*****************************************************************************


bool Timer_init(unsigned short usTim1Timerout50us);
void TimersEnable(  );
void TimersDisable(  );
void Timer0IntHandler(void);

#endif /* INC_TIMER0_A_H_ */
