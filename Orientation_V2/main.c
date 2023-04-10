
#include "include.h"
//USER-DEFINED
#include "hw.h"
#include "stepper_driver.h"
#include "controller.h"
#include "inc/global_var.h"


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
// Orientation Module v2.0 dated 29/07/2021.
// Author : Khaleel
//
//*****************************************************************************





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
    hw_init();


    while(1)//;

    {
//        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,GPIO_PIN_2);
//        SysCtlDelay(8000000);
//        GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,0X00);
//        SysCtlDelay(8000000);
//
//        Stepper_CW(50);
        controller();
    }


}

