#include "ads1115.h"
#include "delay.h"
/************************************
 *   ADDR(1)---> GND
 *   VDD (8)---> 3.3V
 *   SCL(10) ---> PB10
 *   SDA(9) ---> PB11
 *   AINp=AIN0, AINn=GND
 ************************************/


/***************Òý½Å¶¨Òå*************                         ****/
#define SCL              0x40
#define SDA              0x80

#define SCL_DDR_OUT  	 PB10OUT()//P5DIR |= SCL       // ÉèÖÃÎªÊä³ö
#define SCL_H 		GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define SCL_L	 	GPIO_ResetBits(GPIOB,GPIO_Pin_10)

#define SDA_DDR_OUT   	PB11OUT() //P5DIR |= SDA        // ÉèÖÃÎªÊä³ö
#define SDA_DDR_IN               PB11IN()  //P5DIR &=  ~SDA      // ÉèÖÃÎªÊäÈë
#define SDA_IN                   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);   // ¶ÁÈ¡ ÊäÈëµçÆ½
#define SDA_H    	 GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define SDA_L	  	 GPIO_ResetBits(GPIOB,GPIO_Pin_11)

#define TRUE   1
#define FALSE  0
#define DA     -1

/*************ADDR Initial********************/
#define ADDRESS    ADDRESS_0   //ADDR PIN ->GND
#define ADDRESS_W  ADDRESS|0x00  //Ð´µØÖ·
#define ADDRESS_R  ADDRESS|0x01    //¶ÁµØÖ·

/*************Config Initial*********************/
#define OS         OS_1
#define PGA        PGA_0     //FS=6.144V
#define DR         DR_7       //Data Rate = 860
#define COMP_QUE   COMP_QUE_3


unsigned int Config;
unsigned char Writebuff[5],Readbuff[4];
unsigned int Result[2]; 
int D_ADS; //×ª»»µÄÊý×ÖÁ¿
float VIN_DAS; //ÊäÈëµÄµçÑ¹Öµ
unsigned char  t_DAS; 
int  Format[5]={0};  //×ª»»µÄÊý×ÖÁ¿×ª»»³ÉÊ®½øÖÆ

/*******************************************
º¯ÊýÃû³Æ£ºdelay
¹¦    ÄÜ£ºÑÓÊ±Ô¼15usµÄÊ±¼ä
²Î    Êý£ºÎÞ
·µ»ØÖµ  £ºÎÞ
********************************************/
void Delay(void)
{
	delay_us(15);
}	

/******************ÑÓÊ±1msµÄÊ±¼ä*********************/
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //Ê¹ÄÜA¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //¸¡¿ÕÊäÈë
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ËÙ¶È50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //³õÊ¼»¯GPIOA3	
}
void PB11OUT()
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //Ê¹ÄÜA¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ËÙ¶È50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //³õÊ¼»¯GPIOA3	
}
void PB10OUT()
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //Ê¹ÄÜA¶Ë¿ÚÊ±ÖÓ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//ËÙ¶È50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //³õÊ¼»¯GPIOA3	
}
/*******************************************
º¯ÊýÃû³Æ£ºStart
¹¦    ÄÜ£ºÍê³ÉIICµÄÆðÊ¼Ìõ¼þ²Ù×÷
²Î    Êý£ºÎÞ
·µ»ØÖµ  £ºÎÞ
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
º¯ÊýÃû³Æ£ºStop
¹¦    ÄÜ£ºÍê³ÉIICµÄÖÕÖ¹Ìõ¼þ²Ù×÷
²Î    Êý£ºÎÞ
·µ»ØÖµ  £ºÎÞ
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
º¯ÊýÃû³Æ£ºACK
¹¦    ÄÜ£ºÍê³ÉIICµÄÖ÷»úÓ¦´ð²Ù×÷
²Î    Êý£ºÎÞ
·µ»ØÖµ  £ºÎÞ
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
º¯ÊýÃû³Æ£ºNACK
¹¦    ÄÜ£ºÍê³ÉIICµÄÖ÷»úÎÞÓ¦´ð²Ù×÷
²Î    Êý£ºÎÞ
·µ»ØÖµ  £ºÎÞ
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

/**********¼ì²éÓ¦´ðÐÅºÅº¯Êý******************/
/*Èç¹û·µ»ØÖµÎª1ÔòÖ¤Ã÷ÓÐÓ¦´ðÐÅºÅ£¬·´Ö®Ã»ÓÐ*/
/*******************************************
º¯ÊýÃû³Æ£ºCheck
¹¦    ÄÜ£º¼ì²é´Ó»úµÄÓ¦´ð²Ù×÷
²Î    Êý£ºÎÞ
·µ»ØÖµ  £º´Ó»úÊÇ·ñÓÐÓ¦´ð£º1--ÓÐ£¬0--ÎÞ
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
    slaveack = SDA_IN  //¶ÁÈëSDAÊýÖµ
    SCL_L;
    Delay();
    SDA_DDR_OUT;
    if(slaveack)    return FALSE;
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
        

 //     P6OUT=0xf5;  // 2¡¢4Î»ÁÁ    
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÏÂ·½*******************/      
	for(i=0;i<n;i++)
	{
		Write_1_Byte(*writebuffer);  
                
       //         P6OUT=0xf6;  // 1 4 Î»ÁÁ   
                 
		if(Check())
		{
			writebuffer ++;                                  
       //                 P6OUT=0x79;  // 2 8 Î»ÁÁ                
		}                         
		else
		{ 
                  
        //         P6OUT=0xeb;  // 3 5 Î»ÁÁ                 
			Stop();
			return DA ;
		}      
	}  
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÉÏ·½*******************/         
  //    P6OUT=0x7a;  // 1 8 Î»ÁÁ  
      
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
	SDA_DDR_IN; //¶Ë¿ÚÎªÊäÈë
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
void Read_N_Byte(unsigned int*readbuff,unsigned char n)
{
	unsigned char i;
	
	for(i=0;i<n;i++)
	{
		readbuff[i]=Read_1_Byte();
		if(i==n-1)
			NACK();  //²»Á¬Ðø¶Á×Ö½Ú
		else 
			ACK(); //Á¬Ðø¶Á×Ö½Ú
	}
	Stop();

}
void Config_Register()

