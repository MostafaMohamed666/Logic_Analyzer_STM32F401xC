/*
 * SPI_interface.h
 *
 *  Created on: Apr 4, 2025
 *      Author: Mostafa Mohamed
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_Master_init();
void SPI_Slave_init();
u8_t SPI_Recieve();
void SPI_Transmit(u8_t Data);


#endif /* SPI_INTERFACE_H_ */
