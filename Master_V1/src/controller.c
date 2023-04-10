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
#include "inc/modbus.h"
#include "include.h"
#include "global_var.h"
#include "inc/RS_232.h"
//#include "inc/encoder.h"
#include "inc/pneumatic.h"
//#include "inc/sccb.h"
//#include "inc/ov7725.h"
#include "inc/stepper_driver.h"
#include "inc/hw.h"
#include "inc/millis.h"

//void Orientator();


uint8_t conveyor = 1;
uint8_t good_chilli = 1, bad_chilli=0;
uint8_t entry_sensor;
uint8_t chilli_pod_detected = 1;
uint8_t R_orient=0, L_orient=1;
uint8_t pod_tilt_flag;
uint32_t count1=0;



uint8_t controller ()
{

    while(1)
    {
          hw_recall();


          //Serial_routine();
    }//while(true)
}//controller



uint8_t Start_Sequence()
{
    //Power Relay initialize
    hw_Raw_relay1_ON();
    hw_Raw_relay2_ON();

    //X time to settle Relay's- Approx 10 second
    delay_ms(5000);

    //Split Conveyor is started
    hw_contactor3_ON();
    //X time to switch on the VFD3 and settle down- 10 seconds
    delay_ms(1000);
    ModbusMaster_assign(12);
    delay_ms(500);
    //hw_conveyor_stop();
    //delay(10)
    hw_conveyor_forward();

    hw_contactor2_ON();
    //X time to switch on the VFD3 and settle down- 10 seconds
    delay_ms(1000);
    ModbusMaster_assign(11);
    delay_ms(500);
    //hw_conveyor_stop();
    //delay(10)
    hw_conveyor_forward();


    ModbusMaster_assign(0);
    Singularizer_connect(); //connect the stepper motor modules
    //X time to settle servo driver - 10 second
    delay_ms(500);
    Singularizer_run();    // run the stepper motor at 240 rpm
    //X time to ramp up the stepper motor to its max speed
    delay_ms(10000);

    hw_contactor1_ON();
    //X time to switch on the VFD3 and settle down- 10 seconds
    delay_ms(2000);
    ModbusMaster_assign(10);
    delay_ms(500);
    //hw_conveyor_stop();
    //delay(10)
    hw_conveyor_forward();

    //Servo Amplifiers ON
    hw_contactor4_ON(); //Servo Power supply ON

    hw_green_lamp_ON();

    return(1);
}

uint8_t Stop_Sequence()
{
    //Hopper Stopping
    ModbusMaster_assign(10);
    hw_conveyor_stop();
     //X time to switch off the VFD3 and settle down- 10 seconds
    delay_ms(3000);
    hw_contactor1_OFF();
    delay_ms(1000);

    //Stop the Linear Drives
    hw_elevator_stop();
    delay_ms(1000);

    //Singilarizer Stop
    ModbusMaster_assign(0);
    Singularizer_stop();
    Singularizer_disconnect();
    delay_ms(2000);

    //Main Conveyor Stop
    ModbusMaster_assign(11);
    hw_conveyor_stop();
    //X time to switch off the VFD3 and settle down- 10 seconds
    delay_ms(3000);
    hw_contactor2_OFF();
    delay_ms(1000);

    //Split Conveyor Stop
    ModbusMaster_assign(12);
    hw_conveyor_stop();
    //X time to switch off the VFD3 and settle down- 10 seconds
    delay_ms(3000);
    hw_contactor3_OFF();


    delay_ms(3000);
    //Power Shutdown
    hw_Raw_relay1_OFF();
    hw_Raw_relay2_OFF();

    return(1);

}
