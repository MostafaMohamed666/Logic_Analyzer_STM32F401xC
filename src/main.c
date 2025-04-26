#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "EXTI_interface.h"
#include "NVIC_interface.h"
#include "RCC_interface.h"
#include "SPI_interface.h"
#include "SYSTICK_interface.h"
#include "UART_interface.h"
#include "TIM2_interface.h"
#include "lgc.h"

int main()
{
	RCC_Peripheral_Enable();
    RCC_Peripheral_CLK_Enable(PERIPH_GPIOA);
    RCC_Peripheral_CLK_Enable(PERIPH_TIMER2);
    RCC_Peripheral_CLK_Enable(PERIPH_USART1);
    GPIO_Set_Mode(PORTA, PIN9, ALT_FUNCTION);
    GPIO_Set_ALT_FUNC_Mode(PORTA, PIN9, AF7);
    TIM2_Peripheral_Init();
    lgc_init();
    UART1_Peripheral_init();
    TIM2_Interrupt_Enable();
    NVIC_Interrupt_Enable(28);
    TIM2_Call_Back_Function(lgc_Record_Channels);
    TIM2_Preload_Value(79);
    TIM2_Start_Timer();
    lgc_Send_Channel_Data();
	while(1)
	{

	}
	return 0;
}
