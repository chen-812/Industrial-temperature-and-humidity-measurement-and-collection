#ifndef __STM32_SPI_H
#define __STM32_SPI_H

#include "stm32l4xx.h"

#define GPIOA_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)             /* PA��ʱ��ʹ�� */
#define GPIOB_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)             /* PB��ʱ��ʹ�� */
#define GPIOC_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)             /* PC��ʱ��ʹ�� */
#define GPIOD_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)             /* PD��ʱ��ʹ�� */

#define DRDY_PIN      GPIO_PIN_8    /*GPIOB.15*/
#define SPI_CS        GPIO_PIN_8    /*GPIOC.8*/
#define SPI_SCK       GPIO_PIN_7    /*GPIOC.7*/
#define SPI_MISO      GPIO_PIN_9    /*GPIOC.9		SDO*/
#define SPI_MOSI      GPIO_PIN_6    /*GPIOC.6		SDI*/

#define SPI_CS_HIGH               HAL_GPIO_WritePin(GPIOC,SPI_CS,GPIO_PIN_SET)
#define SPI_CS_LOW                HAL_GPIO_WritePin(GPIOC,SPI_CS,GPIO_PIN_RESET)

#define u8		uint8_t
#define vu32  uint32_t


//SPIʱ��
#define 	SCK_L	HAL_GPIO_WritePin(GPIOC,SPI_SCK,GPIO_PIN_RESET)
#define 	SCK_H	HAL_GPIO_WritePin(GPIOC,SPI_SCK,GPIO_PIN_SET)

//SPI���
#define 	MOSI_L	HAL_GPIO_WritePin(GPIOC,SPI_MOSI,GPIO_PIN_RESET)
#define 	MOSI_H	HAL_GPIO_WritePin(GPIOC,SPI_MOSI,GPIO_PIN_SET)

//SPI����
#define 	READ_MISO	HAL_GPIO_ReadPin(GPIOC, SPI_MISO)

void SPI_Inital(void);
//ͨ��SPIд�����Ĵ���
u8 SPI_Write_Reg(u8 reg_addr,u8 data);
//��ָ��λ��дָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 SPI_Write_Buf(u8 reg_addr, u8 *pBuf, u8 data_len);
//��ȡSPI�Ĵ���ֵ ��regaddr:Ҫ���ļĴ���
u8 SPI_Read_Reg(u8 reg_addr);
//��ָ��λ�ö���ָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 SPI_Read_Buf(u8 reg_addr,u8 *pBuf,u8 data_len);

uint8_t DRDY_Pin_Value(void);

#endif


