/*=============================================================================
 * Module Name: Command.c
 * Purpose : 
 *	
 *	
 *	
 * Author : s.reynolds
 * Date : October 14, 2020
 * Notes :
 * 
 *
 *=============================================================================
 *
 *********************
 **	Revision Level:
 **	 
 *********************
 **/

//-------
// Includes
//-------

//#include "ADuC841.h"
#include "types.h"
#include "main.h"
//#include "cpu_init.h"
//#include "display.h"
//#include "displayconfig.h"
#include "uart.h"
#include "intrins.h"

//-------
// Global CONSTANTS
//-------
//-------
// Function PROTOTYPES
//-------
U8_T Transmit (void);
//void SendPowerUp(void);
void ProcessCommand(U8_T * CmdPtr);
void ProcessResetRequest(void); 
//void ProcessStatusRequest(void); 
void ProcessDisplayRequest(U8_T * DatPtr);
//void ProcessDisplayTestRequest(void);
//void ProcessDimmingRequest(void);
void ProcessFirmwareRequest(U8_T * FirmwarePtr);

//void ProcessLoadRequest(U8_T * Dat);
//void ProcessDataInRequest(U8_T * Dat);
//void ProcessClockRequest(void);
void SendCommandComplete(void);


//-------
// Global Variables
//-------


/*
 * ----------------------------------------------------------------------------
 * Function Name: void ProcessCommand(U8_T * CmdPtr)
 * Purpose: process Uart message
 * Params:
 * Returns:
 * Note:	
 *		// uart serial command  defines
 *		//#define RESETFLAG			0x01
 *		//#define DISPLAYFLAG		0x02
 *		//#define DIMMINGFLAG		0x04
 *		//#define FIRMWAREFLAG		0x08
 *		//#define RXCOMPLETEFLAG	0x80
 * ----------------------------------------------------------------------------
 */
void ProcessCommand(U8_T * CmdPtr)
{
	switch (*CmdPtr){
		case RESET_REQUEST: // 0xF0
			ProcessResetRequest();
			break;
		case DISPLAY_REQUEST: //	0xF5
			ProcessDisplayRequest(CmdPtr+1); // adding 1 because data starts at the next buffer position
			break;
//		case STATUS_REQUEST: //	0xF1
//			ProcessStatusRequest(); // adding 1 because data starts at the next buffer position
//			break;
//		case DIMMING_REQUEST: //	0x30
//			ProcessDimmingRequest();
//			break;
		case FIRMWARE_REQUEST: //	0xFE
			ProcessFirmwareRequest(&Firmware[0]);
			break;
//    case CLOCK_REQUEST:   // 0xE0
//      ProcessClockRequest();
//      SendCommandComplete();
//      break;
//    case DATA_IN_REQUEST: // 0xE1
//      ProcessDataInRequest(CmdPtr+1);
//      SendCommandComplete();
//      break;
//    case LOAD_REQUEST:    // 0xE2
//      ProcessLoadRequest(CmdPtr+1);
//      SendCommandComplete();
//      break;
//    case DISPLAY_TEST_REQUEST:   // 0xE3
//      ProcessDisplayTestRequest();
//      SendCommandComplete();
//      break;
//    case DISPLAY_BLANK_REQUEST:   // 0xE4
//      DISPLAY_Blank();
//      SendCommandComplete();
//      break;
//    case DISPLAY_ALIGN_REQUEST:  // 0xE5
//      DISPLAY_Align();
//      SendCommandComplete();
//      break;
		}
	}

void SendCommandComplete(void)
{
		MAIN_UartTxBuf[0] = 0x03;
    MAIN_UartTxBuf[1] = PANEL_ADDRESS;
		MAIN_UartTxBuf[2] = 0x0D;
		MAIN_UartTxBuf[3] = 0x0A;

    Transmit();

}

//void ProcessLoadRequest(U8_T * Dat)
//{
//  DispLoad = (*Dat ? 1 : 0);
//}
//
//void ProcessDataInRequest(U8_T * Dat)
//{
//  DispData = (*Dat ? 1 : 0);
//}
//void ProcessClockRequest(void)
//{
//  DispClk = 0;
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  DispClk = 1;
//}
//
//void ProcessDisplayTestRequest(void)
//{
//  DISPLAY_Test();
//
//}



/*
 * ----------------------------------------------------------------------------
 * Function Name: ProcessReset(
 * Purpose: software reset function
 * Params:
 * Returns:
 * Note:	
 * ----------------------------------------------------------------------------
 */
void ProcessResetRequest(void) // reset function
{
  AD7247_Write(0,0); // reset all 4 D/A channels to zero scale
}

