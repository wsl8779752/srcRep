#include "ads1115.h"
#include "delay.h"
/************************************
 *   ADDR(1)---> GND
 *   VDD (8)---> 3.3V
 *   SCL(10) ---> PB10
 *   SDA(9) ---> PB11
 *   AINp=AIN0, AINn=GND
 ************************************/
/***************引脚定义*************                         ****/
#define SCL              0x40
#define SDA              0x80

#define SCL_DDR_OUT  	 PB10OUT()//P5DIR |= SCL       // 设置为输出
#define SCL_H 		GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define SCL_L	 	GPIO_ResetBits(GPIOB,GPIO_Pin_10)

#define SDA_DDR_OUT   	PB11OUT() //P5DIR |= SDA        // 设置为输出
#define SDA_DDR_IN               PB11IN()  //P5DIR &=  ~SDA      // 设置为输入
#define SDA_IN                   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);   // 读取 输入电平
#define SDA_H    	 GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define SDA_L	  	 GPIO_ResetBits(GPIOB,GPIO_Pin_11)

#define TRUE   1
#define FALSE  0
#define DA     -1  //靠靠

/*************ADDR Initial********************/
#define ADDRESS    ADDRESS_0   //ADDR PIN ->GND
#define ADDRESS_W  ADDRESS|0x00  //写地址
#define ADDRESS_R  ADDRESS|0x01    //读地址

/*************Config Initial*********************/
#define OS         OS_1
#define PGA        PGA_0     //FS=6.144V
#define DR         DR_7       //Data Rate = 860
#define COMP_QUE   COMP_QUE_3

unsigned int Config;
unsigned char Writebuff[5],Readbuff[4];
unsigned int Result[2]; 
int D_ADS; //转换的数字量
float VIN_DAS; //输入的电压值
unsigned char  t_DAS; 
int  Format[5]={0};  //转换的数字量转换成十进制

/*******************************************
函数名称：delay
功    能：延时约15us的时间
参    数：无
返回值  ：无
********************************************/
void Delay(void)
{
	delay_us(15);
}	

/******************延时1ms的时间*********************/
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA3	
}
void PB11OUT()
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA3	
}
void PB10OUT()
{
 	GPIO_InitTypeDef  GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOA3	
}
/*******************************************
函数名称：Start
功    能：完成IIC的起始条件操作
参    数：无
返回值  ：无
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
函数名称：Stop
功    能：完成IIC的终止条件操作
参    数：无
返回值  ：无
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
函数名称：ACK
功    能：完成IIC的主机应答操作
参    数：无
返回值  ：无
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
函数名称：NACK
功    能：完成IIC的主机无应答操作
参    数：无
返回值  ：无
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

/**********检查应答信号函数******************/
/*如果返回值为1则证明有应答信号，反之没有*/
/*******************************************
函数名称：Check
功    能：检查从机的应答操作
参    数：无
返回值  ：从机是否有应答：1--有，0--无
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
    slaveack = SDA_IN  //读入SDA数值
    SCL_L;
    Delay();
    SDA_DDR_OUT;
    if(slaveack)    return FALSE; //靠靠靠
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
 //     P6OUT=0xf5;  // 2、4位亮    
 /*************************************程序可能卡这里下方*******************/      
	for(i=0;i<n;i++)
	{
		Write_1_Byte(*writebuffer);  
                
       //         P6OUT=0xf6;  // 1 4 位亮   
                 
		if(Check()==TRUE)
		{
			writebuffer ++;                                  
       //                 P6OUT=0x79;  // 2 8 位亮                
		}                         
		else
		{ 
        //         P6OUT=0xeb;  // 3 5 位亮                 
			Stop();
			return FALSE ;
 /*************************************程序可能卡这里上方*******************/         
  //    P6OUT=0x7a;  // 1 8 位亮  
      
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
        SDA_DDR_IN; //端口为输入
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
			NACK();  //不连续读字节
		else 
			ACK(); //连续读字节
	}
	Stop();
}
/**
 * @brief ads1115靠靠靠靠
 */
void yuedeAds1115PortInit(){
    SCL_DDR_OUT;                                                                
    SDA_DDR_OUT; 
    SDA_H;
}
/**
 * @brief 靠靠靠靠靠靠靠靠�
 * 靠靠靠ads1115靠靠�
 * 靠�3縜ds1115 靠靠靠靠靠縂ND縑CC縎CL靠靠緼DDRESS_0 1 3
 * 靠靠�4靠靠靠靠靠縂ND靠靠靠靠MUX_4 5 6 7
 * 靠靠靠靠靠靠靠靠靠靠靠縁SR靠6.144V靠靠128 SPS
 * 靠靠靠靠靠靠靠靠靠8靠靠� OS_1+ MUX_4縪r5 6 7�+ PGA0 +MODE_1 = 0XC1
 * �8靠靠DR_7(860sps)+ COMP_MODE_0 + COMOP_POL_0 + COMP_LAT_0 + COM_QUE_3 = 0xe3
 * @param addr 靠靠靠
 * @param port 靠靠
 */
unsigned char ads1115ConfigRegister(unsigned char writeaddr,unsigned char chnel){
    Writebuff[0] = writeaddr;
    Writebuff[1] = Pointer_1;
    Writebuff[2] = chnel;
    Writebuff[3] = 0xe3 ;  //860sps,靠靠�,靠靠靠1.2ms
    Start();
    return Write_N_Byte(Writebuff,4);
}
/**
 * @brief 靠靠靠靠靠靠靠靠靠靠靠�
 *
 * @param addr 靠靠靠靠�
 */
 unsigned char PointRegister (unsigned char writeaddr) {
    Writebuff[0] = writeaddr; //靠靠靠�
    Writebuff[1] = Pointer_0; //靠靠靠�
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
    Read_N_Byte(ans,2);  //读出2个字节
� � return TRUE;
}
/**
 * @brief 靠靠靠靠靠靠靠靠靠靠靠靠靠ans靠靠靠
 *
 * @param addr //靠靠 0 1 2 3
 * @param channel //靠0 1 2 3
 * @param ans //靠靠緼D�
 *
 * @return 靠靠靠靠靠靠靠靠靠靠靠靠靠靠靠靠
 * 靠靠靠靠靠靠靠靠靠靠靠靠FALSE
 */
unsigned int ads1115GetAD (unsigned char addr, unsigned char channel,unsigned char *ans)
{
    switch (addr){ 
        case 0: { writeaddr = ADDRESS_0; }//靠靠縜ds1115 
                break; 
        case 1: { writeaddr = ADDRESS_1;} //靠縱cc靠�  
                break; 
        case 2: { writeaddr = ADDRESS_2; }//靠縎DA靠�,靠靠靠靠靠�  
                break; 
        default: { writeaddr = ADDRESS_3;} //靠縎CL靠�  
                 break; 
    } 
    switch (port)
    {
        case 0: chnel=0xC1; break;//靠靠靠緼IN0縂ND靠�6.144V靠靠�
        case 1: chnel=0xD1; break;//靠靠緼IN1縂ND靠靠�
        case 2: chnel=0xE1; break;//靠靠緼IN2縂ND靠靠�
        case 3: chnel=0xF1; break;//靠靠緼IN3縂ND靠靠�
        default:;break; 
    }
    if( ads1115ConfigRegister(writeaddr,chnel) !=TRUE)
        return FALSE; //靠靠靠�
    delay_us(1300) ;//靠1.3ms靠靠靠�
    if(PointRegister(writeaddr) != TRUE ) return FALSE;
    return ads1115ReadData(writeaddr+1,chenl,ans);
}
