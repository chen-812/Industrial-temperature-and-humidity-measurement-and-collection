/*
 * spi_pcap01.c
 *
 *  Created on: 2022年9月10日
 *      Author: LZC
 */
#include "SPI_PCAP.h"
#include "stm32_spi.h"


uint8_t ma;
void Delay_(uint32_t nCount)
{
  for(; nCount != 0; nCount--){ma=0;};
}

void CAP_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	GPIOA_CLK_ENABLE();   //GPIOB使能
	GPIOC_CLK_ENABLE();   //GPIOB使能

	GPIO_InitStructure.Pin = CAP_SSN|CAP_MOSI;	//SCK/SSN/MOSI
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    	//推挽输出
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = CAP_SCK;	//SCK/SSN/MOSI
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    	//推挽输出
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = CAP_MISO;
	GPIO_InitStructure.Mode =GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

}

/*模拟SPI读写数据函数*/
uint8_t CAP_SPI_ReadWriteByte(uint8_t TxData)
{
    uint8_t bit_ctr;
    for(bit_ctr=0;bit_ctr<8;bit_ctr++)
    {
        if(TxData & 0x80)
            CAP_MOSI_1;
        else
            CAP_MOSI_0;
        TxData = (TxData << 1);
        CAP_SCK_1;
        Delay_(0xff);
        if(CAP_MISO_IN==1)
            TxData |= 0x01;
        CAP_SCK_0;
        Delay_(0xff);
    }
    return(TxData);
}

void CAP_SPI_Transmit(uint8_t* Send_data, uint8_t size)
{
    uint8_t i;
    SSN_LOW;
    for(i=0;i<size;i++)
    {
        CAP_SPI_ReadWriteByte(*Send_data++);
    }
    SSN_HIGH;
}

void CAP_SPI_TransmitReceive(uint8_t* Send_data, uint8_t* Read_data,uint8_t size)
{
    uint8_t i;
    SSN_LOW;
    for(i=0;i<size;i++)
    {
        *Read_data++=CAP_SPI_ReadWriteByte(*Send_data++);
    }
    SSN_HIGH;
}


