/*
 * spi_pcap01.h
 *
 *  Created on: 2022年9月10日
 *      Author: LZC
 */

#ifndef SPI_PCAP01_H_
#define SPI_PCAP01_H_

#include "stdint.h"
#include "stm32l4xx.h"

#define  CAP_MISO       GPIO_PIN_5    /*GPIOC.4*/
#define  CAP_SCK        GPIO_PIN_4    /*GPIOC.5*/
#define  CAP_SSN        GPIO_PIN_7    /*GPIOC.6*/
#define  CAP_MOSI       GPIO_PIN_6    /*GPIOC.7*/

//==================================主出从入====================================B7
#define  CAP_MOSI_0     HAL_GPIO_WritePin(GPIOA,CAP_MOSI,GPIO_PIN_RESET)
#define  CAP_MOSI_1     HAL_GPIO_WritePin(GPIOA,CAP_MOSI,GPIO_PIN_SET)
//===================================主入从出===================================B4
#define  CAP_MISO_0     HAL_GPIO_WritePin(GPIOC,CAP_MISO,GPIO_PIN_RESET)
#define  CAP_MISO_1     HAL_GPIO_WritePin(GPIOC,CAP_MISO,GPIO_PIN_SET)
#define  CAP_MISO_IN    HAL_GPIO_ReadPin(GPIOC, CAP_MISO)
//===================================SPI时钟端口================================B5
#define  CAP_SCK_0      HAL_GPIO_WritePin(GPIOC,CAP_SCK,GPIO_PIN_RESET)
#define  CAP_SCK_1      HAL_GPIO_WritePin(GPIOC,CAP_SCK,GPIO_PIN_SET)
//=========================SPI使能端口==========================================B6
#define  SSN_LOW    		HAL_GPIO_WritePin(GPIOA,CAP_SSN,GPIO_PIN_RESET)
#define  SSN_HIGH    		HAL_GPIO_WritePin(GPIOA,CAP_SSN,GPIO_PIN_SET)

//void CAP_SPI_Init();
void CAP_SPI_Transmit(uint8_t* Send_data, uint8_t size);
void CAP_SPI_TransmitReceive(uint8_t* Send_data, uint8_t* Read_data,uint8_t size);
void CAP_SPI_Init(void);



#endif /* SPI_PCAP01_H_ */
