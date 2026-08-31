#ifndef __MAX31865drv_H
#define __MAX31865drv_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32_spi.h"

typedef struct
{
 uint8_t   Vbias;
 uint8_t   Conversion_mode;
 uint8_t   Rtd_wire;
 uint8_t   Filter; 
}max31865_configuration;

extern char s[64];
extern uint8_t uch_fault_status;
extern uint8_t auch_rtd[2];
extern uint16_t w_rtd_value;  //MAX31865寄存器电阻值
extern float   f_temperature; //温度
extern float   f_resistance;  //PT100阻值

extern max31865_configuration  configuration;

//如果RTD为PT100

#define         REF_RES                         430
#define         R0                              100

/*
 //如果RTD为PT1K
#define         REF_RES                         4000
#define         R0                              1000
*/

#define         ON                              0x80
#define         OFF                             0x00

#define         Auto_Conversion                 0x40
#define         One_Shot_Conversion             0x20

#define         RTD_3wire                       0x10
#define         RTD_2wire                       0x00
#define         RTD_4wire                       0x00

#define         Filter_50Hz                     0x01
#define         Filter_60Hz                     0x00

/* 定义温度修正系数*/

#define         A                               0.00390830
#define         B                               -0.0000005775
#define         C                               -0.00000000000418301


//float Temperature();
float Get_tempture(u8 *array);
void maxim_31865_configuration(void);
void maxim_31865_write_register(uint8_t uch_register_address, uint8_t uch_register_value);
void maxim_31865_write_nregisters(uint8_t uch_register_address,uint8_t *uch_buff,uint8_t uch_nBytes);
uint8_t maxim_31865_read_register(uint8_t uch_register_address);
void maxim_31865_read_nregisters(uint8_t uch_register_address, uint8_t *uch_buff,uint8_t uch_nBytes);
void maxim_31865_init(max31865_configuration* configuration);
void maxim_set_fault_threshold(float high_threshold, float low_threshold);
uint8_t maxim_auto_fault_detection(void) ;
uint8_t maxim_manual_fault_detection(void);
void maxim_clear_fault_status(void);
void maxim_get_rtd_value(uint8_t *uch_buff);
void delay_us(uint32_t us);

  
 #ifdef __cplusplus
}
#endif

#endif


