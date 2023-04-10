/*
 * modbus.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Admin
 */

#ifndef INC_MODBUS_H_
#define INC_MODBUS_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
//#include "drivers/pinout.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"


#define SlaveID 0
//uint8_t SlaveID = 0;

//#define MAX485_TX_ENABLE  1  // EIA-485 transmit control pin
//#define MAX485_RX_ENABLE  1  // EIA-485 transmit control pin

static const uint8_t ku8MBSuccess = 0x00;
static const uint8_t ku8MBResponseTimedOut = 0xE2;
static const uint8_t ku8MBInvalidCRC = 0xE3;

uint16_t get_ResponseBuffer(uint8_t);
uint8_t read_HoldingRegisters(uint16_t, uint16_t);
uint8_t test_writingRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty);
uint8_t writeMultipleRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty);

uint8_t _u8MBSlave; ///< Modbus slave (1..255) initialized in begin()
uint16_t _u16ReadAddress; ///< slave register from which to read
uint16_t _u16ReadQty; ///< quantity of words to read

static const uint8_t ku8MBReadHoldingRegisters = 0x03; ///< Modbus function 0x03 Read Holding Registers
static const uint8_t ku8MBWriteSingleRegisters = 0x06; // modbus writing single register function 0x06
static const uint8_t ku8MBWriteMultipleRegisters = 0x10; // modbus writing single register function 0x06
static const uint16_t ku16MBResponseTimeout = 2000; ///< Modbus timeout [milliseconds]

void preTransmission();
void postTransmission();
void ModbusMaster_begin();
void ModbusMaster_assign(uint8_t identity);
uint8_t ModbusMasterTransaction(uint8_t);
uint8_t ModbusMasterTransaction_m(uint8_t u8MBFunction);
static uint16_t crc16_update(uint16_t , uint8_t );

  uint8_t u8ModbusADU[50], u8ModbusADU2[50];
  //uint8_t u8ModbusADUSize = 0;
  uint8_t i, u8Qty;
  uint16_t u16CRC;
  uint32_t u32StartTime;
  uint8_t u8BytesLeft;
  uint8_t u8MBStatus;




#endif /* INC_MODBUS_H_ */
