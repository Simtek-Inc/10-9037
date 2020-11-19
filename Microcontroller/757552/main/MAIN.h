 /*=============================================================================
 * Module Name: Main.h
 * Purpose : MAIN defines
 *						for 51-7056-01  
 *              
 * Author : Sr
 * Date : October 14, 2020
 * Notes :
 *
 *
 *=============================================================================
 */

#ifndef _MAIN_H_
#define _MAIN_H_
#include "ADuC841.h"
#include "types.h"

/* begin port control line defines */
// Port 0 is used as High BYTE D/A Data bus

sbit DB_3      = P2^7;
sbit DB_2      = P2^6;
sbit DB_1      = P2^5;
sbit DB_0      = P2^4;
//sbit CSA_CRS   = P2^3;
//sbit CSB_CRS   = P2^2;
//sbit CSA_FINE  = P2^1;
//sbit CSB_FINE  = P2^0;
#define CSA_CRS  0x07   //P2^3
#define CSB_CRS  0x0B   //P2^2;
#define CSA_FINE 0x0D   //P2^1;
#define CSB_FINE 0x0E   //P2^0;

sbit VBR_CTRL  = P3^7;
sbit AD_WR        = P3^5;
sbit DE        = P3^4;
//sbit AD_CLK    = P3^3;  // not currently used
//sbit AD_CS     = P3^2;  // not currently used
/* end port control line defines */

/* begin exported variables */
extern U8_T MAIN_CommandBuf[];
extern U8_T MAIN_UartTxBuf[];
extern void AD7247_Write(U16_T Dat, U8_T Dac);
extern void AD7247_Init(void);
extern U8_T MAIN_StatusBuf;

extern U8_T code Firmware[];

/* end exported variables */
#endif