/*
 * hw.h
 *
 *  Created on: Jul 28, 2021
 *      Author: yallo
 */

#ifndef INC_HW_H_
#define INC_HW_H_

//Sensor
#define sensor              GPIO_PORTN_BASE
#define proximity_enter     GPIO_PIN_0
#define proximity_orient    GPIO_PIN_1



void hw_init();

void hw_proximity_init();
void hw_recall();
void Orientator();

void wait_up();
void wait_up2();

#endif /* INC_HW_H_ */
