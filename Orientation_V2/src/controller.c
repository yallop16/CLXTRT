/*
 * controller.c
 *
 *  Created on: Jul 1, 2021
 *      Author: yallo
 */
//#define TARGET_IS_TM4C129_RA1
//#include <stdint.h>
//#include <stdbool.h>
//#include "inc/hw_ints.h"
//#include "inc/hw_types.h"
//#include "inc/hw_memmap.h"
//#include "inc/hw_udma.h"
//#include "inc/hw_ssi.h"
//#include "driverlib/debug.h"
//#include "driverlib/gpio.h"
//#include "driverlib/qei.h"
//#include "driverlib/interrupt.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/rom.h"
//#include "driverlib/rom_map.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/udma.h"
//#include "driverlib/ssi.h"
//#include "driverlib/uart.h"
//#include "utils/uartstdio.h"
#include "include.h"
#include "global_var.h"
#include "inc/RS_232.h"
#include "inc/pneumatic.h"
//#include "inc/sccb.h"
//#include "inc/ov7725.h"
#include "inc/stepper_driver.h"
#include "inc/modbus.h"
#include "hw.h"

void Orientator();


uint8_t conveyor = 1;
uint8_t good_chilli = 1, bad_chilli=0;
uint8_t entry_sensor;
uint8_t chilli_pod_detected = 1;

//uint8_t pod_tilt_flag ;




uint8_t controller ()
{


    while(1){

   //camera pulse, if chilli is detected. It can be accept pulse/reject pulse
        /*
    if (chilli_pod_detected == 1)
        {
            if(good_chilli == 1)//chilli accepted
            {
                pod_accept_on();
                wait_up2();
                pod_accept_off();
                wait_up2();
            }//if(good_chilli == 1)
            else if (bad_chilli == 1)//chilli rejected
            {
                pod_reject_on();
                wait_up2();
                pod_reject_off();
                wait_up2();

            }//else if (bad_chilli == 1)
        }//if (chilli_pod_detected == 1)
        */
    //Homing_Servo_Orientation();
        hw_recall();



    }//while(true)
}//controller


