/*******************************************************************************
* File Name          : includes.h
* Author             : lison
* Version            : V1.0
* Date               : 03/24/2016
* Description        : This file contains includes file and define.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __INCLUDES_H
#define  __INCLUDES_H

/* Includes ------------------------------------------------------------------*/
#include "lsys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"  
#include "malloc.h" 
#include "ff.h"  
#include "exfuns.h"     
#include "usbh_usr.h" 
#include "24cxx.h"
#include "mb85rcxx.h"
#include "digital_led.h"
#include "ewdt.h"
#include "update.h"
#include "iap.h"
#include "rtc.h"
#include "usb_task.h"
#include "sys_task.h"
#ifdef GEC_CB_MAIN
#include "hw_test.h"
#include "can.h"
#include "freertos_lwip.h" 
#include "modbusTask.h"
#include "stm32f10x_STLlib.h"
#include "stm32f10x_STLclassBvar.h"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#ifdef GEC_CB_MAIN

#define USE_FREERTOS_OS        1

/* number is big, priority is big */
#define LED_TASK_PRIO			( tskIDLE_PRIORITY + 9 )
#define USB_THREAD_PRIO                 ( tskIDLE_PRIORITY + 7 )
#define RX485_THREAD_PRIO               ( tskIDLE_PRIORITY + 2 )
#define RTC_THREAD_PRIO                 ( tskIDLE_PRIORITY + 2 )
#define TCP_TASK_PRIO			( tskIDLE_PRIORITY + 5 )
#define DHCP_TASK_PRIO                  ( tskIDLE_PRIORITY + 8 ) 
#define INPUT_TASK_PRIO                 ( tskIDLE_PRIORITY + 6 )
#define SELFCHEK_TASK_PRIO              ( tskIDLE_PRIORITY + 8 )
#define CAN_THREAD_PRIO                 ( tskIDLE_PRIORITY + 6 )

/*************************  TEST    *******************************************/
#define ETH_LWIP_TEST    1

#define TCP_CLIENT_TEST    0

#define TCP_SERVER_TEST    0

#define MODBUS_TCP_TEST    1

#define MODBUS_RTU_TEST    0

#define USB_HOST_MASS_STORAGE_TEST      0

#define INPUT_RELAY_OUTPUT_AND_CAN_TEST    1

#define RX485_TEST      0

#define RTC_CLOCK_TEST          1

#define MODBUS_LOCAL_DDU_TEST   1
/*************************  TEST    *******************************************/
#define DEBUG_PRINTF                0
#endif /* GEC_CB_MAIN */

/* Exported functions ------------------------------------------------------- */

#ifdef GEC_CB_MAIN
extern u8 testmode;
extern u8 timeset;
#endif

#endif /* __INCLUDES_H */


/******************************  END OF FILE  *********************************/   

