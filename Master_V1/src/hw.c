/*
 * hw.c
 *
 *  Created on: Jul 28, 2021
 *      Author: yallo
 */

#include "inc/modbus.h"
#include "inc/include.h"
#include "inc/global_var.h"

//user defined
#include "RS_232.h"
#include "bicolor.h"
#include "stepper_driver.h"
#include "hw.h"
#include "pneumatic.h"
#include "millis.h"

#define StartSequence 1
#define StopSequence  1

uint8_t m=0;
uint8_t i2=0, j2=0, frame_char;
uint8_t emergency_reset=0;
uint8_t systemState  ;
uint8_t systemUp = 0;
bool frame_rcvd=1;
volatile unsigned char str[100];
uint32_t str2int ;
extern uint32_t g_ui32SysClock;
volatile uint32_t milliseconds;

uint32_t curr_millis_tilter, prev_millis_tilter=0;

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
        //SysTickPeriodSet(g_ui32SysClock / 1000); // Set SysTick period to 1ms
        SysTickPeriodSet(120000000 / 1000); // Set SysTick period to 1ms
        IntMasterEnable();
        SysTickIntRegister(SysTickIntHandler);
        SysTickIntEnable(); // Enable SysTick interrupt
        SysTickEnable(); // Enable SysTick
    }

void
Timer0AIntHandler(void)
{
    //
    // Clear the timer interrupt flag.
    //
   // TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
}

void PortQIntHandler()
{
//        uint32_t Q_state;
//        Q_state = GPIOIntStatus(GPIO_PORTQ_BASE, true);

//        switch(Q_state)
//        {
//        case 2 :
//            GPIOIntClear(GPIO_PORTQ_BASE, GPIO_INT_PIN_1);
////            hw_green_lamp_ON();
//            hw_red_lamp_ON();
//            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
//            systemState = 1;
//         break;
//
//        case 3 :
//            GPIOIntClear(GPIO_PORTQ_BASE, GPIO_INT_PIN_2);
//            hw_green_lamp_ON();
//            GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x00);
//            systemState = 2;
//        break;
//        }
}

void
UART0IntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = MAP_UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    MAP_UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(MAP_UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //


    j2 = UARTCharGetNonBlocking(UART0_BASE);

        str[i2] =j2;
        i2++;


 //  dbg_printf("data rcvd is : %c \n", j2);
//    dbg_printf("data rcvd is : %c \n", str[i]);

    if (j2=='}' )
    {
        frame_rcvd=1;
        i2=0;
        j2=0;
        processCommand();
    }

    }
}

void PortNIntHandler()
{
    uint32_t state;
    state = GPIOIntStatus(GPIO_PORTN_BASE, true);

   switch(state){
    case 1:     //Hardware Reset
                GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_0);
                //GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
                hw_red_lamp_ON();
               // GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1,GPIO_PIN_1);
               //wait_up2();
               // GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1,0x00);
                emergency_reset = 1;

     break;

    case 2:       //Hard Start
                  GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_1);
                  GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);

                  hw_Raw_relay1_ON();
                  hw_Raw_relay2_ON();
                  systemState = 1;
    break;

    case 4:       //Hard Stop
                  GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_2);
                  GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x00);
                  hw_green_lamp_OFF();

                  systemState = 2;
    break;
   }
//        if(state & GPIO_INT_PIN_0)
//         {
//            GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_0);
//            //GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
//            hw_red_lamp_ON();
//            emergency_reset = 1; //Emergency Stop
//         }
//
//        if(state & GPIO_INT_PIN_1)
//         {
//             GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_1);
//             GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,GPIO_PIN_4);
//             systemState = 1; //System Start
//         }
//
//         if(state & GPIO_INT_PIN_2)
//         {
//             GPIOIntClear(GPIO_PORTN_BASE, GPIO_INT_PIN_2);
//             GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,0x00);
//             systemState = 2; //System Stop
//         }

}

void hw_hard_reset_init()
{
    GPIOPinTypeGPIOInput(reset, hard_reset);
    GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    //interrupt settings
    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_0,GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_0);


//    GPIOPinTypeGPIOInput(sensor, proximity_orient);
//    GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
//    //interrupt settings
//    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_1,GPIO_FALLING_EDGE);
//    GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
//    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_1);

    dbg_printf("\nHard-Reset Enable");
}

void hw_Start_Stop_init()
{
    GPIOPinTypeGPIOInput(GPIO_PORTN_BASE, GPIO_INT_PIN_1 |GPIO_INT_PIN_2);
    GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_INT_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_INT_PIN_2,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    //interrupt settings
    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_INT_PIN_1,GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_1);

    //GPIOPinTypeGPIOInput(GPIO_PORTQ_BASE, GPIO_PIN_2 );
    //GPIOPadConfigSet(GPIO_PORTQ_BASE,GPIO_PIN_2,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_2,GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_2);


    dbg_printf("\nHard-Start-Stop Enable");
}

