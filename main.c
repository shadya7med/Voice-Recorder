/*
 * main.c
 *
 *  Created on: Apr 26, 2020
 *      Author: shady
 */
#include"STD_TYPES.h"
#include"BIT_CALC.h"
#include"INTERRUPT_INT.h"
#include"DIO_REG.h"
#include"DIO_INT.h"
#include"ADC_int.h"
#include"util/delay.h"
#include"TIMER_INT.h"
#include"TIMER_CONFG.h"

#include"SPI_Interface.h"
#include"SPI_Config.h"
#include"MAX7219_Interface.h"
#include"RAM_INT.h"

/*new comment to test changes*/

void AdcCap_MemoStore(void);
void Read_GenPWM(void);
void TimeDigSplit_Disp(void);
//u8 DataConv(u8 Data);

u8 AdcResult = 0;
u32 RamAddress = 0;
u8 RamData= 0 ;

u32 time=0;
u8 secL =0;
u8 secH =0;
u8 minL =0;
u8 minH =0;

u32 INTCounter1 = 0 ;
u32 INTCounter2 = 0 ;

u8 WriteDone = 0;
u8 readDone = 0 ;
int main (void)
{
	u8 PBValue = 1;
	/*RAM PORT*/
	RAM_PinsInitailize();
	/*Push Button*/
	DIO_SetPinDirection(PORTA,PIN2,INPUT);//Pulled Up PB to Start Recording
	DIO_SetPinValue(PORTA,PIN2,HIGH);
	/*LED State Indicator*/
	DIO_SetPinDirection(PORTB,PIN0,OUTPUT);
	DIO_SetPinValue(PORTB,PIN0,LOW);
	/*ADC Channel 0 --> PA0*/
	DIO_SetPinDirection(PORTA,PIN0,INPUT);
	ADC_intialize();
	/*SPI PINS INIT*/
	DIO_SetPinDirection(PORTB,SCK_PIN,OUTPUT);
	DIO_SetPinDirection(PORTB,MOSI_PIN,OUTPUT);
	DIO_SetPinDirection(PORTB,SS_PIN,OUTPUT);
	DIO_SetPinValue(PORTB,SS_PIN,HIGH);
	/*SPI MASTER INIT*/
	SPI_Init();
	/*MAX7912 Init*/
	MAX7219_Init();
	/*TIMER0 INT*/
	SET_INT_VEC_TO_ISR(TIMER0_CMP_VEC,AdcCap_MemoStore);
	SET_INT_VEC_TO_ISR(TIMER1_OVF_VEC,Read_GenPWM);
	/*Polling on PB*/
	while (PBValue == 1){DIO_GetPinValue(PORTA,PIN2,& PBValue);}
	/*Timer0 Initializing*/
	TIMER0_INIT(0,125);
	/*Enable Global Interrupts*/
	EN_GlobalInterrupt();


	while(1){
		if (WriteDone == 1)
		{
			WriteDone = 0;
			CLR_BIT(PORTB_register,PIN0);
			_delay_ms(2000);
			//DIS_GlobalInterrupt();
			DIO_SetPortDirection(RAM_DATA_PORT,PORT_INPUT);
			RamAddress = 0;
			RamData = RAM_ReadData(RamAddress);
			TIMER1_INIT(0,RamData,0,249);
			//EN_GlobalInterrupt();
		}
		else if(readDone == 1)
		{
			readDone = 0;
			MAX7219_writeData(0x01,0);
			MAX7219_writeData(0x02,0);
			MAX7219_writeData(0x03,0);
			MAX7219_writeData(0x04,0);
		}
		else{
			/*Wait for interrupts*/
		}
	}

	return 0;
}
void AdcCap_MemoStore(void){
		INTCounter1 ++;
		if(INTCounter1 == 8000)
		{
			INTCounter1 = 0;
			time ++;
			TimeDigSplit_Disp();
		}

		if (RamAddress == 131072)
		{

			TIMER0_STOPPED();
			WriteDone = 1;


		}
		else{
		ADC_GETVALUE_BLOCKING(0,&AdcResult);
		if(AdcResult > 249)
		{
			AdcResult=249;
		}
		else{

		}
		/*Write operation*/
		//RAM_WriteData(RamAddress,AdcResult);
		DIO_SetPinValue(RAM_CTRL_PORT,ADR_16_PIN,(u8)((RamAddress >> 16) & 0x01));
		SET_BIT(PORTA_register,LE_PIN);
		DIO_SetPinValue(RAM_CTRL_PORT,ADR_13_5_PIN,(u8)((RamAddress >> 13) & 0x01));
		RAM_ADR_PORT_REG =((RAM_ADR_PORT_REG & 0x20)|(u8)((RamAddress >> 8) & 0xDF));
		CLR_BIT(PORTA_register,LE_PIN);
		DIO_SetPinValue(RAM_CTRL_PORT,ADR_13_5_PIN,(u8)((RamAddress >> 5) & 0x01));
		RAM_ADR_PORT_REG =((RAM_ADR_PORT_REG & 0x20)|((u8)(RamAddress) & 0xDF));

		CLR_BIT(PORTA_register,CE1_PIN);
		SET_BIT(PORTA_register,OE1_PIN);
		CLR_BIT(PORTA_register,WE1_PIN);


		PORTC_register = AdcResult;
		SET_BIT(PORTA_register,WE1_PIN);

		SET_BIT(PORTB_register,PIN0);
		/*INC ADR*/
		RamAddress ++ ;
		}



}
void Read_GenPWM(void)
{

	INTCounter2 ++;
	if((INTCounter2 == 32000))
	{
		INTCounter2 = 0;
		time --;
		TimeDigSplit_Disp();
	}

	if (RamAddress == 131072)
	{

		TIMER1_STOPPED();
		readDone = 1;

	}
	else if((INTCounter2 % 4) == 0)
	{

	RamAddress ++ ;
	/*Read*/
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
	/*Getting Data from RAM*/
	RamData = RAM_DATA_READ_REG;
	/*DISABLE RAM output*/
	SET_BIT(PORTA_register,OE1_PIN);

	TIM1_Set_CMPA_REG_Value(RamData);


	TOG_BIT(PORTB_register,PIN0);

	}
	else{}
}
void TimeDigSplit_Disp(void){
	u8 tempSec = 0;
	u8 tempMin = 0;

	tempMin = (u8)(time/(u32)60);
	tempSec = (u8)(time - (tempMin *(u32)60));
	secH =(u8)(tempSec/(u8)10);
	secL =(u8)(tempSec - (secH*(u8)10));
	minH =(u8)(tempMin/(u8)10);
	minL =(u8)(tempMin - (minH*(u8)10));

	MAX7219_writeData(0x01,secL);
	MAX7219_writeData(0x02,secH);
	MAX7219_writeData(0x03,minL);
	MAX7219_writeData(0x04,minH);

}
/*
u8 DataConv(u8 Data)
{
	u32 tempData = 0;
	tempData = (u32)(((u32)Data *(u32)1000)/255);
	return ((u8)((tempData * (u32)125)/1000));
}*/

