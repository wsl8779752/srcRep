/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   UART配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */


#ifndef __DRV_UART_H__
#define __DRV_UART_H__


#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

#ifndef uint8_t
#define uint8_t unsigned char
#endif
//串口硬件定义
#define UART_PORT						USART1
#define UART_PORT_CLK				RCC_APB2Periph_USART1
#define UART_PORT_AF				GPIO_Remap_USART1

//串口引脚定义
#define UART_TX_GPIO_PORT			GPIOA
#define UART_TX_GPIO_CLK			RCC_APB2Periph_GPIOA
#define UART_TX_GPIO_PIN			GPIO_Pin_9

#define UART_RX_GPIO_PORT			GPIOA
#define UART_RX_GPIO_CLK			RCC_APB2Periph_GPIOA
#define UART_RX_GPIO_PIN			GPIO_Pin_10

/************************************************************/
/***环形BUF定义头********************************************/

#define GPrx_LEN 96     //环形BUFF 长度
#define last_function_code 0x0f  //功能码最长
#define RINGBUFFER_FRAME_HAED 0XA8A8  //协议帧头
#define  RINGBUFFER_FRAME_TAIL 0XAEAE //协议帧尾
#define  FRAME_HAED_TO_FUNCTION_CODE_DISTANCE 5//协议帧头到功能吗距离5
#define  FRAME_HAED_TO_LENGTH_DISTANCE 6     //协议帧头到协议长度６
#define  FRAME_LENGTH_EXCEPT_DATA    9  //协议中除数据外的其他部分长度

typedef struct{
    uint8_t RxData[Gprx_LEN];
    uint8_t RxLength;
    uint8_t head;
    uint8_t tail;
}DsUsart;

int fputc(int ch,FILE *f) ;

void drv_uart_init( uint32_t UartBaudRate );
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );
int deal_uart_data(void);


#endif



