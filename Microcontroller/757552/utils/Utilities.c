/*=============================================================================
 * Module Name: Utilities.c
 * Purpose : place for function tools 
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

#include "types.h"
#include "intrins.h"

//-------
// Global CONSTANTS
//-------
//-------
// Function PROTOTYPES
//-------
void NOP(U16_T loop);
void LongDelay(U8_T count,U16_T loop);


/*
 * ----------------------------------------------------------------------------
 * Function Name: void NOP(U16_T loop)
 * Purpose: variable delay
 * Params:
 * Returns:
 * Note:	
 *
 * ----------------------------------------------------------------------------
 */
void NOP(U16_T loop) // loop of _nop instructions
{ 
	do{
		_nop_();
		loop--;
		} while(loop);
}

void LongDelay(U8_T count,U16_T loop)
{ 
	do{
		do{
			_nop_();
			loop--;
			} while(loop);
			count--;
		} while(count);
}



//-------
// End Of File
//-------
