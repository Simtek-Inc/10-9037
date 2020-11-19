/*=============================================================================
 * Module Name: uart.c
 * Purpose : uart interrupt handler
 *
 * Author : s.reynolds
 * Date : October 14, 2020
 * Notes :
 * 
 *
 *=============================================================================
 *********************
 **	Revision Level:
 *********************
 **/


//-------
// Includes
//-------
#include "ADuC841.h"
#include "types.h"
#include "uart.h"

//#ifndef _MAIN_H_
#include "main.h"
//#endif


//-------
// Global CONSTANTS
//-------


// UART CONTROL FLAGS
#define RX_FLAG	0x01
#define TX_FLAG 0x02

#define RX_FLAG_SET  (UART_CtrlReg & RX_FLAG)
#define SET_RX_FLAG  (UART_CtrlReg |= RX_FLAG)
#define CLEAR_RX_FLAG (UART_CtrlReg &= ~RX_FLAG)

#define TX_FLAG_SET  (UART_CtrlReg & TX_FLAG)
#define SET_TX_FLAG  (UART_CtrlReg |= TX_FLAG)
#define CLEAR_TX_FLAG (UART_CtrlReg &= ~TX_FLAG)

#define STOP  0
#define START 1

//#define DimmingMessageDataLength 2
typedef enum _parity_t_ { ODD, EVEN } PARITY_T;
PARITY_T parity;
//-------
// Global Variables
//-------
U8_T data UART_RxBuf[RXBUF_SIZE];// 
U8_T data UART_TxBuf[TXBUF_SIZE];// 
static U8_T RxByte  = 0;
static U8_T RxCount = 0;
static U8_T TxCount = 0;
U8_T UART_CtrlReg = 0;	// bit0 = 1 - indicates received valid command.  
                    //      = 0 - 
							      // .7 TransmittingData
U8_T RxMessageLength; // only interested in data for ACNIP Display Module 
U8_T MessageDataLength; // 


//-------
// Function PROTOTYPES
//-------
void UART_Int(void);
void TimerZero_Int(void);
void DecodeCommandByte(void);
void ProcessRXByte(void);
//void ProcessReset(void);
void ReceiveDisplayData(void);
//void ReceiveDimmingData(void);
//void ProcessFirmware(void);
void ProcessTXInt(void);
BOOL ValidateCommand(void);
BOOL ValidateAddress(void);
void SerialWatchDog(BOOL ctrl);
void Timer0Interrupt(void);		// timer 0 interrupt service routine 
U8_T ParityCheck(unsigned char);
void UART_Reset(void);


//---------------------------
// UART_Interrupt
//---------------------------
void UART_Int(void) interrupt 4		// interrupt service routine for all serail UART interrupts
{
  bit RxParityBit = 0;
  PARITY_T RxByteParity;

		if (RI){
      SerialWatchDog(STOP);
			RxByte = SBUF;
      RxParityBit = RB8;
			RI = 0;
      RxByteParity = ParityCheck(RxByte);
      if( ( ( RxByteParity == ODD  ) && ( RxParityBit == 0 ) ) ||
          ( ( RxByteParity == EVEN ) && ( RxParityBit == 1 ) ) ) {
		    ProcessRXByte();
        if(RX_FLAG_SET)
          SerialWatchDog(START);
        }
        else {
          RxCount = 0;
          CLEAR_RX_FLAG;
          }
			} /* End of if(RI) */
	  if (TI){ // we got a tx interrupt
			TI = 0;	// clear tx flag
			ProcessTXInt();
			}
//		}
} /* End of UART_Int */

PARITY_T ParityCheck(unsigned char c)
{ unsigned char i,p = 0;
  

  for(i = 0x80; i > 0; i >>= 1){ 
    if(c & i)
      p++;
    }
  switch(p) {
    case 0:
    case 2:
    case 4:
    case 6:
    case 8:
      return EVEN;
      break;
    default:
      return ODD;
      break;
    }
}


void UART_Reset(void)
{
  SerialWatchDog(STOP);
  CLEAR_TX_FLAG;
  UART_TxBuf[0] = 0; // notify tx finish
  DE = 0; // disable transmitter
  REN = 1;  // enable receive interrupt
  RxCount = 0;
  RxMessageLength = 0;
  CLEAR_RX_FLAG;
}


void SerialWatchDog(BOOL ctrl)
{ // controls Timer0Interrupt routine
switch(ctrl) {
  case START:
    TR0 = 1; //start serial watchdog
    break;
  case STOP:
  default:  // stop the watchdog;
    TR0 = 0; //disable serial watchdog
		TL0 = 0;	// reload for serial watchdog
		TH0 = 0;	// reload 
    break;
  }
}


/*
 * ----------------------------------------------------------------------------
 * Function Name: void ProcessTXInt(void)
 * Purpose: process transmit byte
 * Params:
 * Returns:
 * Note:	
 *		// serial command  defines
 *		#define StartByte			0xFF
 *		#define ResetRequest		0xF0
 *		#define DisplayRequest	0xF5
 *		#define DimmingRequest	NA
 *		#define FirmwareRequest	0xFE
 * U8_T TxCount = 0;
 * #define TRANSMITTINGFLAG	0x80
 *		
 * ----------------------------------------------------------------------------
 */

