/**
  ******************************************************************************
  * @author  SHSD  weishulin
  * @version V3.0
  * @date    2017-3-20
  * @brief   UART配置C文件
  ******************************************************************************  
  */


#include "drv_uart.h"
#include "string.h"
DsUsart sUsart1 = {{0},GPrx_LEN,0,0};
#pragma import(__use_no_semihosting)             
//±ê×¼¿âÐèÒªµÄÖ§³Öº¯Êý                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//¶¨Òå_sys_exit()ÒÔ±ÜÃâÊ¹ÓÃ°ëÖ÷»úÄ£Ê½    
int _sys_exit(int x) 
{ 
	x = x; 
	return 1;
} 
//ÖØ¶¨Òåfputcº¯Êý 


int fputc(int ch,FILE *f)
{
	USART_SendData(UART_PORT,(u8)ch);
	while(USART_GetFlagStatus(UART_PORT,USART_FLAG_TXE)==RESET);
	return ch;
}



/**
  * @brief :串口初始化
  * @param :
  *			@UartBaudRate:串口波特率
  * @note  :无
  * @retval:无
  */
void drv_uart_init( uint32_t UartBaudRate )
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//   Ê¹ÄÜUSART1£¬GPIOAÊ±ÖÓ
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//¸´ÓÃÍÆÍìÊä³ö
  GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIOA.9
   
  //USART1_RX	  GPIOA.10³õÊ¼»¯
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//¸¡¿ÕÊäÈë
  GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIOA.10  

  //Usart1 NVIC ÅäÖÃ
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//ÇÀÕ¼ÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾ÝÖ¸¶¨µÄ²ÎÊý³õÊ¼»¯VIC¼Ä´æÆ÷
  
   //USART ³õÊ¼»¯ÉèÖÃ

	USART_InitStructure.USART_BaudRate =UartBaudRate;//´®¿Ú²¨ÌØÂÊ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//×Ö³¤Îª8Î»Êý¾Ý¸ñÊ½
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//Ò»¸öÍ£Ö¹Î»
	USART_InitStructure.USART_Parity = USART_Parity_No;//ÎÞÆæÅ¼Ð£ÑéÎ»
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ÎÞÓ²¼þÊý¾ÝÁ÷¿ØÖÆ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ÊÕ·¢Ä£Ê½

  USART_Init(USART1, &USART_InitStructure); //³õÊ¼»¯´®¿Ú1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//¿ªÆô´®¿Ú½ÓÊÜÖÐ¶Ï
  USART_Cmd(USART1, ENABLE);                    //Ê¹ÄÜ´®¿Ú1 

	
}

/**
  * @brief :串口发送数据
  * @param :
  *			@TxBuffer:发送数据首地址
  *			@Length:数据长度
  * @note  :无
  * @retval:无
  */
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length )
{
	while( Length-- )
	{
		while( RESET == USART_GetFlagStatus( UART_PORT, USART_FLAG_TXE ));
		UART_PORT->DR = *TxBuffer;
		TxBuffer++;
	}
}

/**
  * @brief :串口接收数据
  * @param :
  *			@RxBuffer:发送数据首地址
  * @note  :无
  * @retval:接收到的字节个数
  */
