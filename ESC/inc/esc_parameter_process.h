/*******************************************************************************
* File Name          : esc_parameter_process.h
* Author             : lison
* Version            : V1.0
* Date               : 07/15/2016
* Description        : This file contains prototype of esc parameter process.
*			          
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ESC_PARAMETER_PROCESS_H
#define __ESC_PARAMETER_PROCESS_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define MESSAGE_TO_CPU      0x11
#define MESSAGE_TO_CONTROL      0x22
#define USB_DETECTED        0x01
#define USB_NOT_DETECTED        0x02
#define SAFETY_PARAMETER_LOADED        0x10
#define CONTROL_PARAMETER_LOADED        0x20
#define PARAMETER_ERROR        0x03
#define PARAMETER_CORRECT        0x04
#define SAFETY_PARAMETER_NOT_EXIST        0x05
#define CONTROL_PARAMETER_NOT_EXIST        0x06
#define SAFETY_PARAMETER_EXIST        0x07
#define CONTROL_PARAMETER_EXIST        0x08
#define SEND_PARAMETER        0x09
#define RECEIVE_PARAMETER        0x0A
#define PARAMETER_LOADED_FINSH        0x0B

/* Exported functions ------------------------------------------------------- */
void ParametersLoading(void);


#endif  /* __ESC_PARAMETER_PROCESS_H */


/******************************  END OF FILE  *********************************/



