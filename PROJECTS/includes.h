/*******************************************************************************
* File Name          : includes.h
* Author             : lison
* Version            : V1.0
* Date               : 03/24/2016
* Description        : 
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __INCLUDES_H
#define  __INCLUDES_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#ifdef GEC_CB_MAIN
/*************************  TEST    *******************************************/
#define TCP_SERVER_TEST    0

#define MODBUS_TCP_TEST    0

#define MODBUS_RTU_TEST    1

#define USB_HOST_MASS_STORAGE_TEST      0

#define INPUT_RELAY_OUTPUT_AND_CAN_TEST    0

#define RX485_TEST      0

#define RTC_CLOCK_TEST          0
/*************************  TEST    *******************************************/
#if RTC_CLOCK_TEST
#define DEBUG_PRINTF                1
#else
#define DEBUG_PRINTF                0
#endif /* RTC_CLOCK_TEST */
#endif /* GEC_CB_MAIN */

/* Exported functions ------------------------------------------------------- */




#endif /* __INCLUDES_H */


/******************************  END OF FILE  *********************************/   

