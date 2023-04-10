/*
 * pneumatic.c
 *
 *  Created on: Jul 1, 2021
 *      Author: yallo
 */
//#include <stdint.h>
//#include <stdbool.h>
//#include "inc/hw_ints.h"
//#include "inc/hw_types.h"
//#include "inc/hw_memmap.h"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.h"
#include "include.h"
#include "pneumatic.h"

void Pneumatic_init()
{

       GPIOPinTypeGPIOOutput(pneumatic, pod_reject_chute|pod_accept_chute|pod_tilter|pod_chanelliser);
}

void pod_accept_on()
{
    GPIOPinWrite(pneumatic, pod_accept_chute,pod_accept_chute);
}

void pod_accept_off()
{
    GPIOPinWrite(pneumatic, pod_accept_chute,0x00);
}

void pod_reject_on()
{
    GPIOPinWrite(pneumatic, pod_reject_chute,pod_reject_chute);
}

void pod_reject_off()
{
    GPIOPinWrite(pneumatic, pod_reject_chute,0x00);
}

void pod_tilter_up()
{
    GPIOPinWrite(pneumatic, pod_tilter,pod_tilter);
}

void pod_tilter_down()
{
    GPIOPinWrite(pneumatic, pod_tilter,0x00);
}

void channelizer_fwd()
{
    GPIOPinWrite(pneumatic, pod_chanelliser,pod_chanelliser);
}

void channelizer_rev()
{
    GPIOPinWrite(pneumatic, pod_chanelliser,0x00);
}