int deal_uart_data(void)
{
	uint8_t sumcheck=0;
	uint8_t i=0,Total_Pkt_Len;
	if (sUsart1.tail==sUsart1.head) return 0;  //未接收到数据

	if(((sUsart1.tail+sUsart1.rxLength-sUsart1.head)%sUsart1.rxLength)<3)  return 0;    //接受的数据长度小于2，说明没接受完，直接返回
	
	if ((sUsart1.rxData[sUsart1.head]!=0xA8) || (sUsart1.rxData[(sUsart1.head+sUsart1.rxLength-1)%sUsart1.rxLength]!=0xA8))   //判断是否帧头
	{
		sUsart1.head = (sUsart1.head+1)%sUsart1.rxLength;		 
		return 0;
	}
	
	if(((sUsart1.tail+sUsart1.rxLength-sUsart1.head)%sUsart1.rxLength)<9)  return 0;    //接受的数据长度小于9，说明没接受完，直接返回
	
	if (sUsart1.rxData[(sUsart1.head+ FRAME_HAED_TO_FUNCTION_CODE_DISTANCE )%sUsart1.rxLength]>last_function_code)	                //如果功能码不再范围内
	{
		sUsart1.head = (sUsart1.head+1)%sUsart1.rxLength;		 
		return 0;
	}
	
	Total_Pkt_Len = sUsart1.rxData[( sUsart1.head+FRAME_HAED_TO_LENGTH_DISTANCE )%sUsart1.rxLength ]+FRAME_LENGTH_EXCEPT_DATA ;                          //如果以上都满足，说明收到了数据长度，取出数据总长度

	if(((sUsart1.tail+sUsart1.rxLength-sUsart1.head)%sUsart1.rxLength)<Total_Pkt_Len)  return 0;			 //检测数据长度对不对

	if((sUsart1.rxData[(sUsart1.head+Total_Pkt_Len-2)%sUsart1.rxLength]==(RINGBUFFER_FRAME_TAIL>>8) && (sUsart1.rxData[(sUsart1.head+Total_Pkt_Len-1)%sUsart1.rxLength]==(uint8_t)RINGBUFFER_FRAME_TAIL)))								  // 数据长度对的话，检测帧尾对不对
	{
		
		for(i=1;i<Total_Pkt_Len-3;i++)																					 					 //帧尾对的话，检测和校验
		{
			sumcheck+=sUsart1.rxData[(sUsart1.head+i)%sUsart1.rxLength];
		}		
		if(sumcheck==sUsart1.rxData[(sUsart1.head+Total_Pkt_Len-3)%sUsart1.rxLength])							        //和校验对的话，将数据从buf 中取出，并开始发送
		{ 			
			for(i=0;i<Total_Pkt_Len-3;i++)   //去头除尾计算和校验
			{
				g_RF24LO1TxBuffer[i]=sUsart1.rxData[(sUsart1.head+i+1)%sUsart1.rxLength];
			}
		
			//memcpy(g_RF24LO1TxBuffer,&sUsart1.rxData[sUsart1.head+1],Total_Pkt_Len) ;    //由于头指针会指向环形数组尾部，所以不能用memcpy 函数
			sUsart1.head = (sUsart1.head+Total_Pkt_Len)%sUsart1.rxLength;			
			return 1;
	  }
    else
		{
			sUsart1.head = (sUsart1.head+1)%sUsart1.rxLength;
			return 0;
		}
	}
	else
	{
			sUsart1.head = (sUsart1.head+1)%sUsart1.rxLength;
			return 0;
	}	
}


void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	{
		USART_ClearFlag(USART1, USART_FLAG_ORE);
		USART_ReceiveData(USART1);
		return;
	}

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
//		if(USART_GetFlagStatus(USART1, USART_FLAG_NF) != RESET)
//		{
//			USART_ClearFlag(USART1, USART_FLAG_NF);
//		}
		if(USART_GetFlagStatus(USART1, USART_FLAG_FE) != RESET)
		{
			USART_ClearFlag(USART1, USART_FLAG_FE);
		}
		if(USART_GetFlagStatus(USART1, USART_FLAG_PE) != RESET)
		{
			USART_ClearFlag(USART1, USART_FLAG_PE);
		}
		
		if(((sUsart1.tail+1)%sUsart1.rxLength) == sUsart1.head) //尾追上头了，空间满了，只接收，不对数据处理；
		{
			USART_ReceiveData(USART1);
			return ;
		}
		else
		{
			sUsart1.rxData[sUsart1.tail]=USART_ReceiveData(USART1);//向队列中添加数据；
			sUsart1.tail =(sUsart1.tail+1)%sUsart1.rxLength;//尾指针自增；0-sUsart1.rxLength  循环
			if((sUsart1.rxData[sUsart1.head]!=0xA8) || (sUsart1.rxData[(sUsart1.head+sUsart1.rxLength-1)%sUsart1.rxLength]!=0xA8))//判断是否是帧头
			{
				sUsart1.head = (sUsart1.head+1)%sUsart1.rxLength;		 //如果不是帧头，则头指针自增；
				return ;
			}		
			return ;
		}
		
	}
}


	
