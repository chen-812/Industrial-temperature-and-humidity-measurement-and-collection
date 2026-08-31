#include "MAX31865drv.h"
#include "stdio.h"
uint8_t uch_cr0,uch_cr1,uch_mask;

max31865_configuration  configuration;

char s[64];
uint8_t uch_fault_status;
uint8_t auch_rtd[2];
uint16_t w_rtd_value;  //MAX31865�Ĵ�������ֵ
float   f_temperature; //�¶�
float   f_resistance;  //PT100��ֵ
/****************************************************************************************
float Temperature()
{
			configuration.Conversion_mode=One_Shot_Conversion;
			maxim_31865_init(&configuration);                              //����һ�β���
			while(DRDY_Pin_Value()==SET);                                  //�ȴ���������
			maxim_get_rtd_value(auch_rtd);                                 //��ȡ�������
			w_rtd_value=(auch_rtd[0]<<8|auch_rtd[1])>>1;               //����RTD����ֵ����
			f_resistance=w_rtd_value*REF_RES/32768.000;
			f_temperature=(0-R0*A+sqrt(pow(R0,2)*pow(A,2)-4*R0*B*(R0-f_resistance)))/(2*R0*B); 
}
******************************************************************************************/

float Get_tempture(u8 *array)
{
  float temps;
  uint16_t data_temp;
	
	configuration.Conversion_mode=One_Shot_Conversion;
	maxim_31865_init(&configuration);                              //����һ�β���
	while(DRDY_Pin_Value()==SET);                                  //�ȴ���������
	maxim_get_rtd_value(auch_rtd);                                 //��ȡ�������
	
  data_temp=(array[0]<<7)+(array[1]>>1);//Get 15Bit DATA;
  temps=data_temp;
  temps=(temps*430)/32768;//Here is the rtd R value;
  temps=(temps-100)/0.385055;//A gruad
  printf("temperature: %.2f °C\r\n", temps);
  return temps;

}


void maxim_31865_configuration(void)
{
    /*����MAX31865����ģʽ*/
    configuration.Vbias=ON;
    configuration.Rtd_wire=RTD_4wire;
    configuration.Filter=Filter_50Hz;
    maxim_31865_init(&configuration);
    maxim_set_fault_threshold(430,0);/*���ù������ޣ�����Ϊ����ֵ*/
}


void maxim_31865_init(max31865_configuration* configuration)
{ 
    uint8_t temp=0;
    temp|=configuration->Vbias|configuration->Conversion_mode|configuration->Rtd_wire|configuration->Filter;
    SPI_Write_Reg(0x80,temp);  
}
/*****************************************************


******************************************************/
void maxim_set_fault_threshold(float high_threshold, float low_threshold)
{
  uint8_t au_threshold[4];
  uint16_t u_threshold;
  
  u_threshold= ((int)((high_threshold/REF_RES)*16383))<<1;
  au_threshold[0]=(u_threshold>>8);
  au_threshold[1]=u_threshold&0xff;
  u_threshold=((int)((low_threshold/REF_RES)*16383))<<1;
  au_threshold[2]=(u_threshold>>8);
  au_threshold[3]=u_threshold&0xff;
  
  SPI_Write_Buf(0x83,au_threshold,4);
}
/****************************************************

*****************************************************/
uint8_t maxim_auto_fault_detection(void)  
{
 uint8_t uch_status;
 uint8_t uch_config;
 uch_config=SPI_Read_Reg(0x00);
 uch_config|=0x84;
 SPI_Write_Reg(0x80, uch_config);
 while((SPI_Read_Reg(0x00)&0xC0)!=0x00);
 uch_status=SPI_Read_Reg(0x07);
 return(uch_status); 
}

uint8_t maxim_manual_fault_detection(void)
{
 uint8_t uch_status;
 uint8_t uch_config;
 uch_config=SPI_Read_Reg(0x00);
 uch_config|=0x80;
 uch_config&=0xf3;
 SPI_Write_Reg(0x80, uch_config);
 delay_us(200);
 uch_config|=0x88;
 SPI_Write_Reg(0x80, uch_config);
 delay_us(200);
 uch_config|=0x8C;
 SPI_Write_Reg(0x80, uch_config);
 while((SPI_Read_Reg(0x00)&0x0C)!=0x00);
 uch_status=SPI_Read_Reg(0x07);
 return(uch_status);   
}

void maxim_clear_fault_status(void)
{
 uint8_t uch_config;
 
  uch_config=SPI_Read_Reg(0x00);
  uch_config&=0xd3;
  uch_config|=0x02;
  SPI_Write_Reg(0x80, uch_config);  
}
//-------------------------------------------------------------------------/


void maxim_get_rtd_value(uint8_t *uch_buff)
{
 SPI_Read_Buf(0x01,uch_buff,2);
}

////�ӳ�1us���ó����ѡ���CPUʱ���йأ��ɸ���ʱ�ӽ��е���
////void delay_us(uint32_t us)
////{
////  uint32_t temp;
////  //temp=0x000640;
////  temp=0x02;
////  while(us)
////  {
////    while (temp!=0)
////        temp--;
////    temp=0x02;
////    us--;
////  }
////}


