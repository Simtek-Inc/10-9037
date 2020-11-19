/*
 ******************************************************************************
 *     Copyright (c) 2006	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
 /*============================================================================
 * Module Name: display.c
 * Purpose:	 LCD display interface 
 * Author:
 * Date:
 * Notes:
 * $Log: adapter.c,v $
 *=============================================================================
 */

/* GLOBAL VARIABLES DECLARATIONS */

/* INCLUDE FILE DECLARATIONS */
//#include <c8051f300.h>                 // SFR declarations
#include "types.h"
#include "displayconfig.h"
//#include "display.h"
#include "main.h"
#include "intrins.h"
#include "Utilities.h"


//#include "cpu_init.h"


//#include "uart.h"

//#include "debug.h"

//#include "types.h"
//#include "display.h"
//#include "main.h"
//#include "displayconfig.h"
//#include "intrins.h"

/* NAMING CONSTANT DECLARATIONS */

#define LD8 20
#define LD16 0


/* LOCAL VARIABLES DECLARATIONS */


U8_T bdata DataByte;
sbit DataBitZero = DataByte^0;

//U8_T idata LCDBuf[5];


/* LOCAL SUBPROGRAM DECLARATIONS */
void DISPLAY_HI8045DriverLoad(U8_T * bmapptr, U8_T loop);
void DISPLAY_Align(void);
void DISPLAY_Test(void);
void DISPLAY_Blank(void);

//void LongDelay(U8_T count,U16_T loop);

/*
 * ----------------------------------------------------------------------------
 * Function Name: DISPLAY_HI8045DriverLoad
 * Purpose:	Load lcd driver with serial data
 * Params: pointer to serial bitmap data, number bytes to send 0 - 255
 * Returns: nothing
 * Note:
 * ----------------------------------------------------------------------------
 */
void DISPLAY_HI8045DriverLoad(U8_T * bmapptr, U8_T loop)	// output the data to the display driver
{
	U8_T ByteCount, BitCount;

//	NOP(3);
	DispLoad = 0;
	DispClk = 1;				// make sure the driver clock is deactivated
	DispData = 0;
//	DispCs = 0;
//	NOP(3);
	for(ByteCount = 0; ByteCount < loop; ByteCount++){ 	// loop so all 5 bytes are output to the display driver
		DataByte = *(bmapptr+ByteCount);	 		// get the current byte of daata
		for(BitCount = 0; BitCount < 8; BitCount++){ 	// loop until all 8 bits in this byte are output to the driver
			DispData = DataBitZero;			// place the data onto the driver data pin
			NOP(3);
			DispClk = 0;	  			// activate the driver clock
			NOP(3);
			DispClk = 1;				// deactivate the driver clock
			NOP(3);
			DataByte = DataByte >> 1;			// move the next bit into place for next output
			}
		}
	DispLoad = 1;				// activate display driver load
	NOP(3);
	NOP(3);
	NOP(3);
	DispLoad = 0;				// deactivate display driver load	
	NOP(3);
//	DispCs = 1;					// deselect HI-8045 driver/s	
	DispData = 0;			// clear data pin
	NOP(3);
}


/*
 * ----------------------------------------------------------------------------
 * Function Name: void	DISPLAY_Align(void);
 * Purpose: turns on segments one at a time,
 *				then turns off one segment at a time
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */


void DISPLAY_Align(void)
{
	U8_T  x,y,z;
	U8_T SData[] = {0,0,0,0,0};
	U8_T DData[5];

	// first turn on 1 segment at a time.
	for(x = 0; x < 5; x++){
	  for(y = 0, z = 1; y < 8; y++,z <<= 1){
			SData[x] |= z;
			CrBitMap(&SData[0],&DData[0]);
			DISPLAY_HI8045DriverLoad(&DData[0], 5);	// output the data to the display driver
			LongDelay(LD8,LD16);
			}
		}

	// now turn off 1 segment at a time.
	for(x = 0; x < 5; x++){
	  for(y = 0, z = 0xFE ; y < 8; y++,z <<= 1){
			SData[x] &= z;
			CrBitMap(&SData[0],&DData[0]);
			DISPLAY_HI8045DriverLoad(&DData[0], 5);	// output the data to the display driver
			LongDelay(LD8,LD16);
			}
		}
}
// end void	DISPLAY_Align(void);




/*
 * ----------------------------------------------------------------------------
 * Function Name: void	DISPLAY_Test(void);
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */

void	DISPLAY_Test(void)
{
	U8_T TmpDisplayDat[5] = {0xFF,0xFF,0xFF,0xFF,0xFF}; // set all bits in buffer
	
	DISPLAY_HI8045DriverLoad(&TmpDisplayDat[0], 5);	// output the data to the display driver
//	LongDelay(LD8,LD16);
}

// end DISPLAY_Test(void);


/*
 * ----------------------------------------------------------------------------
 * Function Name: void	DISPLAY_Blank(void);
 * Purpose:
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */

void	DISPLAY_Blank(void)
{
	U8_T TmpDisplayDat[5] = {0,0,0,0,0};  // clear buffer
	
	DISPLAY_HI8045DriverLoad(&TmpDisplayDat[0], 5);	// output the data to the display driver
}// end DISPLAY_Blank(void);





/* End of display.c */
