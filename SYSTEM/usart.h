#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "lsys.h" 
	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收

#define EN_USART3_PRINTF                0


#define USART3_TRX_EN         	1


#ifdef USART3_TRX_EN
#define USART3_TRX_GPIO        	GPIOB
#define USART3_TRX_RCC         	RCC_APB2Periph_GPIOB
#define USART3_TRX_PIN        	GPIO_Pin_14	

#define USART3_TRX_CONTROL      PBout(14)
#endif
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void USART3_SEND(u8 * str,int len);
#endif


