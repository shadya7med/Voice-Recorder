/*
 * MAX7219_Interface.h
 *
 *  Created on: Apr 20, 2020
 *      Author: shady
 */

#ifndef MAX7219_INTERFACE_H_
#define MAX7219_INTERFACE_H_

#define DIG_IN_USE				  4

#define ON                        1
#define OFF                       0

#define SS_PIN					  PIN4
#define MOSI_PIN				  PIN5
#define MISO_PIN				  PIN6
#define SCK_PIN					  PIN7

#define MAX7219_MODE_DECODE       0x09
#define MAX7219_MODE_INTENSITY    0x0A
#define MAX7219_MODE_SCAN_LIMIT   0x0B
#define MAX7219_MODE_POWER        0x0C
#define MAX7219_MODE_TEST         0x0F
#define MAX7219_MODE_NOOP         0x00

// I only have 3 digits, no point having the
// rest. You could use more though.
#define MAX7219_DIGIT0            0x01
#define MAX7219_DIGIT1            0x02
#define MAX7219_DIGIT2            0x03
#define MAX7219_DIGIT3            0x04

#define MAX7219_CHAR_BLANK        0xF
#define MAX7219_CHAR_NEGATIVE     0xA

void MAX7219_Init(void);
void MAX7219_Load1(void);
void MAX7219_Load0(void);
void MAX7219_writeData(u8 data_register, u8 data);
void MAX7219_clearDisplay();
void MAX7219_displayNumber(volatile long number) ;

#endif /* MAX7219_INTERFACE_H_ */
