#ifndef __PCAD01_H
#define __PCAD01_H


#include "SPI_PCAP.h"

#define IF_POLY_FIT 1
#define CAP0_VALUE  10.0

#define WSRAM 0X09  //写SRAM操作码
#define RSRAM 0x01  //读SRAM操作码

#define SDCOMD   1 //操作码byte
#define SDFIRMWR 3 //写SRAM主设备发送byte
#define SDFIRMRD 2 //读SRAM主设备发送byte
#define RESRAM   1 //读SRAM从设备发送byte
#define RESULT   3 //读测量结果从设备发送byte
#define SDREGISTWR 4 //写寄存器主设备发送byte
#define SDREGISTRD 1 //读寄存器主设备发送byte

#define CAP_CHANNEL0 res0
#define CAP_CHANNEL1 res1
#define CAP_CHANNEL2 res2
#define CAP_CHANNEL3 res3
#define CAP_CHANNEL4 res4

typedef enum
{
    res0=0,
    res1=1,
    res2=2,
    res3=3,
	  res4=4,
    res8=8,
    res13=13,
    hcap,
    lcap,
    temp,
}CHANNEL;



void PCAP01_Command(unsigned char value);
void SSPI_SendData(unsigned char size);
void PCAP01_Wirte_SRAM(unsigned short address,unsigned char value);
unsigned char PCAP01_Read_SRAM(unsigned short address);
void Send_RegisterData(unsigned char address,unsigned long value);
void PCAP01_Write_Register(void);
uint32_t Read_Register(unsigned char address);

void PCAP01_Init(void);
float PCAP01_result(CHANNEL channel);
float read_humidity(void);


#endif 
