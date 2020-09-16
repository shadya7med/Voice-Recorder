/*
 * MAX7219_FUNC.c
 *
 *  Created on: Apr 20, 2020
 *      Author: shady
 */
#include"STD_TYPES.h"
#include"BIT_CALC.h"
#include"util/delay.h"
#include"DIO_INT.h"
#include"SPI_Interface.h"
#include"SPI_Config.h"
#include"MAX7219_Interface.h"
//u8 Garbage = 0;
void MAX7219_Init(void)
{
	MAX7219_writeData(MAX7219_MODE_TEST,0x00);
	/*Decode Mode to Font Code-B*/
	MAX7219_writeData(MAX7219_MODE_DECODE,0xFF);
	/*Scan limit runs from 0*/
	MAX7219_writeData(MAX7219_MODE_SCAN_LIMIT,(DIG_IN_USE -1) );
	MAX7219_writeData(MAX7219_MODE_INTENSITY,8);
	MAX7219_writeData(MAX7219_MODE_POWER,ON);

}
void MAX7219_Load1(void)
{
	DIO_SetPinValue(PORTB,SS_PIN,HIGH);

}

void MAX7219_Load0(void)
{
	DIO_SetPinValue(PORTB,SS_PIN,LOW);

}

void MAX7219_writeData(u8 data_register, u8 data)
{
		MAX7219_Load0();
		_delay_ms(1);
        // Send the register where the data will be stored
		SPI_SendByte(data_register);
        // Send the data to be stored
		SPI_SendByte(data);
        MAX7219_Load1();
}

void MAX7219_clearDisplay()
{
    u8 i = DIG_IN_USE;
    // Loop until 0, but don't run for zero
    do {
        // Set each display in use to blank
        MAX7219_writeData(i, MAX7219_CHAR_BLANK);
    } while (--i);
}


void MAX7219_displayNumber(volatile long number)
{
    char negative = 0;

    // Convert negative to positive.
    // Keep a record that it was negative so we can
    // sign it again on the display.
    if (number < 0) {
        negative = 1;
        number *= -1;
    }

    MAX7219_clearDisplay();

    // If number = 0, only show one zero then exit
    if (number == 0) {
        MAX7219_writeData(MAX7219_DIGIT0, 0);
        return;
    }

    // Initialization to 0 required in this case,
    // does not work without it. Not sure why.
    char i = 0;

    // Loop until number is 0.
    do {
        MAX7219_writeData(++i, number % 10);
        // Actually divide by 10 now.
        number /= 10;
    } while (number);

    // Bear in mind that if you only have three digits, and
    // try to display something like "-256" all that will display
    // will be "256" because it needs an extra fourth digit to
    // display the sign.
    if (negative) {
        MAX7219_writeData(i, MAX7219_CHAR_NEGATIVE);
    }
}
