/*=============================================================================
 * Module Name: Command.h
 * Purpose : ICD description of command functions.
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
//#include "main.h"
//#include "cpu_init.h"
//#include "uart.h"

//-------
// Global CONSTANTS
//-------

//-------
// Function PROTOTYPES
//-------
U8_T Transmit (void);
//void SendPowerUp(void);
//void SendData(void);
U8_T ProcessCommand(U8_T * CmdPtr);
U8_T SendCommandComplete(void);
//void ProcessCommandByte(void);
void ProcessResetRequest(void); 
void ProcessDisplayRequest(void);
//void ProcessDimmingRequest(void);
U8_T ProcessFirmwareRequest(U8_T * FirmwarePtr);

//-------
// Global Variables
//-------


////-------
//// End Of File
////-------
