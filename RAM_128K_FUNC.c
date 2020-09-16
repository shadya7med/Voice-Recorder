/*
 * RAM_128K_FUNC.c
 *
 *  Created on: Apr 15, 2020
 *      Author: shady
 */
#include"STD_TYPES.h"
#include"BIT_CALC.h"
#include"DIO_REG.h"
#include"DIO_INT.h"

#include"RAM_INT.h"

void RAM_PinsInitailize ()
{
	DIO_SetPortDirection(RAM_ADRH_PORT,PORT_OUTPUT);//PORTD
	DIO_SetPortValue(RAM_ADRH_PORT,PORT_LOW);
	//DIO_SetPortDirection(RAM_ADRL_PORT,PORT_OUTPUT);//PORTD
	//DIO_SetPortValue(RAM_ADRL_PORT,PORT_LOW);
	DIO_SetPortDirection(RAM_DATA_PORT,PORT_OUTPUT);//PORTC
	DIO_SetPortValue(RAM_DATA_PORT,PORT_LOW);

	DIO_SetPinDirection(RAM_CTRL_PORT,ADR_16_PIN,OUTPUT);
	DIO_SetPinValue(RAM_CTRL_PORT,ADR_16_PIN,LOW);
	DIO_SetPinDirection(RAM_CTRL_PORT,ADR_13_5_PIN,OUTPUT);
	DIO_SetPinValue(RAM_CTRL_PORT,ADR_13_5_PIN,LOW);
	DIO_SetPinDirection(RAM_CTRL_PORT,LE_PIN,OUTPUT);
	DIO_SetPinValue(RAM_CTRL_PORT,LE_PIN,LOW);
	DIO_SetPinDirection(RAM_CTRL_PORT,OE1_PIN,OUTPUT);
	DIO_SetPinValue(RAM_CTRL_PORT,OE1_PIN,HIGH);
	DIO_SetPinDirection(RAM_CTRL_PORT,WE1_PIN,OUTPUT);
	DIO_SetPinValue(RAM_CTRL_PORT,WE1_PIN,HIGH);
	DIO_SetPinDirection(RAM_CTRL_PORT,CE1_PIN,OUTPUT);
	DIO_SetPinValue(RAM_CTRL_PORT,CE1_PIN,LOW);

}

void RAM_WriteData(u32 RamAddress,u8 Data)
{
	/*Setting Address*/
	/*/Without Latch/
	DIO_SetPinValue(RAM_CTRL_PORT,ADR_16_PIN,(u8)((RamAddress >> 16) & 0x01));
	DIO_SetPortValue(RAM_ADRH_PORT,(u8)(RamAddress >> 8));
	DIO_SetPinValue(RAM_CTRL_PORT,ADR_3_PIN,(u8)((RamAddress >> 3) & 0x01));
	RAM_ADRL_PORT_REG = (RAM_ADRL_PORT_REG & 0x08)|(0xF7 & (u8)(RamAddress));*/
	/*With Latch*/
	PORTA_register = (PORTA_register & 0x7F)|((u8)((RamAddress >> 16) & 0x01));
	SET_BIT(PORTA_register,LE_PIN);
	PORTD_register =(u8)(RamAddress >> 8);
	CLR_BIT(PORTA_register,LE_PIN);
	PORTD_register =(u8)(RamAddress );
	//DIO_SetPinValue(RAM_CTRL_PORT,ADR_16_PIN,(u8)((RamAddress >> 16) & 0x01));
	//DIO_SetPinValue(RAM_CTRL_PORT,LE_PIN,HIGH);
	//DIO_SetPortValue(RAM_ADRH_PORT,(u8)(RamAddress >> 8));
	//DIO_SetPinValue(RAM_CTRL_PORT,ADR_13_5_PIN,(u8)((RamAddress >> 13) & 0x01));
	//RAM_ADR_PORT_REG =(RAM_ADR_PORT_REG & 0x20)|((u8)(RamAddress >> 8) & 0xDF);
	//DIO_SetPinValue(RAM_CTRL_PORT,LE_PIN,LOW);
	//DIO_SetPortValue(RAM_ADRL_PORT,(u8)(RamAddress));
	//DIO_SetPinValue(RAM_CTRL_PORT,ADR_13_5_PIN,(u8)((RamAddress >> 5) & 0x01));
	//RAM_ADR_PORT_REG =(RAM_ADR_PORT_REG & 0x20)|((u8)(RamAddress) & 0xDF);

	/*Setting Control Signals to WRITE*/
	DIO_SetPinValue(RAM_CTRL_PORT,CE1_PIN,LOW);
	DIO_SetPinValue(RAM_CTRL_PORT,OE1_PIN,HIGH);
	DIO_SetPinValue(RAM_CTRL_PORT,WE1_PIN,LOW);
	/*Apply Data to RAM*/
	//DIO_SetPortValue(RAM_DATA_PORT,Data);
	/*DISABLE RAM output*/
	DIO_SetPinValue(RAM_CTRL_PORT,WE1_PIN,HIGH);
}
u8 RAM_ReadData(u32 RamAddress)
{
	static u8 RamData = 0;
		/*Setting Address*/
	/*With Latch*/
		DIO_SetPinValue(RAM_CTRL_PORT,ADR_16_PIN,(u8)((RamAddress >> 16) & 0x01));
		SET_BIT(PORTA_register,LE_PIN);
		DIO_SetPinValue(RAM_CTRL_PORT,ADR_13_5_PIN,(u8)((RamAddress >> 13) & 0x01));
		RAM_ADR_PORT_REG =((RAM_ADR_PORT_REG & 0x20)|(u8)((RamAddress >> 8) & 0xDF));
		CLR_BIT(PORTA_register,LE_PIN);
		DIO_SetPinValue(RAM_CTRL_PORT,ADR_13_5_PIN,(u8)((RamAddress >> 5) & 0x01));
		RAM_ADR_PORT_REG =((RAM_ADR_PORT_REG & 0x20)|((u8)(RamAddress) & 0xDF));
		/*Setting Control Signals to read*/
		SET_BIT(PORTA_register,WE1_PIN);
		CLR_BIT(PORTA_register,OE1_PIN);
		CLR_BIT(PORTA_register,CE1_PIN);
		/*Getting Data to RAM*/
		RamData = RAM_DATA_READ_REG;
		/*DISABLE RAM output*/
		SET_BIT(PORTA_register,OE1_PIN);

		return RamData;
}
