 /*=============================================================================
 * Module Name: cpu.c
 * Purpose : ADUC841 initialization file 
 *						
 *              
 * Author : Sr
 * Date : October 13, 2020
 * Notes :
 * 
 * 
 *=============================================================================
 */

 #include "ADuC841.h"
 #include "Timer3BaudRates.H"
 #include "types.h"
 #include "intrins.h"
 #include "uart.h"




/* begin Proto types */
void CPU_Init(void);
void Interrupt_Init(void);
BOOL Timer3_Init(void);
void Uart_Init(void);
void TimerZero_Init(void);
void PortIO_Init(void);
/* end Proto types */




/* global variables */
BOOL error = FALSE;





void CPU_Init(void)
{ CFG841 = 0x81;   // use extended stack pointer: enable XRAMEN  
  PortIO_Init();
  Uart_Init();
  Interrupt_Init();
}

void Interrupt_Init(void)
{
	ES = 1; // to enable serial port interrupt
	ET0 = 1; // to enable Timer zero interrupt
	EA = 1; // to enable interrupts
}

BOOL Timer3_Init(void)
{ 
	T3CON = t3con_14M_115200; 
	T3FD = t3fd_14M_115200;
  return (TRUE);
}


void Uart_Init(void)
{
	// initialize uart
//	SCON = 0x50;	// 8 bit variable baud rate.
	SCON = 0xD0;	// 9 bit variable baud rate.
								// multi process communication off
								// receive enable
  TimerZero_Init();
  Timer3_Init();
}



void TimerZero_Init(void)
{
  TCON      = 0x00;	//to turn on timer 1
  TMOD      = 0x01;	//timer 1 - mode 2 8bit auto reload
	 							// timer 0 16 bit timer
   	TL0 = LOW_BYTE(TIMER_0_RELOAD);	// reload for serial watchdog
		TH0 = HIGH_BYTE(TIMER_0_RELOAD);	// reload 

}



void PortIO_Init(void)
{
	// initialize port pins
  P0 = 0xFF;	// to initialize port 0
              // BITS 11 thru 4 of data bus
  P1 = 0x00;	// to initialize port 1 as input
  P2 = 0x0F;	// to initialize port 2	
							// p2.7 BIT 3 of data bus
							// p2.6 BIT 2 of data bus
							// p2.5 BIT 1 of data bus
							// p2.4 BIT 0 of data bus
                            
							// p2.3 CSA_CRS  default to high
							// p2.2 CSB_CRS  default to high
							// p2.1 CSA_FINE  default to high
							// p2.0 CSB_FINE  default to high

  P3 = 0xE3;  // to initialize port 3
							// p3.7 Not used
							// p3.6 Not used
							// p3.5 WR  default to HIGH
							// p3.4 DE  default to LOW
							// p3.3 //NOT USED
							// p3.2 //NOT USED
							// p3.1 TX 
							// p3.0 RX
}	

