/*
 * SPI_config.h
 *
 *  Created on: Apr 4, 2025
 *      Author: Mostafa Mohamed
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


typedef enum
{
	PERIPH_CLK_2,
	PERIPH_CLK_4,
	PERIPH_CLK_8,
	PERIPH_CLK_16,
	PERIPH_CLK_32,
	PERIPH_CLK_64,
	PERIPH_CLK_128,
	PERIPH_CLK_256
}SPI_CLK_PRESCALAR;

#define SPI_CLK PERIPH_CLK_16


#endif /* SPI_CONFIG_H_ */
