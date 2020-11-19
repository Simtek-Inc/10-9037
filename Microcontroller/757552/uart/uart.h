/*
 ******************************************************************************
 *     Copyright (c) 2013	Simtek, Incorporated      All rights reserved.
 *
 *     This is unpublished proprietary source code of Simtek, Inc
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
/*=============================================================================
 * Module Name: uart.h
 * Purpose : uart header file for ADUC841
 * Author : s.reynolds
 * Date : October 23, 2020
 * Notes :
 *=============================================================================
 *
 *********************
 **	Revision Level:
 **	 
 *********************
 **/
//-------
// Includes
#include "ADuC841.h"

#include "types.h"

//-------

//-------
// GLOBAL CONSTANTS
//-------
#define START_BYTE			  0xFF
#define RESET_REQUEST		  0xF0
//#define STATUS_REQUEST		0xF1
//#define STATUS_RESPONSE		0xF1
//#define STATUS_RESPONSE_LENGTH 3
#define DISPLAY_REQUEST	  0xF5
#define DISPLAY_REQUEST_LENGTH 3
//#define DIMMING_REQUEST	  0x30
#define FIRMWARE_REQUEST	0xFE
#define FIRMWARE_REQUEST_LENGTH	1
#define FIRMWARE_RESPONSE	0xFE
#define FIRMWARE_RESPONSE_LENGTH 6
#define RXBUF_SIZE        8
#define TXBUF_SIZE        8
//#define CLOCK_REQUEST     0xE0
//#define DATA_IN_REQUEST   0xE1
//#define LOAD_REQUEST      0xE2
//#define DISPLAY_TEST_REQUEST      0xE3
//#define DISPLAY_BLANK_REQUEST      0xE4
//#define DISPLAY_ALIGN_REQUEST      0xE5

#define PANEL_ADDRESS (~P1 & 0x07)


// timer 0 is used as a serial timeout to prevent lockups or loosing sync with the command message.
// It takes approximately 260uS for one character to arrive at 38400 bps
// timer zero will allow 3 * 1 character time before it expires.
// if the next character is received before timer 0 expires
// the timer is reset for 3 * 1 character time and we wait for the next character.
// this repeats until the entire message is received.
// if the timer expires before the next character is received the message is ignored
// and the serial state machine starts over looking for a new command byte.

#define TIMER_0_RELOAD (65535 - 3840) // time for 3 received bytes



extern U8_T data UART_TxBuf[];
//extern U8_T UART_CtrlReg;	// .0 ReceivingData
							// .7 TransmittingData

// UART CONTROL FLAGS
#define RX_FLAG	0x01
#define TX_FLAG 0x02
//#define DEBUG_FLAG 0x04

extern U8_T UART_CtrlReg;	// bit0 = 1 - indicates received valid command.  

#define RX_FLAG_SET  (UART_CtrlReg & RX_FLAG)
#define SET_RX_FLAG  (UART_CtrlReg |= RX_FLAG)
#define CLEAR_RX_FLAG (UART_CtrlReg &= ~RX_FLAG)

#define TX_FLAG_SET  (UART_CtrlReg & TX_FLAG)

//-------
// LOCAL CONSTANTS
//-------


//-------
// Function PROTOTYPES
//-------
extern void UART_Reset(void);
void Timer0Interrupt(void);
