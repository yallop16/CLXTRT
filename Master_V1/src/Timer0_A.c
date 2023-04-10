/*
 * Timer0_A.c
 *
 *  Created on: Dec 13, 2020
 *      Author: Admin
 */

#include <modbus_old.bak>
#include "Timer0_A.h"

//unsigned short usMBMulDiv(unsigned short a, unsigned short b, unsigned short c);
//
///* ----------------------- Persistent variable ------------------------------*/
unsigned short usDelta;
/* ----------------------- Start implementation -----------------------------*/
unsigned short usMBMulDiv(unsigned short a, unsigned short b, unsigned short c)
{
    unsigned long x;
    x = a;
    x *= b;
    x /= c;
    return (unsigned short) x;
}

bool
Timer_init(unsigned short usTim1Timerout50us)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerClockSourceSet(TIMER0_BASE, TIMER_CLOCK_PIOSC);
 //   TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
//    usDelta = usMBMulDiv(usTim1Timerout50us, 800, 100);//200
    usDelta = ((usTim1Timerout50us*SysCtlClockGet())/20000)-1;
    IntMasterEnable();
//    IntEnable(INT_TIMER0A);//inc/hw_ints.h header defines
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);//select timer source// TIMEOUT interrupt

    return true;
}

void TimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */

//   TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock/3);
   TimerLoadSet(TIMER0_BASE, TIMER_A, usDelta);
   TimerEnable(TIMER0_BASE, TIMER_A);
   TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
   TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

void TimersDisable(  )
{
    /* Disable any pending timers. */

    TimerDisable(TIMER0_BASE,TIMER_A);
    TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

void Timer0IntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //(void)pxMBPortCBTimerExpired();
    u8MBStatus = ku8MBResponseTimedOut;
}


