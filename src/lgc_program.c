/*
 * lgc.c
 *
 *  Created on: Apr 24, 2025
 *      Author: Mostafa Mohamed
 */
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "TIM2_interface.h"
#include "UART_interface.h"
#include "lgc.h"
#include "lgc_config.h"
#include "lgc_private.h"

u8_t LGC_FLAG = 0;
static volatile u16_t logic_capture;

void lgc_init()
{
	LGC_FLAG = 0;
	GPIO_Set_Mode(CHANNEL_1_PORT, CHANNEL_1_PIN, INPUT);
	GPIO_Set_Input_Type(CHANNEL_1_PORT, CHANNEL_1_PIN, PULL_DOWN);
	GPIO_Set_Mode(CHANNEL_2_PORT, CHANNEL_2_PIN, INPUT);
	GPIO_Set_Input_Type(CHANNEL_2_PORT, CHANNEL_2_PIN, PULL_DOWN);
	GPIO_Set_Mode(CHANNEL_3_PORT, CHANNEL_3_PIN, INPUT);
	GPIO_Set_Input_Type(CHANNEL_3_PORT, CHANNEL_3_PIN, PULL_DOWN);
	GPIO_Set_Mode(CHANNEL_4_PORT, CHANNEL_4_PIN, INPUT);
	GPIO_Set_Input_Type(CHANNEL_4_PORT, CHANNEL_4_PIN, PULL_DOWN);
}

void lgc_Record_Channels()
{
	TIM2_Clear_Interrupt_Flag();
    static volatile u16_t counter = 0;
    if(counter < CHANNELSIZE){
    	logic_capture = GPIO_Read_Input_Register_PortA();
        Channels[0][counter] = (logic_capture>>CHANNEL_1_PIN)&1;
        Channels[1][counter] = (logic_capture>>CHANNEL_2_PIN)&1;
        Channels[2][counter] = (logic_capture>>CHANNEL_3_PIN)&1;
        Channels[3][counter] = (logic_capture>>CHANNEL_4_PIN)&1;
        counter++;
    } else
    {
    	TIM2_Stop_Timer();
    	LGC_FLAG = 1;
   	}
}

void lgc_Send_Channel_Data()
{
	while(!LGC_FLAG);
	UART1_Send_Data('s');
    for(u16_t i=0; i<CHANNELSIZE; i++){
    	UART1_Send_Data(Channels[0][i] ? '1':'0');
    	UART1_Send_Data(Channels[1][i] ? '1':'0');
    	UART1_Send_Data(Channels[2][i] ? '1':'0');
    	UART1_Send_Data(Channels[3][i] ? '1':'0');
    }
}
