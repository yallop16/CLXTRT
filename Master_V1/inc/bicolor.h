/*
 * bicolor.h
 *
 *  Created on: Sep 29, 2020
 *      Author: Admin
 */

#ifndef DRIVERS_BICOLOR_H_
#define DRIVERS_BICOLOR_H_

#define HIGH 0x01
#define LOW 0x00

#define led1_1_LO() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,LOW);
#define led1_1_HI() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,HIGH);

#define led1_2_LO() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,LOW);
#define led1_2_HI() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,HIGH);

#define led2_1_LO() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,LOW);
#define led2_1_HI() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6,HIGH);

#define led2_2_LO() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,LOW);
#define led2_2_HI() GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7,HIGH);

#define led3_1_LO() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,LOW);
#define led3_1_HI() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0,HIGH);

#define led3_2_LO() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,LOW);
#define led3_2_HI() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1,HIGH);

#define led4_1_LO() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,LOW);
#define led4_1_HI() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2,HIGH);

#define led4_2_LO() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,LOW);
#define led4_2_HI() GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3,HIGH);

void bicolor_init(void);



#endif /* DRIVERS_BICOLOR_H_ */
