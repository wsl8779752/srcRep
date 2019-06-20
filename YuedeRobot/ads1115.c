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
#define DA     -1  //¿¿¿¿

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
    if(slaveack)    return FALSE; //¿¿¿¿¿¿
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
                 
		if(Check()==TRUE)
		{
			writebuffer ++;                                  
       //                 P6OUT=0x79;  // 2 8 Î»ÁÁ                
		}                         
		else
		{ 
        //         P6OUT=0xeb;  // 3 5 Î»ÁÁ                 
			Stop();
			return FALSE ;
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
void Read_N_Byte(unsigned char *readbuff,unsigned char n)
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
unsigned char ads1115ConfigRegister(unsigned char writeaddr,unsigned char chnel){
    Writebuff[0] = writeaddr;
    Writebuff[1] = Pointer_1;
    Writebuff[2] = chnel;
    Writebuff[3] = 0xe3 ;  //860sps,¿¿¿¿¿,¿¿¿¿¿¿1.2ms
    Start();
    return Write_N_Byte(Writebuff,4);
}
/**
 * @brief ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
 *
 * @param addr ¿¿¿¿¿¿¿¿¿
 */
 unsigned char PointRegister (unsigned char writeaddr) {
    Writebuff[0] = writeaddr; //¿¿¿¿¿¿¿
    Writebuff[1] = Pointer_0; //¿¿¿¿¿¿¿
    Start();
    return Write_N_Byte(Writebuff,2);
}
unsigned char ads1115ReadData ( unsigned char readaddr,unsigned char *ans) {  
    Start();
    Write_1_Byte(readaddr);  
    if(Check()!= TRUE)
    {             
        Stop();
        return FALSE;
    }   
    Read_N_Byte(ans,2);  //¶Á³ö2¸ö×Ö½Ú
    return TRUE;
}
/**
 * @brief ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿ans¿¿¿¿¿¿
 *
 * @param addr //¿¿¿¿ 0 1 2 3
 * @param channel //¿¿0 1 2 3
 * @param ans //¿¿¿¿¿AD¿
 *
 * @return ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
 * ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿FALSE
 */
unsigned int ads1115GetAD (unsigned char addr, unsigned char channel,unsigned char *ans)
{
    switch (addr){ 
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
    if( ads1115ConfigRegister(writeaddr,chnel) !=TRUE)
        return FALSE; //¿¿¿¿¿¿¿
    delay_us(1300) ;//¿¿1.3ms¿¿¿¿¿¿¿
    if(PointRegister(writeaddr) != TRUE ) return FALSE;
    return ads1115ReadData(writeaddr+1,chenl,ans);
}
