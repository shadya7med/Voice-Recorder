/*
 * RAM_INT.h
 *
 *  Created on: Apr 15, 2020
 *      Author: shady
 */

#ifndef RAM_INT_H_
#define RAM_INT_H_

#define RAM_ADRH_PORT				PORTD
#define RAM_ADRL_PORT				PORTD
#define RAM_DATA_PORT				PORTC
#define RAM_CTRL_PORT				PORTA
#define RAM_ADR_PORT_REG			PORTD_register
#define RAM_DATA_READ_REG			PINC_register

#define ADR_16_PIN			PIN7
#define	ADR_13_5_PIN		PIN1
#define OE1_PIN				PIN4
#define WE1_PIN				PIN5
#define CE1_PIN				PIN6
#define LE_PIN				PIN3

/*RAM Functions */
void RAM_PinsInitailize ();
void RAM_WriteData(u32 RamAddress,u8 Data);
u8 RAM_ReadData(u32 RamAddress);

#endif /* RAM_INT_H_ */
