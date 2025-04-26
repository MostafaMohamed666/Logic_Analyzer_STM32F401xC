/*
 * RCC_program.c
 *
 *  Created on: Mar 1, 2025
 *      Author: Mostafa Mohamed
 */
#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "RCC_config.h"
#include "RCC_private.h"
#include "RCC_interface.h"

void RCC_Peripheral_Enable(){
#if(SYSCLK == HSI)
	// HSI is turned on
    SET_BIT(RCC->CR, HSION);
    // HSI is on wait until ready
    while(!READ_BIT(RCC->CR, HSIRDY));
    // Switch system clock to HSI
    CLEAR_BIT(RCC->CFGR, SW0);
    CLEAR_BIT(RCC->CFGR, SW1);
#elif(SYSCLK == PLL)
    SET_BIT(RCC->CR, HSION);
    while(!READ_BIT(RCC->CR, HSIRDY));

    CLEAR_BIT(RCC->CR, PLLON);
    while (READ_BIT(RCC->CR, PLLRDY));  // Wait until PLL is fully off

    CLEAR_BIT(RCC->CFGR, PLLSRC);       // HSI selected as PLL source (bit 22 = 0)

    // Set PLLM = 16 (bits [5:0])
    RCC->PLLCFGR &= ~(0x3F);
    RCC->PLLCFGR |= 16;

    // Set PLLN = 144 (bits [14:6])
    RCC->PLLCFGR &= ~(0x1FF << 6);
    RCC->PLLCFGR |= (144 << 6);

    // Set PLLP = 4 bits [17:16] = 0b01
    RCC->PLLCFGR &= ~(0b11 << 16);
    RCC->PLLCFGR |= (0b01 << 16);  // PLLP = 4

    SET_BIT(RCC->CR, PLLON);
    while (!READ_BIT(RCC->CR, PLLRDY));

    CLEAR_BIT(RCC->CFGR, SW0);
    SET_BIT(RCC->CFGR, SW1);

    while ((RCC->CFGR & (0b11 << 2)) != (0b10 << 2)); // Wait until PLL is used
#elif(SYSCLK == HSE)
    /************HSE OSCILLATOR SELECTION*********/
    #if(HSE_OSC == MECHANICAL_OSC)
        CLEAR_BIT(RCC->CR, HSEBYP);
    #elif(HSE_OSC == RC_OSC)
        SET_BIT(RCC->CR, HSEBYP);
    #endif
    /*********************************************/
	// HSE is turned on
    SET_BIT(RCC->CR, HSEON);
    // HSE is on wait until ready
    while(!READ_BIT(RCC->CR, HSERDY));
    // Switch system clock to HSE
    SET_BIT(RCC->CFGR, SW0);
    CLEAR_BIT(RCC->CFGR, SW1);
    // Disable HSI Clock
    CLEAR_BIT(RCC->CR, HSION);
#endif
}
void RCC_Peripheral_CLK_Enable(Peripheral_t enuPeripheral)
{
    switch (enuPeripheral)
    {
        // AHB1 Bus
        case PERIPH_GPIOA:
            SET_BIT(RCC->AHB1ENR, GPIOA);
            break;
        case PERIPH_GPIOB:
            SET_BIT(RCC->AHB1ENR, GPIOB);
            break;
        case PERIPH_GPIOC:
            SET_BIT(RCC->AHB1ENR, GPIOC);
            break;
        case PERIPH_DMA1:
            SET_BIT(RCC->AHB1ENR, DMA1);
            break;
        case PERIPH_DMA2:
            SET_BIT(RCC->AHB1ENR, DMA2);
            break;

        // APB1 Bus
        case PERIPH_SPI2:
            SET_BIT(RCC->APB1ENR, SPI2);
            break;
        case PERIPH_SPI3:
            SET_BIT(RCC->APB1ENR, SPI3);
            break;
        case PERIPH_USART2:
            SET_BIT(RCC->APB1ENR, USART2);
            break;
        case PERIPH_TIMER2:
        	SET_BIT(RCC->APB1ENR, TIMER2);
        	break;

        // APB2 Bus
        case PERIPH_USART1:
            SET_BIT(RCC->APB2ENR, USART1);
            break;
        case PERIPH_USART6:
            SET_BIT(RCC->APB2ENR, USART6);
            break;
        case PERIPH_SPI1:
            SET_BIT(RCC->APB2ENR, SPI1);
            break;
        case PERIPH_SPI4:
            SET_BIT(RCC->APB2ENR, SPI4);
            break;
        case PERIPH_SYSCFG:
            SET_BIT(RCC->APB2ENR, SYSCFG);
            break;
    }
}

void RCC_Peripheral_CLK_Disable(Peripheral_t enuPeripheral)
{
    switch (enuPeripheral)
    {
        // AHB1 Bus
        case PERIPH_GPIOA:
            CLEAR_BIT(RCC->AHB1ENR, GPIOA);
            break;
        case PERIPH_GPIOB:
            CLEAR_BIT(RCC->AHB1ENR, GPIOB);
            break;
        case PERIPH_GPIOC:
            CLEAR_BIT(RCC->AHB1ENR, GPIOC);
            break;
        case PERIPH_DMA1:
            CLEAR_BIT(RCC->AHB1ENR, DMA1);
            break;
        case PERIPH_DMA2:
            CLEAR_BIT(RCC->AHB1ENR, DMA2);
            break;

        // APB1 Bus
        case PERIPH_SPI2:
            CLEAR_BIT(RCC->APB1ENR, SPI2);
            break;
        case PERIPH_SPI3:
            CLEAR_BIT(RCC->APB1ENR, SPI3);
            break;
        case PERIPH_USART2:
            CLEAR_BIT(RCC->APB1ENR, USART2);
            break;
        case PERIPH_TIMER2:
        	CLEAR_BIT(RCC->APB1ENR, TIMER2);
        	break;

        // APB2 Bus
        case PERIPH_USART1:
            CLEAR_BIT(RCC->APB2ENR, USART1);
            break;
        case PERIPH_USART6:
            CLEAR_BIT(RCC->APB2ENR, USART6);
            break;
        case PERIPH_SPI1:
            CLEAR_BIT(RCC->APB2ENR, SPI1);
            break;
        case PERIPH_SPI4:
            CLEAR_BIT(RCC->APB2ENR, SPI4);
            break;
        case PERIPH_SYSCFG:
            CLEAR_BIT(RCC->APB2ENR, SYSCFG);
            break;
    }
}




