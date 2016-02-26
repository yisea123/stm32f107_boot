#include "lsys.h"
#include "usart.h"
#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
#include "includes.h"  
#include "port.h" 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if DEBUG_PRINTF
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 
//
//}; 
//
//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
            USART3->DR = (u8) ch;  
            
	return ch;
}
#else

int fputc(int ch, FILE *f)
{      
      return ch;
}

#endif 

/*
//72M
//n=2000 T=392us
//n=1000 T=196us
//n=500  T=98us
//n=100  T=20.6us
*/ 
void Delay_us(uint32_t n)
{ 
	uint32_t m=0;
        m=n*50;
	
	while(m)
	{
            m--;
	}	
}
 

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	//GPIOC AFIO时钟
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);          //使能USART3
        
        GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
        
        
 	USART_DeInit(USART3);  //复位串口3
	 //USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PB10
   
    //USART3_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PB11
    
#ifdef USART3_TRX_EN
    RCC_APB2PeriphClockCmd(USART3_TRX_RCC, ENABLE); 
    
    GPIO_InitStructure.GPIO_Pin = USART3_TRX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART3_TRX_GPIO , &GPIO_InitStructure);

#ifdef DEBUG_PRINTF
    USART3_TRX_CONTROL = 1;
#else
    USART3_TRX_CONTROL = 0;
#endif
#endif    
    

   //Usart3 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART3, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART3, USART_IT_RXNE , ENABLE);//开启中断
    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    USART_Cmd(USART3, ENABLE);                    //使能串口 

}

void USART3_SEND(u8 * str,int len)
{
    USART3_TRX_CONTROL = 1;
    Delay_us(4000);
    
    for(int t = 0;t < len; t++)
    {      
      USART3->DR = (u8) str[t];
      while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
       
    }
    
//    if(USART_GetITStatus(USART1, USART_IT_TC) == SET)
//    {
        USART3_TRX_CONTROL = 0;
//    }
}


#ifndef MODBUS_RTU_TEST

#if EN_USART3_RX   //如果使能了接收
void USART3_IRQHandler(void)                	//串口3中断服务程序
{
  u8 Res;
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
  {
 
      Res =USART_ReceiveData(USART3);
      if((USART_RX_STA&0x8000)==0)//接收未完成
      {
          if(USART_RX_STA&0x4000)//接收到了0x0d
          {
              if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
              else 
              {
                  USART_RX_STA|=0x8000;	//接收完成了 
//                  USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
//                  USART3_TRX_CONTROL = 1;
              }
          }
          else //还没收到0X0D
          {	
              if(Res==0x0d)USART_RX_STA|=0x4000;
              else
              {
                  USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
                  USART_RX_STA++;
                  if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
              }		 
          }
      }      
      
  }
} 
#endif	
#endif

#if MODBUS_RTU_TEST
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{		
		prvvUARTRxISR();
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}

	if(USART_GetITStatus(USART3, USART_IT_TXE) == SET)
	{
		prvvUARTTxReadyISR();
// 		USART_ClearITPendingBit(USART1, USART_IT_TXE);
	}
}

#endif