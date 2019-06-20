#include "ads1115.h"
#include "delay.h"
/************************************
 *   ADDR(1)---> GND
 *   VDD (8)---> 3.3V
 *   SCL(10) ---> PB10
 *   SDA(9) ---> PB11
 *   AINp=AIN0, AINn=GND
 ************************************/
/***************���Ŷ���*************                         ****/
#define SCL              0x40
#define SDA              0x80

#define SCL_DDR_OUT  	 PB10OUT()//P5DIR |= SCL       // ����Ϊ���
#define SCL_H 		GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define SCL_L	 	GPIO_ResetBits(GPIOB,GPIO_Pin_10)

#define SDA_DDR_OUT   	PB11OUT() //P5DIR |= SDA        // ����Ϊ���
#define SDA_DDR_IN               PB11IN()  //P5DIR &=  ~SDA      // ����Ϊ����
#define SDA_IN                   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);   // ��ȡ �����ƽ
#define SDA_H    	 GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define SDA_L	  	 GPIO_ResetBits(GPIOB,GPIO_Pin_11)

#define TRUE   1
#define FALSE  0
#define DA     -1  //����

/*************ADDR Initial********************/
#define ADDRESS    ADDRESS_0   //ADDR PIN ->GND
#define ADDRESS_W  ADDRESS|0x00  //д��ַ
#define ADDRESS_R  ADDRESS|0x01    //����ַ

/*************Config Initial*********************/
#define OS         OS_1
#define PGA        PGA_0     //FS=6.144V
#define DR         DR_7       //Data Rate = 860
#define COMP_QUE   COMP_QUE_3

unsigned int Config;
unsigned char Writebuff[5],Readbuff[4];
unsigned int Result[2]; 
int D_ADS; //ת����������
float VIN_DAS; //����ĵ�ѹֵ
unsigned char  t_DAS; 
int  Format[5]={0};  //ת����������ת����ʮ����

/*******************************************
�������ƣ�delay
��    �ܣ���ʱԼ15us��ʱ��
��    ������
����ֵ  ����
********************************************/
void Delay(void)
{
	delay_us(15);
}	

/******************��ʱ1ms��ʱ��*********************/
void Delay_1ms(void)
{
	delay_ms(1);
}
void __no_operation()
{
	delay_us(5);	
}
void PB11IN()
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA3	
}
void PB11OUT()
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA3	
}
void PB10OUT()
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOA3	
}
/*******************************************
�������ƣ�Start
��    �ܣ����IIC����ʼ��������
��    ������
����ֵ  ����
********************************************/
void Start(void)
{
        SCL_H;
        SDA_H;
        Delay();
	SDA_L;
        Delay();
	SCL_L;
        Delay();
}

/*******************************************
�������ƣ�Stop
��    �ܣ����IIC����ֹ��������
��    ������
����ֵ  ����
********************************************/
void Stop(void)
{ 
        SDA_L;
        Delay();
        SCL_H;
        Delay();
	SDA_H;
        Delay();
}


/*******************************************
�������ƣ�ACK
��    �ܣ����IIC������Ӧ�����
��    ������
����ֵ  ����
********************************************/
void ACK(void)
{
        SDA_L;
        __no_operation();__no_operation();
        SCL_H;
        Delay();
        SCL_L;
	__no_operation();__no_operation();
	SDA_H;
        Delay();
}

/*******************************************
�������ƣ�NACK
��    �ܣ����IIC��������Ӧ�����
��    ������
����ֵ  ����
********************************************/
void NACK(void)
{
	SDA_H;
	__no_operation();__no_operation();
	SCL_H;
	Delay();
	SCL_L;
	__no_operation();__no_operation();
	SDA_L;   
	Delay();       
}

/**********���Ӧ���źź���******************/
/*�������ֵΪ1��֤����Ӧ���źţ���֮û��*/
/*******************************************
�������ƣ�Check
��    �ܣ����ӻ���Ӧ�����
��    ������
����ֵ  ���ӻ��Ƿ���Ӧ��1--�У�0--��
********************************************/
unsigned char Check(void)
{
    unsigned char slaveack;
    SDA_H;
   __no_operation();__no_operation();
    
	 SCL_H;
   __no_operation();__no_operation();
   
	SDA_DDR_IN;
   __no_operation();__no_operation();
    slaveack = SDA_IN  //����SDA��ֵ
    SCL_L;
    Delay();
    SDA_DDR_OUT;
    if(slaveack)    return FALSE; //������
    else            return TRUE;
}

/***************Write a Byte****************/
void Write_1_Byte(unsigned char DataByte)
{
    int i;
    for(i=0;i<8;i++)
    {
        if(DataByte&0x80)  //if((DataByte<<i)&0x80)
            SDA_H;
        else
            SDA_L;
        Delay();
        SCL_H;
        Delay();
        SCL_L;
        Delay();
        DataByte <<= 1;
    }
    SDA_H;
    __no_operation();__no_operation();
}