/*****************³õÊ¼»¯******************/
void InitADS1115(int x)  //x ¶ÔÓ¦Ã¿Ò»¸öÆ÷¼þµØÖ·£¬°´ÕÕÅÅ±¬»úÆ÷ÈËµÄÉè¼Æ£¬Ó¦ÎªADDRES_0 1 3
{
    int deviceAddr;
  //  SCL_SEL;
   // SDA_SEL;
    SCL_DDR_OUT;
    SDA_DDR_OUT;
    SDA_H;
    switch(x)
    {
    case 0:deviceAddr=ADDRESS_0;break;
    case 1:deviceAddr=ADDRESS_1;break;
    case 2:return;   //Æ÷¼þ2 ²»ÓÃ
    case 3:deviceAddr=ADDRESS_3;break;
    }
    Config = OS_0+MUX_4+PGA_0+MODE_1+COMP_QUE_3;
    Writebuff[0]=deviceAddr|0x00;
    Writebuff[1]=Pointer_1;
	//	Writebuff[2]=deviceAddr;
    Writebuff[2]=Config/256;
    Writebuff[3]=Config%256;
    WriteWord();  
		delay_ms(1);
    Readbuff[0]=deviceAddr|0x00;
    Readbuff[1]=Pointer_1;            
		Readbuff[2]=deviceAddr|0x01;
		ReadWord();
}

/***************Write a Word***********************/
void WriteWord(void)
{
     int t=0;
                                                                                                                
  //   P6OUT=0x7f;  // ×î¸ßÎ»ÁÁ
     
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÏÂ·½*******************/       
     Start();   //Ð´Èë4¸ö×Ö½Ú
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÉÏ·½*******************/  
     
 //    P6OUT=0x3f;   //  ×î¸ßÁ½Î»ÁÁ
     
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÏÂ·½*******************/       
     do
     {
     t=Write_N_Byte(Writebuff,4);
     }while(t==0);
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÉÏ·½*******************/     
  //   P6OUT=0x1f;   //  ×î¸ßÈýÎ»ÁÁ
}

/***************Read Word***********************/
void ReadWord(void)
{
    int t;
    Start();  //Ð´Èë2¸ö×Ö½Ú
    
  //  P6OUT=0xfc;  //    µÍÁ½Î»ÁÁ  
  /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÏÂ·½*******************/    
//    do
//    {
//      t=Write_N_Byte(Readbuff,2);
//    }while(t==0);

//    Start();   //Ð´Èë2¸ö×Ö½Ú
  /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÉÏ·½*******************/    
   // P6OUT=0xf8;  //    µÍÈýÎ»ÁÁ   
    
//    do
//    {
//      t=Write_N_Byte(&Readbuff[2],1);
//    }while(t==0);
    
  //   P6OUT=0xf1;  //    µÚ2¡ª4 Î» ÁÁ    
   


   Write_1_Byte(*&Readbuff[2]);  
                
       //         P6OUT=0xf6;  // 1 4 Î»ÁÁ   
                 
		if(!Check()) //Ã»¼ì²âµ½ACK 
		{             
                
			Stop();
			return  ;
		}   
    Read_N_Byte(Result,2);  //¶Á³ö2¸ö×Ö½Ú

}

