/*
 * hw.h
 *
 *  Created on: Jul 28, 2021
 *      Author: yallo
 */

#ifndef INC_HW_H_
#define INC_HW_H_

//Sensor
#define hw_start           GPIO_PORTQ_BASE
#define reset              GPIO_PORTN_BASE
#define feedback           GPIO_PORTN_BASE
#define hard_reset         GPIO_PIN_0
#define feedback_cont1     GPIO_PIN_1
#define feedback_cont2     GPIO_PIN_2
#define feedback_cont3     GPIO_PIN_3
#define feedback_cont4     GPIO_PIN_4
#define feedback_cont5     GPIO_PIN_5
#define hw_start_pin       GPIO_PIN_1
//#define proximity_enter     GPIO_PIN_0
//#define proximity_orient    GPIO_PIN_1
#define green_Lamp  GPIO_PIN_0
#define red_Lamp    GPIO_PIN_2
#define raw_Relay1  GPIO_PIN_3
#define raw_Relay2  GPIO_PIN_4
#define Contactor1  GPIO_PIN_2
#define Contactor2  GPIO_PIN_0
#define Contactor3  GPIO_PIN_1
#define Contactor4  GPIO_PIN_3
#define Contactor5  GPIO_PIN_4
#define elevator1   GPIO_PIN_5//D5
#define elevator2   GPIO_PIN_6//D6
#define elevator3   GPIO_PIN_4//Q4
#define Leveler     GPIO_PIN_0//L0

void hw_init();
void hw_hard_reset_init();
void hw_Start_Stop_init();
void hw_proximity_init();

void hw_Linear_drive_init();
void hw_elevator_start();
void hw_elevator_stop();

void hw_Raw_relay_init();
void hw_Raw_relay1_ON();
void hw_Raw_relay2_ON();
void hw_Raw_relay1_OFF();
void hw_Raw_relay2_OFF();

void hw_contactor_init();
void hw_contactor1_ON();
void hw_contactor2_ON();
void hw_contactor3_ON();
void hw_contactor4_ON();
void hw_contactor5_ON();
void hw_contactor1_OFF();
void hw_contactor2_OFF();
void hw_contactor3_OFF();
void hw_contactor4_OFF();
void hw_contactor5_OFF();

void hw_towerlamp_init();
void hw_green_lamp_ON();
void hw_red_lamp_ON();
void hw_green_lamp_OFF();
void hw_red_lamp_OFF();

void hw_conveyor_forward();
void hw_conveyor_reverse();
void hw_conveyor_stop();
void Singularizer_connect();
void Singularizer_disconnect();
void Singularizer_run();
void Singularizer_stop();

void Timer0_init();

void wait_up();
void wait_up2();

void hw_recall();
uint8_t Start_Sequence();
uint8_t Stop_Sequence();

void removeBraces(char *str);
void processCommand();

#endif /* INC_HW_H_ */
