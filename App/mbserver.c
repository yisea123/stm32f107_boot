/*
 * FreeModbus Libary: STM32F10X Port
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: mbserver.c,v 1.1 2014/08/31 23:15:18 wolti Exp $
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "mbutils.h"

#include "hw_test.h"

/* ----------------------- Defines ------------------------------------------*/
// ����Ĵ�����ʼ��ַ
#define REG_INPUT_START      1
 // ����Ĵ�������
#define REG_INPUT_NREGS      16

// ���ּĴ�����ʼ��ַ
#define	REG_HOLD_START	      1
// ���ּĴ�������
#define REG_HOLD_NREGS	      16

// ��Ȧ��ʼ��ַ
#define REG_COILS_START       1    
// ��Ȧ����
#define REG_COILS_SIZE        16                    

// ���ؼĴ�����ʼ��ַ
#define REG_DISCRETE_START    1    
// ���ؼĴ�������
#define REG_DISCRETE_SIZE     16                    
/* ----------------------- Static variables ---------------------------------*/
// �Ĵ�����ʼ��ַ
static USHORT   usRegInputStart = REG_INPUT_START;
// ����Ĵ�������
static USHORT   usRegInputBuf[REG_INPUT_NREGS] = {0};//{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
// ���ּĴ�����ʼ��ַ
static USHORT   usRegHoldStart =  REG_HOLD_START;
// ���ּĴ�������
static USHORT   usRegHoldBuf[REG_HOLD_NREGS]  = {0};//{16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
// ��Ȧ״̬
static UCHAR ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x00};//{0xFF, 0x55};
// ����״̬
static UCHAR ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x00};//{0xAA,0xFF};

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInputStart );
        usRegInputBuf[0] = IN1;
        usRegInputBuf[1] = IN2;
        usRegInputBuf[2] = IN3;
        usRegInputBuf[3] = IN4;
        usRegInputBuf[4] = IN5;
        usRegInputBuf[5] = IN6;
        usRegInputBuf[6] = IN7;
        usRegInputBuf[7] = IN8;
        usRegInputBuf[8] = IN9;
        usRegInputBuf[9] = IN10;
        usRegInputBuf[10] = IN11;
        usRegInputBuf[11] = IN12;        
        usRegInputBuf[12] = IN13;
        usRegInputBuf[13] = IN14; 
        usRegInputBuf[14] = IN15;
        usRegInputBuf[15] = IN16;        
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if( ( usAddress >= REG_HOLD_START )
        && ( usAddress + usNRegs <= REG_HOLD_START + REG_HOLD_NREGS ) )
    {
      
        iRegIndex = ( int )( usAddress - usRegHoldStart );
        
		switch(eMode)
		{
                    case MB_REG_READ:
                        while( usNRegs > 0 )
                        {
                            *pucRegBuffer++ = ( unsigned char )( usRegHoldBuf[iRegIndex] >> 8 );
                            *pucRegBuffer++ = ( unsigned char )( usRegHoldBuf[iRegIndex] & 0xFF );
                            iRegIndex++;
                            usNRegs--;
                        }
			break;
                    case MB_REG_WRITE:
			while(usNRegs > 0 )
			{
                            usRegHoldBuf[iRegIndex] = *pucRegBuffer++;
                            usRegHoldBuf[iRegIndex] <<= 8;
                            usRegHoldBuf[iRegIndex]|= *pucRegBuffer++;
                            iRegIndex++;
                            usNRegs--;	
			}
                        {
                            GRL1 = usRegHoldBuf[0];
                            GRL2 = usRegHoldBuf[1];
                            GRL3 = usRegHoldBuf[2];
                            GRL4 = usRegHoldBuf[3];
                            GRL5 = usRegHoldBuf[4];
                            GRL6 = usRegHoldBuf[5];
                            GRL7 = usRegHoldBuf[6];
                            GRL8 = usRegHoldBuf[7];
                            GRL9 = usRegHoldBuf[8];
                            GSFR1 = usRegHoldBuf[9];       
                            GSFR2 = usRegHoldBuf[10];
                            GSFR3 = usRegHoldBuf[11];
                            GSFR4 = usRegHoldBuf[12];
                            TRANS_CTRL1 = usRegHoldBuf[13];
                            TRANS_CTRL2 = usRegHoldBuf[14];
                        }
			break;
		}
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}


eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
              eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    short           iNCoils = ( short )usNCoils;
    unsigned short  usBitOffset;
    
    if( ( usAddress >= REG_COILS_START ) &&
       ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
    {
        usBitOffset = ( unsigned short )( usAddress - REG_COILS_START );
        switch ( eMode )
        {
            
        case MB_REG_READ:
//            if( iNCoils > 0 )
//            {
//                ucRegCoilsBuf[0] = 0x00;
//                ucRegCoilsBuf[1] = 0x00;
//                
//                ucRegCoilsBuf[0] |= IN1 << 0;
//                ucRegCoilsBuf[0] |= IN2 << 1;
//                ucRegCoilsBuf[0] |= IN3 << 2;
//                ucRegCoilsBuf[0] |= IN4 << 3;
//                ucRegCoilsBuf[0] |= IN5 << 4;
//                ucRegCoilsBuf[0] |= IN6 << 5;
//                ucRegCoilsBuf[0] |= IN7 << 6;
//                ucRegCoilsBuf[0] |= IN8 << 7;
//                
//                ucRegCoilsBuf[1] |= IN9  << 0;
//                ucRegCoilsBuf[1] |= IN10 << 1;
//                ucRegCoilsBuf[1] |= IN11 << 2;
//                ucRegCoilsBuf[1] |= IN12 << 3;       
//                ucRegCoilsBuf[1] |= IN13 << 4;
//                ucRegCoilsBuf[1] |= IN14 << 5; 
//                ucRegCoilsBuf[1] |= IN15 << 6;
//                ucRegCoilsBuf[1] |= IN16 << 7; 
//            }
            while( iNCoils > 0 )
            {
                *pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,
                                                 ( unsigned char )( iNCoils > 8 ? 8 : iNCoils ) );
                iNCoils -= 8;
                usBitOffset += 8;
            }
            break;
            
        case MB_REG_WRITE:       
            while( iNCoils > 0 )
            {
                xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,
                               ( unsigned char )( iNCoils > 8 ? 8 : iNCoils ),
                               *pucRegBuffer++ );
                iNCoils -= 8;
                usBitOffset += 8;
            }
            {
              
                GRL1 = (ucRegCoilsBuf[0]&0x01) >> 0;
                GRL2 = (ucRegCoilsBuf[0]&0x02) >> 1;
                GRL3 = (ucRegCoilsBuf[0]&0x04) >> 2;
                GRL4 = (ucRegCoilsBuf[0]&0x08) >> 3;
                GRL5 = (ucRegCoilsBuf[0]&0x10) >> 4;
                GRL6 = (ucRegCoilsBuf[0]&0x20) >> 5;
                GRL7 = (ucRegCoilsBuf[0]&0x40) >> 6;
                GRL8 = (ucRegCoilsBuf[0]&0x80) >> 7;
                GRL9 = (ucRegCoilsBuf[1]&0x01) >> 0;
                GSFR1 = (ucRegCoilsBuf[1]&0x02) >> 1;
                GSFR2 = (ucRegCoilsBuf[1]&0x04) >> 2;
                GSFR3 = (ucRegCoilsBuf[1]&0x08) >> 3;
                GSFR4 = (ucRegCoilsBuf[1]&0x10) >> 4;
                TRANS_CTRL1 = (ucRegCoilsBuf[1]&0x20) >> 5;
                TRANS_CTRL2 = (ucRegCoilsBuf[1]&0x40) >> 6;

            }              
            break;
        }
        
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    short           iNDiscrete = ( short )usNDiscrete;
    unsigned short  usBitOffset;
    
    if( ( usAddress >= REG_DISCRETE_START ) &&
       ( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
    {
        usBitOffset = ( unsigned short )( usAddress - REG_DISCRETE_START );
        
        if( iNDiscrete > 0 )
        {
          ucRegDiscreteBuf[0] = 0x00;
          ucRegDiscreteBuf[1] = 0x00;
          
          ucRegDiscreteBuf[0] |= IN1 << 0;
          ucRegDiscreteBuf[0] |= IN2 << 1;
          ucRegDiscreteBuf[0] |= IN3 << 2;
          ucRegDiscreteBuf[0] |= IN4 << 3;
          ucRegDiscreteBuf[0] |= IN5 << 4;
          ucRegDiscreteBuf[0] |= IN6 << 5;
          ucRegDiscreteBuf[0] |= IN7 << 6;
          ucRegDiscreteBuf[0] |= IN8 << 7;
          
          ucRegDiscreteBuf[1] |= IN9  << 0;
          ucRegDiscreteBuf[1] |= IN10 << 1;
          ucRegDiscreteBuf[1] |= IN11 << 2;
          ucRegDiscreteBuf[1] |= IN12 << 3;       
          ucRegDiscreteBuf[1] |= IN13 << 4;
          ucRegDiscreteBuf[1] |= IN14 << 5; 
          ucRegDiscreteBuf[1] |= IN15 << 6;
          ucRegDiscreteBuf[1] |= IN16 << 7; 
        }
        while( iNDiscrete > 0 )
        {
            *pucRegBuffer++ = xMBUtilGetBits( ucRegDiscreteBuf, usBitOffset,
                                             ( unsigned char)( iNDiscrete > 8 ? 8 : iNDiscrete ) );
            iNDiscrete -= 8;
            usBitOffset += 8;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}