/*
 * pneumatic.h
 *
 *  Created on: Jul 1, 2021
 *      Author: yallo
 */

#ifndef INC_PNEUMATIC_H_
#define INC_PNEUMATIC_H_

//Pneumatics
#define pneumatic           GPIO_PORTD_BASE //base
#define pod_accept_chute    GPIO_PIN_1
#define pod_reject_chute    GPIO_PIN_0
#define pod_tilter          GPIO_PIN_2  //D2
#define pod_chanelliser     GPIO_PIN_3  //D3

void Pneumatic_init();
void pod_accept_on();
void pod_accept_off();
void pod_reject_on();
void pod_reject_off();
void pod_tilter_up();
void pod_tilter_down();
void channelizer_fwd();
void channelizer_rev();

#endif /* INC_PNEUMATIC_H_ */
