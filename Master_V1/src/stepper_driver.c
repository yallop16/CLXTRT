/*
 * stepper_driver.c
 *
 *  Created on: Jul 12, 2021
 *      Author: yallo
 */

//#define TARGET_IS_TM4C129_RA1
//#include <stdint.h>
//#include <stdbool.h>
//#include "inc/hw_ints.h"
//#include "inc/hw_types.h"
//#include "inc/hw_memmap.h"
//#include "driverlib/gpio.h"
//#include "driverlib/sysctl.h"
#include "include.h"
#include "stepper_driver.h"
#include "hw.h"



void stepper_init()
{

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, right|left|Enable);  //Pin 4,5,6


}

//void step_dir(uint8_t dir)
//{
//    if(dir == 0)
//    GPIOPinWrite(GPIO_PORTH_BASE, stepper_dir,0x00);
//    else if (dir == 1)
//    GPIOPinWrite(GPIO_PORTH_BASE, stepper_dir,stepper_dir);
//}
//
//
//void step_pulse()
//{
//    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0,GPIO_PIN_0);
//    delayMs(50);
//    //delayUs(rpm_t);
//    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_0,0x00);
//    delayMs(50);
//   // delayUs(rpm_t);
//}

void Stepper_CW()
{//uint32_t count=0;
//    step_dir(cw);
//    for(count = 0; count<steps;count++)
//                    {
//
//                        step_pulse();
//                    }
    left_turn();
               wait_up();
               enable_servo();
               wait_up2();
               disable_servo();
               no_left_turn();
}

void Stepper_CCW()
{//uint32_t count=0;
//    step_dir(ccw);
//    for(count = 0; count<steps;count++)
//                    {
//
//                        step_pulse();
//                    }

           right_turn();
           wait_up();
           enable_servo();
           wait_up2();
           disable_servo();
           no_right_turn();
}

void delayMs(uint32_t ui32Ms) {

    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000

    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}

void delayUs(uint32_t ui32Us) {
    SysCtlDelay(ui32Us * (SysCtlClockGet() / 3 / 1000000));
}


void enable_servo()
{
    GPIOPinWrite(GPIO_PORTD_BASE, Enable,Enable);
}

void disable_servo()
{
    GPIOPinWrite(GPIO_PORTD_BASE, Enable,0x00);
}

void right_turn()
{
    GPIOPinWrite(GPIO_PORTD_BASE, right,right);
}

void no_right_turn()
{
    GPIOPinWrite(GPIO_PORTD_BASE, right,0x00);
}

void left_turn()
{
    GPIOPinWrite(GPIO_PORTD_BASE, left,left);
}

void no_left_turn()
{
    GPIOPinWrite(GPIO_PORTD_BASE, left,0x00);
}

void Homing()
{
    enable_servo();
    right_turn();
    left_turn();

    wait_up();
    disable_servo();
    no_left_turn();
    no_right_turn();

}
