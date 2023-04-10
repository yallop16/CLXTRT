/*
 * RS_232.h
 *
 *  Created on: Nov 3, 2020
 *      Author: Admin
 */

#ifndef INC_RS_232_H_
#define INC_RS_232_H_

#define uart0 1
#define uart2 2
#define both 3

void rs232_init(uint8_t select);
void UART0_init(void);
void UART2_init(void);



#endif /* INC_RS_232_H_ */