void ProcessTXInt(void)
{
  PARITY_T TxByteParity;
	static unsigned char TxMessageLength;

	if((TX_FLAG_SET)){
		if(TxCount <= TxMessageLength){
      TxByteParity = ParityCheck(UART_TxBuf[TxCount]);
      if (TxByteParity == EVEN)
        TB8 = 1;
      else
        TB8 = 0;
			SBUF = UART_TxBuf[TxCount];
			TxCount++;
			}
		else{
			CLEAR_TX_FLAG;
			UART_TxBuf[0] = 0; // notify tx finish
			UART_TxBuf[0] = 0; // notify tx finish
			DE = 0; // disable transmitter
      REN = 1;  // enable receive interrupt
			}
		}
	else if(UART_TxBuf[0]){
    REN = 0;  // disable receive interrupt
		DE = 1; // enable transmitter
		TxMessageLength = UART_TxBuf[0];
		SET_TX_FLAG;
    TxByteParity = ParityCheck(UART_TxBuf[1]);
    if (TxByteParity == EVEN)
      TB8 = 1;
    else
      TB8 = 0;
		SBUF = UART_TxBuf[1];
		TxCount = 2;
		}
}


/*
 * ----------------------------------------------------------------------------
 * Function Name: void ProcessRXByte(void)
 * Purpose: process the received byte
 * Params:
 * Returns:
 * Note:	
 *		// serial command  defines
 *		#define StartByte			0xFF
 *		#define ResetRequest		0xF0
 *		#define DisplayRequest	0xF5
 *		#define DimmingRequest	NA
 *		#define FirmwareRequest	0xFE
 *		
 * ----------------------------------------------------------------------------
 */
void ProcessRxByte(void)
{
	U8_T i;
  if(RxCount == 0) {   // we should have a command byte
    if (ValidateCommand()){
      if(RxMessageLength) {
        UART_RxBuf[RxCount] = RxByte;
        RxCount++;
        SET_RX_FLAG;
        }
      }
    }
  else if(RxCount == 1) {  // we should have an address byte
    if (ValidateAddress()){
        UART_RxBuf[RxCount] = RxByte;
        RxCount++;
        }
      else {
        RxCount = 0;
        RxMessageLength = 0;
			  CLEAR_RX_FLAG;
        }
      }
    
  else if(RxCount <= RxMessageLength ){
			UART_RxBuf[RxCount] = RxByte; // store the data byte
//			RxMessageLength--;
			RxCount++;
			}
  if (RxCount > RxMessageLength) { // if we have received the last byte
	  for(i=0; i < RXBUF_SIZE; i++){
		  MAIN_CommandBuf[i] = UART_RxBuf[i]; // notify main to process uart message
      UART_RxBuf[i] = 0;
      }
    RxCount = 0;
    RxMessageLength = 0;
		CLEAR_RX_FLAG;
		}
}

BOOL ValidateAddress(void)
{
  BOOL status = FALSE;

	if (RxByte == PANEL_ADDRESS){
      status = TRUE;
			}
	return(status);
}






/*
 * ----------------------------------------------------------------------------
 * Function Name: BOOL ValidateCommand(void)
 * Purpose: sets up for receiving data
 * Params:
 * Returns:
 * Note:	
 *		// serial command  defines
 *		#define StartByte			0xFF
 *		#define ResetRequest		0x11
 *		#define DisplayRequest	0x20
 *		#define DimmingRequest	0x30
 *		#define FirmwareRequest	0x70
 *		
 * ----------------------------------------------------------------------------
 */
BOOL ValidateCommand(void)
{
  BOOL status = FALSE;

	switch (RxByte){
//    case CLOCK_REQUEST:          // activate display clock signal
		case RESET_REQUEST:
		case FIRMWARE_REQUEST:
//		case STATUS_REQUEST:
//    case DISPLAY_ALIGN_REQUEST:
//    case DISPLAY_BLANK_REQUEST:
//    case DISPLAY_TEST_REQUEST:

//			MessageDataLength = FIRMWARE_REQUEST_LENGTH; // message is complete
      RxMessageLength = FIRMWARE_REQUEST_LENGTH;
      status = TRUE;
			break;
		case DISPLAY_REQUEST:
//			MessageDataLength = DISPLAY_REQUEST_LENGTH; // only interested in data for LCD 74-7744 (outboard display)
			RxMessageLength = DISPLAY_REQUEST_LENGTH; // 5 byte message (including command byte)
      status = TRUE;
			break;
//    case DATA_IN_REQUEST:
//    case LOAD_REQUEST:
//			RxMessageLength = 1; 
//      status = TRUE;
//      break;
		default:
			RxMessageLength = 0;
      status = FALSE;
			break;
			}
	return(status);
}


/*
 * ----------------------------------------------------------------------------
 * Function Name: void Timer0Interrupt(void) interrupt 1
 * Purpose: uart timeout timer used for receiving data
 *				
 * Params:
 * Returns:
 * Note:	
 *
 * ----------------------------------------------------------------------------
 */
void Timer0Interrupt(void) interrupt 1		// timer 0 interrupt service routine 
{  // interrupt is switched on and off by SerialWatchDog() routine.
		TR0 = 0;
   	TL0 = LOW_BYTE(TIMER_0_RELOAD);	// reload for serial watchdog
		TH0 = HIGH_BYTE(TIMER_0_RELOAD);	// reload 
//    TR0 = 1;  // restart the timer
		if(RX_FLAG_SET){ // already got a start byte
      RxCount = 0;
      RxMessageLength = 0;
			CLEAR_RX_FLAG;
      			}
}


 /* End of UART_Int */