//input_init()
//{
//
//}

void hw_Contactor_feedback_init()
{
//    GPIOPinTypeGPIOInput(feedback, feedback_cont1|feedback_cont2|feedback_cont3|feedback_cont4|feedback_cont5);
//    GPIOPadConfigSet(GPIO_PORTN_BASE,feedback_cont1|feedback_cont2|feedback_cont3|feedback_cont4|feedback_cont5,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    //interrupt settings
//    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_0,GPIO_FALLING_EDGE);
//    GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
//    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_0);


//    GPIOPinTypeGPIOInput(sensor, proximity_orient);
//    GPIOPadConfigSet(GPIO_PORTN_BASE,GPIO_PIN_1,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
//    //interrupt settings
//    GPIOIntTypeSet(GPIO_PORTN_BASE,GPIO_PIN_1,GPIO_FALLING_EDGE);
//    GPIOIntRegister(GPIO_PORTN_BASE,PortNIntHandler);
//    GPIOIntEnable(GPIO_PORTN_BASE, GPIO_INT_PIN_1);


}

/********************************Linear Drive****************************************/

void hw_Linear_drive_init()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, elevator1|elevator2);
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, elevator3);
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, Leveler);
}

void hw_elevator_start()
{
    GPIOPinWrite(GPIO_PORTD_BASE,elevator1,elevator1);
    GPIOPinWrite(GPIO_PORTD_BASE,elevator2,elevator2);
    GPIOPinWrite(GPIO_PORTL_BASE,Leveler,Leveler);
    GPIOPinWrite(GPIO_PORTQ_BASE,elevator3,elevator3);
}

void hw_elevator_stop()
{
    GPIOPinWrite(GPIO_PORTD_BASE,elevator1,0x00);
    GPIOPinWrite(GPIO_PORTD_BASE,elevator2,0x00);
    GPIOPinWrite(GPIO_PORTL_BASE,Leveler,0x00);
    GPIOPinWrite(GPIO_PORTQ_BASE,elevator3,0x00);
}

/*****************************Relay*************************************************/
void hw_Raw_relay_init()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, raw_Relay1|raw_Relay2);
    dbg_printf("\nHardware Relays initiated...");
}

void hw_Raw_relay1_ON()
{
    GPIOPinWrite(GPIO_PORTF_BASE,raw_Relay1,raw_Relay1); // Relay1 on
    dbg_printf("\nHardware Relay1 Activated.");
}

void hw_Raw_relay2_ON()
{
    GPIOPinWrite(GPIO_PORTF_BASE,raw_Relay2,raw_Relay2); // Relay2 on
    dbg_printf("\nHardware Relay2 Activated.");
}

void hw_Raw_relay1_OFF()
{
    GPIOPinWrite(GPIO_PORTF_BASE,raw_Relay1,0x00); // Relay1 off
}

void hw_Raw_relay2_OFF()
{
    GPIOPinWrite(GPIO_PORTF_BASE,raw_Relay2,0x00); // Relay1 off
}

/*************************************************************************************/

/**********************************Contactor******************************************/
void hw_contactor_init()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);

}

void hw_contactor1_ON()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor1,Contactor1); // Contactor1
}

void hw_contactor2_ON()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor2,Contactor2); // Contactor2
}

void hw_contactor3_ON()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor3,Contactor3); // Contactor3
}

void hw_contactor4_ON()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor4,Contactor4); // Contactor4
}

void hw_contactor5_ON()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor5,Contactor5); // Contactor5
}

void hw_contactor1_OFF()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor1,0x00); // Contactor
}

void hw_contactor2_OFF()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor2,0x00); // Contactor
}

void hw_contactor3_OFF()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor3,0x00); // Contactor
}

void hw_contactor4_OFF()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor4,0x00); // Contactor
}

void hw_contactor5_OFF()
{
    GPIOPinWrite(GPIO_PORTD_BASE,Contactor5,0x00); // Contactor
}

/************************************************************************************/



void hw_conveyor_forward()
{
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
    test_writingRegisters(8,4); // forward
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
}

void hw_conveyor_reverse()
{
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
    test_writingRegisters(8,2); // reverse
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
}

void hw_conveyor_stop()
{
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
    test_writingRegisters(8,0); // stop
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
}

void Singularizer_connect()
{
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
    test_writingRegisters(0,1);
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
}

void Singularizer_disconnect()
{
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
    test_writingRegisters(0,0);
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
}

void Singularizer_run()
{
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
    writeMultipleRegisters(37,3);
    SysCtlDelay(8000000);
    SysCtlDelay(8000000);
}

void Singularizer_stop()
{
        SysCtlDelay(8000000);
        SysCtlDelay(8000000);
        test_writingRegisters(25,5);
        SysCtlDelay(8000000);
        SysCtlDelay(8000000);
}

