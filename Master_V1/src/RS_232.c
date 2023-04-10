/*
 * RS_232.c
 *
 *  Created on: Nov 3, 2020
 *      UART0 and UART2 are initialized in this source file.
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "inc/RS_232.h"
#include "inc/dbg.h"

/********************************************************************************************
 * select 0: UART0 is initialized for debugging.
 * select 1: UART2 is initialized for RS485(MODBUS) COMMUNICATION
 * select 2: Both UART0 and UART2 is initialized for debugging and board2board communication.
 * ******************************************************************************************/

void rs232_init(uint8_t select)
{

switch (select)
{
    case 1: //UART0 initialization for debugging
    UART0_init();

    break;

    case 2: //UART2 initialization for board 2 board communication
    UART2_init();
    break;

    case 3: //Both UART0 and UART2 is initialized for debugging and board2board communication.
    UART0_init();
    UART2_init();
    break;

}
dbg_printf("RS232 initialized - UART0-(EN) | UART2-(EN)");
}

void UART0_init(void)
{
       //
       // Enable the peripherals used by this example.
       //
       ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
       ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

       IntMasterEnable();
       //
       // Set GPIO A0 and A1 as UART pins.
       //
       GPIOPinConfigure(GPIO_PA0_U0RX);
       GPIOPinConfigure(GPIO_PA1_U0TX);
       GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

       // Use the internal 16MHz oscillator as the UART clock source.
       //
       UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
       //

       // Configure the UART for 115,200, 8-N-1 operation.
       //
       UARTConfigSetExpClk(UART0_BASE, 16000000, 115200,
                                   (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));
       IntEnable(INT_UART0);
       UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

       UARTEnable(UART0_BASE);

}

void UART2_init(void)
{
    //
       // Enable GPIO port A which is used for UART0 pins.
       // TODO: change this to whichever GPIO port you are using.
       //
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

       //
       // Configure the pin muxing for UART0 functions on port A0 and A1.
       // This step is not necessary if your part does not support pin muxing.
       // TODO: change this to select the port/pin you are using.
       //
       GPIOPinConfigure(GPIO_PA6_U2RX);
       GPIOPinConfigure(GPIO_PA7_U2TX);

       //
       // Enable UART0 so that we can configure the clock.
       //
       SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);

       //
       // Use the internal 16MHz oscillator as the UART clock source.
       //
       UARTClockSourceSet(UART2_BASE, UART_CLOCK_PIOSC);

       //
       // Select the alternate (UART) function for these pins.
       // TODO: change this to select the port/pin you are using.
       //
       GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);

       //
       // Initialize the UART for console I/O.
       //
       UARTStdioConfig(2, 19200, 16000000);
}
