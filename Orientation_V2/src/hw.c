/*
 * hw.c
 *
 *  Created on: Jul 28, 2021
 *      Author: yallo
 */

#include "inc/include.h"
#include "inc/global_var.h"

//user defined
#include "RS_232.h"
#include "bicolor.h"
#include "modbus.h"
#include "stepper_driver.h"
#include "hw.h"
#include "pneumatic.h"
#include "millis.h"

#define channel1 1
#define channel2 2
#define channel3 3
#define channel4 4

uint8_t channelizer_pos = 1;
uint8_t pod_tilt_flag ;
uint8_t pod_Channel_flag ;
uint8_t R_orient=0, L_orient=1;
uint8_t tilterTask_Success ;
uint8_t Servo_homing;

uint32_t count1=0;
volatile uint32_t curr_millis_tilter , prev_millis_tilter=0;
volatile uint32_t milliseconds;

void SysTickIntHandler(void)
    {
        // Update the Systick interrupt counter.
        milliseconds++;
    }

uint32_t millis(void)
    {
        return milliseconds;
    }

void Systick_init()
    {
        SysTickPeriodSet(g_ui32SysClock / 1000); // Set SysTick period to 1ms
        IntMasterEnable();
        SysTickIntRegister(SysTickIntHandler);
        SysTickIntEnable(); // Enable SysTick interrupt
        SysTickEnable(); // Enable SysTick
    }


void PortNIntHandler()
{
    uint32_t state;
    state = GPIOIntStatus(GPIO_PORTN_BASE, true);

   switch(state){
    case 1:
                GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_0);
                pod_Channel_flag = 1;

                if(channelizer_pos == 4)
                     {
                         channelizer_pos = 0;
                     }
                     channelizer_pos++;
    break;
/***************************************************************************/
    case 2:
                  GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_1);
                  pod_tilt_flag = 1;
                  //GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,GPIO_PIN_0);
    break;
   }//Switch case end

}//ISR end

void hw_proximity_init()
{
    GPIOPinTypeGPIOInput(sensor, proximity_enter);
    GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    //interrupt settings
    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_0,GPIO_FALLING_EDGE);
    //GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_0);


    GPIOPinTypeGPIOInput(sensor, proximity_orient);
    GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    //interrupt settings
    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_1,GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_1);


}





void hw_pneumatic_init()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}



void hw_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); //Port C LED's
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); //Pneumatics and contactor
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); //Port E LED's
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH); //Stepper motor
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); //Proximity
  //  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL); //Encoder

    Systick_init();
    rs232_init(both);
    bicolor_init();

    //Sensor Init
    hw_proximity_init();

    //Pneumatic init
    hw_pneumatic_init();

    //Servo Init
    stepper_init();


}

void hw_recall()
{
         if(pod_tilt_flag == 1)
             {
          count1 =1; //flag_up
          tilterTask_Success =0; // not completed the orienation task

//          Orientator();
//          pod_tilt_flag=0;
          prev_millis_tilter = millis();
          pod_tilt_flag=0;
             }


         //if( millis() - curr_millis_tilter >= 100 && tilterTask_Success == 0)
          if(millis() - prev_millis_tilter>= 100 && tilterTask_Success == 0)
             {
                  //GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, ~GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2));

                  Orientator();

                  //pod_tilter_up();
                  prev_millis_tilter = millis();
                  tilterTask_Success = 1;
                  Servo_homing = 1;
             }
          if(millis() - prev_millis_tilter>= 500 && Servo_homing == 1)
          {
              Homing();
              prev_millis_tilter = millis();//reset the previous millis variable
          }


         if(pod_Channel_flag == 1)
             {

                switch(channelizer_pos)
                      {
                      case channel1 :
                              //Pause();
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0x00);
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,0x00);
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0x00);
                          break;

                      case channel2 :
                              channelizer_fwd();
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_PIN_6);
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x00);
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,0x00);
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0x00);
                          break;

                      case channel3 :
                              //Pause();
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,GPIO_PIN_0);
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x00);
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0x00);
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,0x00);
                          break;

                      case channel4 :
                              channelizer_rev();
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2,GPIO_PIN_2);
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x00);
                              GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,0x00);
                              GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_0,0x00);
                          break;


                      }//switch

                 }//pod_Channel_flag

}

void wait_up()
{
    //1 sec of processing delay
    SysCtlDelay(8000000);
}

void wait_up2()
{
    //0.5 sec of processing delay
    SysCtlDelay(8000000/2);
}

void Orientator()
{

    if (R_orient == 1 && count1 == 1)//
    {
        //Rotate Clockwise
        Stepper_CCW();
        ////////////////
        R_orient =0;
        L_orient =1;
        count1 = 0;

    }

    if (L_orient == 1 && count1 == 1)//
    {
       //Rotate Counter Clockwise
        Stepper_CW();
        ////////////////
                R_orient =1;
                L_orient =0;
                count1 = 0;

    }
   // GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, ~GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2));

}