/***************ADS1115********************/
 
void ADS1115(int a)
{  


     
    InitADS1115(a);
    

  //   P6OUT=0xf0;       //µÍËÄÎ»ÁÁ  
 
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÏÂ·½*******************/      
    
    WriteWord(); 
    
     
 //   P6OUT=0xfe;       // ×îµÍÎ»ÁÁ
    
    delay_ms(1);
    ReadWord();
    
  /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀïÉÏ·½*******************/     
   
    //   P6OUT=0x07;    // ¸ßÎåÎ»ÁÁ  
	
    D_ADS=Result[0]*256+Result[1];  //×ª»»µÄÊý×ÖÁ¿
    t_DAS=0;
    ShowInt(D_ADS);    //×ª»»µÄÊý×ÖÁ¿×ª»»³ÉÊ®½øÖÆ
    VIN_DAS=6.144*D_ADS/32768;  //ÊäÈëµÄµçÑ¹Öµ
}
void ad1115test()
{
    WriteWord();
    Delay_1ms();
    ReadWord();
    D_ADS=Result[0]*256+Result[1];  //×ª»»µÄÊý×ÖÁ¿
    t_DAS=0;
    ShowInt(D_ADS);    //×ª»»µÄÊý×ÖÁ¿×ª»»³ÉÊ®½øÖÆ
    VIN_DAS=6.144*D_ADS/32768;  //ÊäÈëµÄµçÑ¹Öµ
}
//ÓÃµÝ¹é·½·¨½«ÕýÕûÊýx×ª»»Îª10½øÖÆ¸ñÊ½
void ShowInt(long int x)
{
	if(x)
	{
          Format[t_DAS]= x%10;
          t_DAS  ++;
          ShowInt(x/10);
	}
}
void adsfilter(int b)//ÖÐÎ»ÖµÆ½¾ùÂË²¨·¨   
{
  char count,i,j;
  char No=10;             //   Ò»´ÎÆ½¾ùÖµ  È¡Öµ×ÜÊý  
  float value_buf[10],temp;    //  Ã¿´ÎADÖµ Ëù´æ·ÅÊý×é
  float sum=0;
 /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀï*******************/    
  for (count=0;count<No;count++)
  {
    
    Delay();
    

   
    ADS1115(b);
  

   
    
    value_buf[count]=VIN_DAS;    
  }
  /*************************************³ÌÐò¿ÉÄÜ¿¨ÕâÀï*******************/   
  for (j=0;j<No;j++)
  {
    for (i=0;i<No-j;i++)
    {
      if (value_buf[i]>value_buf[i+1])
      {
        temp=value_buf[i];
        value_buf[i]=value_buf[i+1];
        value_buf[i+1]=temp;
      }      
    }
  }


  for (count=1;count<No-1;count++)
  {
    sum+=value_buf[count];
  }
  VIN_DAS=sum/(No-2);
  //sum=sum*1.492-35.55;//-0.0016*sum*sum;
  //sum=(uint)sum;

}
/**
 * @brief ads1115¿¿¿¿¿¿¿¿
 */
void yuedeAds1115PortInit(){
    SCL_DDR_OUT;                                                                
    SDA_DDR_OUT; 
    SDA_H;
}
/**
 * @brief ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
 * ¿¿¿¿¿¿ads1115¿¿¿¿¿
 * ¿¿¿3¿ads1115 ¿¿¿¿¿¿¿¿¿¿¿GND¿VCC¿SCL¿¿¿¿¿ADDRESS_0 1 3
 * ¿¿¿¿¿4¿¿¿¿¿¿¿¿¿¿¿GND¿¿¿¿¿¿¿¿MUX_4 5 6 7
 * ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿FSR¿¿6.144V¿¿¿¿128 SPS
 * ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿8¿¿¿¿¿ OS_1+ MUX_4¿or5 6 7¿+ PGA0 +MODE_1 = 0XC1
 * ¿8¿¿¿¿DR_7(860sps)+ COMP_MODE_0 + COMOP_POL_0 + COMP_LAT_0 + COM_QUE_3 = 0xe3
 * @param addr ¿¿¿¿¿¿
 * @param port ¿¿¿¿
 */