/***************Write N Byte****************/
unsigned char Write_N_Byte(unsigned char *writebuffer,unsigned char n)
{
	int i;
 //     P6OUT=0xf5;  // 2��4λ��    
 /*************************************������ܿ������·�*******************/      
	for(i=0;i<n;i++)
	{
		Write_1_Byte(*writebuffer);  
                
       //         P6OUT=0xf6;  // 1 4 λ��   
                 
		if(Check()==TRUE)
		{
			writebuffer ++;                                  
       //                 P6OUT=0x79;  // 2 8 λ��                
		}                         
		else
		{ 
        //         P6OUT=0xeb;  // 3 5 λ��                 
			Stop();
			return FALSE ;
 /*************************************������ܿ������Ϸ�*******************/         
  //    P6OUT=0x7a;  // 1 8 λ��  
      
	Stop();
	return TRUE;
}

/***************Read a Byte****************/
unsigned char Read_1_Byte(void)
{
    unsigned char data=0,FLAG, i;
    for(i=0;i<8;i++)
    {
        SDA_H;
        Delay();
        SCL_H;
        SDA_DDR_IN; //�˿�Ϊ����
        Delay();
        FLAG=SDA_IN;
        data <<= 1;
        if( FLAG)
            data |= 0x01;
        SDA_DDR_OUT;
        SCL_L;
        Delay();
    }
    return data;
}

/***************Read N Byte****************/
void Read_N_Byte(unsigned char *readbuff,unsigned char n)
{
	unsigned char i;
	for(i=0;i<n;i++)
	{
		readbuff[i]=Read_1_Byte();
		if(i==n-1)
			NACK();  //���������ֽ�
		else 
			ACK(); //�������ֽ�
	}
	Stop();
}
/**
 * @brief ads1115��������
 */
void yuedeAds1115PortInit(){
    SCL_DDR_OUT;                                                                
    SDA_DDR_OUT; 
    SDA_H;
}
/**
 * @brief �����������������
 * ������ads1115�����
 * ���3�ads1115 �����������GND�VCC�SCL�����ADDRESS_0 1 3
 * �����4�����������GND��������MUX_4 5 6 7
 * �����������������������FSR��6.144V����128 SPS
 * ������������������8����� OS_1+ MUX_4�or5 6 7�+ PGA0 +MODE_1 = 0XC1
 * �8����DR_7(860sps)+ COMP_MODE_0 + COMOP_POL_0 + COMP_LAT_0 + COM_QUE_3 = 0xe3
 * @param addr ������
 * @param port ����
 */
unsigned char ads1115ConfigRegister(unsigned char writeaddr,unsigned char chnel){
    Writebuff[0] = writeaddr;
    Writebuff[1] = Pointer_1;
    Writebuff[2] = chnel;
    Writebuff[3] = 0xe3 ;  //860sps,�����,������1.2ms
    Start();
    return Write_N_Byte(Writebuff,4);
}
/**
 * @brief �����������������������
 *
 * @param addr ���������
 */
 unsigned char PointRegister (unsigned char writeaddr) {
    Writebuff[0] = writeaddr; //�������
    Writebuff[1] = Pointer_0; //�������
    Start();
    return Write_N_Byte(Writebuff,2);
}
unsigned char ads1115ReadData ( unsigned char readaddr,unsigned char *ans) { �
    Start();
    Write_1_Byte(readaddr);  
    if(Check()!= TRUE)
    {             
        Stop();
        return FALSE;
    }   
    Read_N_Byte(ans,2);  //����2���ֽ�
� � return TRUE;
}
/**
 * @brief ��������������������������ans������
 *
 * @param addr //���� 0 1 2 3
 * @param channel //��0 1 2 3
 * @param ans //�����AD�
 *
 * @return ��������������������������������
 * ������������������������FALSE
 */
unsigned int ads1115GetAD (unsigned char addr, unsigned char channel,unsigned char *ans)
{
    switch (addr){ 
        case 0: { writeaddr = ADDRESS_0; }//�����ads1115 
                break; 
        case 1: { writeaddr = ADDRESS_1;} //���vcc���  
                break; 
        case 2: { writeaddr = ADDRESS_2; }//���SDA���,�����������  
                break; 
        default: { writeaddr = ADDRESS_3;} //���SCL���  
                 break; 
    } 
    switch (port)
    {
        case 0: chnel=0xC1; break;//�������AIN0�GND���6.144V�����
        case 1: chnel=0xD1; break;//�����AIN1�GND�����
        case 2: chnel=0xE1; break;//�����AIN2�GND�����
        case 3: chnel=0xF1; break;//�����AIN3�GND�����
        default:;break; 
    }
    if( ads1115ConfigRegister(writeaddr,chnel) !=TRUE)
        return FALSE; //�������
    delay_us(1300) ;//��1.3ms�������
    if(PointRegister(writeaddr) != TRUE ) return FALSE;
    return ads1115ReadData(writeaddr+1,chenl,ans);
}
