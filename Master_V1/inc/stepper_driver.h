/*
 * stepper_driver.h
 *
 *  Created on: Jul 12, 2021
 *      Author: yallo
 */

#ifndef INC_STEPPER_DRIVER_H_
#define INC_STEPPER_DRIVER_H_

#define cw 0
#define ccw 1
#define right   GPIO_PIN_4
#define left    GPIO_PIN_5
#define Enable  GPIO_PIN_6

void stepper_init();
//void step_pulse();
//void step_dir(uint8_t dir);
void enable_servo();
void disable_servo();
void right_turn();
void no_right_turn();
void left_turn();
void no_left_turn();
void Homing();
void Stepper_CW();
void Stepper_CCW();
void delayMs(uint32_t ui32Ms);
void delayUs(uint32_t ui32Us);

uint32_t rpm_t ;

#endif /* INC_STEPPER_DRIVER_H_ */