void ads1115ConfigRegister(unsigned char addr,unsigned char port){
    static unsigned char chnel,writeaddr;
    switch (addr) { 
        case 0: { writeaddr = ADDRESS_0; }//¿¿¿¿¿ads1115 
                break; 
        case 1: { writeaddr = ADDRESS_1;} //¿¿¿vcc¿¿¿  
                break; 
        case 2: { writeaddr = ADDRESS_2; }//¿¿¿SDA¿¿¿,¿¿¿¿¿¿¿¿¿¿¿  
                break; 
        default: { writeaddr = ADDRESS_3;} //¿¿¿SCL¿¿¿  
                 break; 
    } 
    switch (port)
    {
        case 0: chnel=0xC1; break;//¿¿¿¿¿¿¿AIN0¿GND¿¿¿6.144V¿¿¿¿¿
        case 1: chnel=0xD1; break;//¿¿¿¿¿AIN1¿GND¿¿¿¿¿
        case 2: chnel=0xE1; break;//¿¿¿¿¿AIN2¿GND¿¿¿¿¿
        case 3: chnel=0xF1; break;//¿¿¿¿¿AIN3¿GND¿¿¿¿¿
        default:;break; 
    }
    Writebuff[0] = writeaddr;
    Writebuff[1] = Pointer_1;
    Writebuff[2] = chnel;
    Writebuff[3] = 0xe3 ;  //860sps,¿¿¿¿¿,¿¿¿¿¿¿1.2ms
    WriteWord();
}
/**
 * @brief ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
 *
 * @param addr ¿¿¿¿¿¿¿¿¿
 */
static void PointRegister (unsigned char addr)
{
    static unsigned char writeaddr;
    switch (addr) { 
        case 0: { writeaddr = ADDRESS_0; }//¿¿¿¿¿ads1115 
                break; 
        case 1: { writeaddr = ADDRESS_1;} //¿¿¿vcc¿¿¿  
                break; 
        case 2: { writeaddr = ADDRESS_2; }//¿¿¿SDA¿¿¿,¿¿¿¿¿¿¿¿¿¿¿  
                break; 
        default: { writeaddr = ADDRESS_3;} //¿¿¿SDA¿¿¿  
                 break; 
    } 
    Writebuff[0] = writeaddr; //¿¿¿¿¿¿¿
    Writebuff[1] = Pointer_0; //¿¿¿¿¿¿¿
    WriteWord();  
}
static uint16_t ReadData (unsigned char chnnal1)
{  

    uint16_t  data;

    i2c_Start();     /////¿¿I2C  

        i2c_SendByte(CMD_Read);   /////¿¿¿¿¿
                ads1115_delay(20);
    i2c_WaitAck();      ////¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿

        ReadBuffer[0] = i2c_ReadByte();   ////¿¿¿¿¿¿
        i2c_Ack();   /////¿¿¿ADS1115¿¿¿¿¿¿
        ads1115_delay(200);

    ReadBuffer[1] = i2c_ReadByte(); ////¿¿¿¿¿¿
    i2c_Ack(); /////¿¿¿ADS1115¿¿¿¿¿¿
    ads1115_delay(200);

    i2c_Stop();   ////¿¿¿¿¿¿
        data = ReadBuffer[0]*256+ReadBuffer[1];  ////¿¿¿¿   
           return data;
}
float Get_ATOD (unsigned char channel)
{
        static unsigned char chn; 

chn = channel; 

  Confige1115(channel); ////¿¿ADS1115¿¿¿¿
      ads1115_delay(1000);
        PointRegister();  ////¿¿ADS1115¿¿¿¿¿¿¿¿¿¿¿¿¿
        ads1115_delay(1000); 
        data_get = ReadData(chn);  ////¿¿¿¿¿¿¿
        ads1115_delay(1000); 
/**¿¿¿¿¿¿¿¿¿¿¿¿8000~ffff,¿¿¿¿¿¿¿0¿¿¿¿¿¿¿¿¿¿¿¿¿+1¿¿**/
if(data_get>=0x8000)  
dianya=((float)(0xffff-data_get)/32768.0)*4.096;
else
dianya=((float)data_get/32768.0)*4.096;

return dianya;    
}
--------------------- 
¿¿¿DengFengLai123 
¿¿¿CSDN 
¿¿¿https://blog.csdn.net/dengfenglai123/article/details/72805739 
¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
