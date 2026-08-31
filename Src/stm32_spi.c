#include "stm32_spi.h"


u8 maa;
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--){maa=0;};
}


void SPI_Inital(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIOA_CLK_ENABLE();   //GPIOAʹ��
	GPIOC_CLK_ENABLE();   //GPIOAʹ��
		
	GPIO_InitStructure.Pin = SPI_SCK|SPI_MOSI;	//GPIO_SCK,	GPIO_SDI(MOSI)
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    	//�������
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = SPI_MISO;				//GPIO_SDO-MISO
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;     		//��������
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = SPI_CS;				//CS
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    	//�������
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.Pin = DRDY_PIN;				//DRDY
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;   //��������
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*ģ��SPI��д���ݺ���*/
u8 SPI_ReadWriteByte(u8 TxData)                                        
{		
	u8 bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) 
   	{
		if(TxData & 0x80)
		MOSI_H;         
		else
		MOSI_L;
		TxData = (TxData << 1);           
		SCK_H; 
		Delay(0xff);
		if(READ_MISO)                     
		TxData |= 0x01;       		  
		SCK_L; 
		Delay(0xff);           		 
   	}
    return(TxData);           		  		    
}


uint8_t DRDY_Pin_Value(void)
{
   return(HAL_GPIO_ReadPin(GPIOA, DRDY_PIN));
}

//ͨ��SPIд�����Ĵ���
u8 SPI_Write_Reg(u8 reg_addr,u8 data)
{
	u8 status;	
    SPI_CS_LOW;                    //ʹ��SPI����
  	status =SPI_ReadWriteByte(reg_addr); //���ͼĴ����� 
  	SPI_ReadWriteByte(data);            //д��Ĵ�����ֵ
  	SPI_CS_HIGH;                    //��ֹSPI����	   
  	return(status);       		         //����״ֵ̬
}

//��ȡSPI�Ĵ���ֵ ��regaddr:Ҫ���ļĴ���
u8 SPI_Read_Reg(u8 reg_addr)
{
	u8 reg_val;	    
 	SPI_CS_LOW;                			//ʹ��SPI����		
  	SPI_ReadWriteByte(reg_addr);     	//���ͼĴ�����
  	reg_val=SPI_ReadWriteByte(0);		//��ȡ�Ĵ�������
  	SPI_CS_HIGH;                		//��ֹSPI����		    
  	return(reg_val);                 	//����״ֵ̬
}	

//��ָ��λ��дָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 SPI_Write_Buf(u8 reg_addr, u8 *pBuf, u8 data_len)
{
	u8 status,i;	    
 	SPI_CS_LOW;                                    //ʹ��SPI����
  	status = SPI_ReadWriteByte(reg_addr);                //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  	for(i=0; i<data_len; i++)
		SPI_ReadWriteByte(*pBuf++); //д������	 
  	SPI_CS_HIGH;                                    //�ر�SPI����
  	return status;                                       //���ض�����״ֵ̬
}

//��ָ��λ�ö���ָ�����ȵ�����
//*pBuf:����ָ��
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 SPI_Read_Buf(u8 reg_addr,u8 *pBuf,u8 data_len)
{
	u8 status,i;	       
  	SPI_CS_LOW;                     //ʹ��SPI����
  	status=SPI_ReadWriteByte(reg_addr);   //��ȡ�Ĵ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(i=0;i<data_len;i++)
		pBuf[i]=SPI_ReadWriteByte(0);//��������

  	SPI_CS_HIGH;                     //�ر�SPI����
  	return status;                        //���ض�����״ֵ̬
}
