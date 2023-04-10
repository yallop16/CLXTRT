
#include "include.h"

//USER-DEFINED
#include "hw.h"
#include "controller.h"
#include "inc/dbg.h"


//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


//*****************************************************************************
//
// Master Module v2.0
// Author : Khaleel
//
//*****************************************************************************

uint32_t g_ui32SysClock;



int main(void)
{
    //
    // Run from the PLL at 120 MHz.
    // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
    // later to better reflect the actual VCO speed due to SYSCTL#22.
    //
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN |
                                             SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480), 120000000);


    /*All hardware peripheral initialization*/
    //Timer0_init();  // Timer init
    hw_init();
    dbg_printf("\nhardware initiated...");

    while(1)//;

    {
        controller();
    }


}

//void Timer0_init()
//{
//    // Enable timer module 0
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//
//
//    // Configure timer module 0 to periodic mode and enable interrupts
//    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
//    TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock); // set timer period to 1 second
//    IntEnable(INT_TIMER0A);
//    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
//
//
//    // Start timer module 0
//    TimerEnable(TIMER0_BASE, TIMER_A);
//}
