 /*=============================================================================
 * Module Name: Main.c
 * Purpose : 75-7552 instrument firmware
 *						for 10-9037-01   Cabin Altimeter Indicator
 *              
 * Author : Sr
 * Date : November 2, 2020
 * Notes :
 * for 51-7056-01 circuit board assembly.
 * uses 14.7456MHz oscillator.
 *=============================================================================
 */

#include "ADuC841.h"
#include "cpu.h"
#include "main.h"
#include "types.h"
#include "uart.h"
#include "Command.h"
#include <intrins.h>


U8_T MAIN_CommandBuf[RXBUF_SIZE];
U8_T MAIN_UartTxBuf[TXBUF_SIZE];
U8_T MAIN_StatusBuf = 0;

U8_T code Firmware[] = "757552-";
void AD7247_Write(U16_T Dat, U8_T Dac);
//U8_T ReadSwitch(void);
//U8_T DebounceSwitch(U8_T OldSw);

//sbit LED = P3^2;

//#define SW_DELAY_COUNT 820  // magic number to give ~ 1ms switch reads.

void main (void)
{ 

//  U16_T SwitchReadCount = SW_DELAY_COUNT;

  CPU_Init();
  AD7247_Write(0,0);  // reset all 4 D/A channels to zero scale
//  MAIN_StatusBuf = ReadSwitch();  // initialize switch status
  SendCommandComplete();

  while(1){	
//    LED = 1;
		if (MAIN_CommandBuf[0]) {
			ProcessCommand(&MAIN_CommandBuf[0]);
      MAIN_CommandBuf[0] = 0;  // clear command buffer
      }
//    LED = 0;
//    if((--SwitchReadCount) == 0) { // read switch when read count expires 
//      SwitchReadCount = SW_DELAY_COUNT;
//      MAIN_StatusBuf = DebounceSwitch(MAIN_StatusBuf);
////      UART_Reset();      	
//      }
    }
}

//U8_T DebounceSwitch(U8_T OldSw)
//{ 
//  // if both port 1 pin and port 3 pin are high...then assume middle positon
//  // save the new switch byte in the buffer
//  // and only report a change when all switch readings are the same.
//  // 
//  static U8_T SwBuf[] = {0,0,0,0,0}; // switch buffer
//  static U8_T Cnt = 0;
//
//  U8_T i;
//  U8_T tmp = 0;
//
//  tmp = ReadSwitch();
//
//  SwBuf[Cnt++] = tmp;
//  if ( Cnt == sizeof(SwBuf))
//    Cnt = 0; 
//  for(i = 0; i < sizeof(SwBuf); i++){
//    if(tmp != SwBuf[i]) {
//      return OldSw;  // no change
//      }
//    }
//  return tmp;
//}
//
//
//
//U8_T ReadSwitch(void)
//{ // reads switch input pins on Port 1 and Port 3
//  // decodes for a three bit status
//
//  U8_T s = 0, i = 0;
//
//  s = (P1 & 0x08) >> 1;  // Switch Position 1 is on P1^3;
//  s |= (P3 & 0x40) >> 6;  // Switch Position 2 is on P3^6;
//  switch(s){  // position 1 and 2 both are high. switch is in middle position
//    case 1:
//      i = 4;
//      break;
//    case 4:
//      i = 1;
//      break;
//    case 5:
//      i = 2;
//      break;
//    case 0:
//      i = 15;
//      break;
//    }
//  return i;
//}



 
void AD7247_Write(U16_T Dat, U8_T Dac)
{
  P0 = Dat >> 4;            // High data to DAC Data Bus
  P2 = (U8_T)Dat << 4;      // Low  data to DAC Data Bus
  P2 |= (Dac & 0x0F);       // Select which DAC channel
  AD_WR = 0;  
  _nop_();
  _nop_();
  _nop_();
  AD_WR = 1;  
  P2 |= 0x0F;//  disable the dacs
}