/*
 * ----------------------------------------------------------------------------
 * Function Name: void ProcessDisplayRequest(void)
 * Purpose: Display function
 * Params:
 * Returns:
 * Note:	
 * ----------------------------------------------------------------------------
 */
void ProcessDisplayRequest(U8_T * DatPtr) // Display function
{

U16_T Dac_Data = 0;

DatPtr++; // to skip over address byte

//Dac_Data = (U16_T)*(DatPtr++) & 0x00FF;
//Dac_Data |= (((U16_T) (*(DatPtr++)  << 6) ) & 0x0FC0);
//AD7247_Write(Dac_Data,CSB_CRS);  // write 
//
//Dac_Data = (U16_T)*(DatPtr++) & 0x00FF;
//Dac_Data |= (((U16_T) (*(DatPtr++)  << 6) ) & 0x0FC0);
//AD7247_Write(Dac_Data,CSA_CRS);  // write 
  
Dac_Data = (U16_T)*(DatPtr++) & 0x00FF;
Dac_Data |= (((U16_T) (*(DatPtr++)  << 6) ) & 0x0FC0);
AD7247_Write(Dac_Data,CSA_FINE);  // write 

}

/*
 * ----------------------------------------------------------------------------
 * Function Name: void ProcessDimmingRequest(void)
 * Purpose: Dimming function
 * Params:
 * Returns:
 * Note:	
 * ----------------------------------------------------------------------------
 */
//void ProcessDimmingRequest(void) // Dimming function
//{
//	U8_T tmp;
//
//	tmp = (MAIN_CommandBuf[1] << 4);
//	tmp |= (MAIN_CommandBuf[2] & 0x0F);
////	PCA0CPH0 = tmp;
//}

/*
 * ----------------------------------------------------------------------------
 * Function Name: U8_T ProcessFirmwareRequest(void)
 * Purpose: Firmware function
 * Params:
 * Returns:
 * Note:	
 * ----------------------------------------------------------------------------
 */
void ProcessFirmwareRequest(U8_T * FirmwarePtr) // firmware function
{
	U8_T i,k,tmp;
	
  if (TX_FLAG_SET)
    return;
	i= 0;

	if(MAIN_UartTxBuf[0] == 0){// clear to load buffer
		MAIN_UartTxBuf[i++] = FIRMWARE_RESPONSE_LENGTH;  // number of bytes to transmit
    MAIN_UartTxBuf[i++] = FIRMWARE_RESPONSE;         //  -
    MAIN_UartTxBuf[i++] = PANEL_ADDRESS;             //  |
    for(k = 0; k < 6; k += 2, i++){
		  tmp = ((*(FirmwarePtr +k)) << 4);              //  Data to transmit
		  tmp |= ((*(FirmwarePtr +k +1)) & 0x0F);
		  MAIN_UartTxBuf[i] = tmp;
		  }                                              //  |
		MAIN_UartTxBuf[i] = (*(FirmwarePtr+k));          //  -

		Transmit();
		}
}


/* * ----------------------------------------------------------------------------
 * Function Name: void ProcessStatusRequest(void)
 * Purpose: Firmware function
 * Params:
 * Returns:
 * Note:	
 * ----------------------------------------------------------------------------
 */
//void ProcessStatusRequest(void) // status function
//{
//	unsigned char i = 0;
//
//if (TX_FLAG_SET) // if we are already transmitting do not overwrite the buffer
//  return;
//
//	if(MAIN_UartTxBuf[0] == 0){// clear to load buffer
//		MAIN_UartTxBuf[i++] = STATUS_RESPONSE_LENGTH;      // number of bytes to transmit
//    MAIN_UartTxBuf[i++] = STATUS_RESPONSE;             //  -
//    MAIN_UartTxBuf[i++] = PANEL_ADDRESS;               //  Data to transmit
////		MAIN_UartTxBuf[i++] = MAIN_StatusBuf;              //  -
//		MAIN_UartTxBuf[i++] = 0x00;              //  -
//                                                       
//		Transmit();                                        
//		}                                                  
//}                                                      
                                                       

U8_T Transmit (void)
{
	U8_T i;
	if(UART_TxBuf[0] == 0){// clear to load buffer
		for(i = 0; i<= MAIN_UartTxBuf[0]; i++) // transfer bytes to tx
			UART_TxBuf[i] = MAIN_UartTxBuf[i]; //  
		MAIN_UartTxBuf[0] = 0; // signal main tx buf empty
		TI = 1; // trigger a tx interrupt
		}
    return(i);
}





 //
 //
 //

//-------
// End Of File
//-------