void hw_pneumatic_init()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}

void hw_towerlamp_init()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, red_Lamp|green_Lamp);
    dbg_printf("\nTower Lamps initialzed.");
}

void hw_green_lamp_ON()
{
    GPIOPinWrite(GPIO_PORTF_BASE,green_Lamp,green_Lamp); // green lamp on
    //dbg_printf("\nGreen Lamps Activated.");
}

void hw_red_lamp_ON()
{
    GPIOPinWrite(GPIO_PORTF_BASE,red_Lamp,red_Lamp); // red lamp on
    dbg_printf("\nRed Lamps Activated.");
}

void hw_green_lamp_OFF()
{
    GPIOPinWrite(GPIO_PORTF_BASE,green_Lamp,0x00); // green lamp off
}

void hw_red_lamp_OFF()
{
    GPIOPinWrite(GPIO_PORTF_BASE,red_Lamp,0x00); // red lamp off
}


void hw_init()
{

    //Peripheral Initialization
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC); //Port C LED's
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); //Pneumatics and contactor
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ); //Elevator
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); //Port E LED's
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //Port E Relay's
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH); //Stepper motor
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION); //Proximity
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL); //Encoder
    Systick_init();



    //Hardware Initialization

    rs232_init(both); //RS232 initialize - UART0 / UART2 Activated

    ModbusMaster_begin(); //modbus master init (VFD)

    bicolor_init();   //Bicolor LED's Initialized

    //input_init();

    //hw_proximity_init();

    hw_pneumatic_init();

    hw_hard_reset_init(); //Hard Reset Init

    hw_Start_Stop_init();           // Hard Start Init

    hw_towerlamp_init();       //Tower Lamp initialize

    hw_Raw_relay_init();       //Power Relay init

    hw_contactor_init();       //Switch on the contactor before VFD init

    hw_Linear_drive_init();    //Linear drive Initialize



    while(!systemState)
    {
     //dbg_printf("system state ON");
        processCommand();

    }

    if(systemState == 1)
    {
        #if StartSequence
              Start_Sequence();
        #endif
        systemState = 0;

    }
    dbg_printf("{syson}");
}

void wait_up()
{
    //1 sec of processing delay
    //SysCtlDelay(8000000);
}

void wait_up2()
{
    //0.5 sec of processing delay
    //SysCtlDelay(8000000/2);
}

void delay_ms(uint32_t time_ms)
{
//    uint32_t current_time = millis(); // get the current time
//     uint32_t target_time = current_time + time_ms; // calculate the target time
//
//     while (millis() < target_time) {
//       // do nothing and wait until the target time is reached
//     }
    uint32_t start_time = millis();
     while (millis() - start_time < time_ms) {
       // do nothing, just wait
     }

}

void hw_recall()
{
    uint32_t value=0;

    value= GPIOPinRead(GPIO_PORTN_BASE,GPIO_PIN_0);
    if(emergency_reset == 1 || (value & GPIO_PIN_0)==0)
    {
        hw_green_lamp_OFF();
        wait_up();
        hw_green_lamp_ON();
        wait_up();

        emergency_reset =0;
    }


//System Shut-Down
    if(systemState == 2)
    {
        #if StopSequence
            Stop_Sequence();
            while(systemState == 2);
        #endif
    }

    //Uart Command Process
        processCommand();
}//Hardware recall


void removeBraces(char *str) {
    char *p = str;
    int len = strlen(str);
    int braces = 0;
    int i;

    for ( i = 0; i < len; i++) {
        if (str[i] == '{') {
            braces++;
        } else if (str[i] == '}') {
            braces--;
        } else {
            *p++ = str[i];
        }
    }

    *p = '\0';
}

void processCommand()
{
    //Command Processing
        if(frame_rcvd == 1)
        {
            removeBraces(str);
            //dbg_printf("frame_rcvd is : %s\n",str);
            str2int = atoi(str);
            dbg_printf("String to integer is : %d\n",str2int);
            frame_rcvd =0;
         // using memset
            memset(str, '\0', sizeof(str));

            switch(str2int)
            {
            case 1: //Soft Start
                //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,GPIO_PIN_2);
                systemState = 1;
            break;

            case 2: //Soft Stop
                //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,0x00);
                systemState = 2;
            break;

            case 3: //Emergency Reset
                //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,0x00);
                emergency_reset = 1;
                hw_Raw_relay1_OFF();
                hw_Raw_relay2_OFF();
            break;

            case 4: //Only Relay On
                //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,0x00);
                hw_Raw_relay1_ON();
                hw_Raw_relay2_ON();
            break;

            case 14: //Soft Stop
                //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,0x00);
                hw_contactor4_ON();
            break;

            case 24: //Soft Stop
                //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2,0x00);
                hw_contactor4_OFF();
            break;
            case 20:
                dbg_printf("{PING OK}");
            break;

            }
        }
}
