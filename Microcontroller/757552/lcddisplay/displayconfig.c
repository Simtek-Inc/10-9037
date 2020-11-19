/*=============================================================================
 * Module Name:DisplayConfig.c
 * Purpose: Ascii to segment translation for ACNIP Display Module Kit 
 * Author:
 * Date:
 * Notes:
 *=============================================================================
 */

/* INCLUDE FILE DECLARATIONS */

#include "displayconfig.h"
#include "types.h"

//#include "display.h"


/* NAMING CONSTANT DECLARATIONS */

#define LcdBitMapByteCount	5 	 		// # bytes in LCD serial bitstream

/* GLOBAL VARIABLES */
U8_T bdata LCDBitMap[LcdBitMapByteCount]; // 
U8_T bdata LCDByte;
sbit LCDByteBitZero = LCDByte^0;

/* LOCAL VARIABLES DECLARATIONS */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */
/*-------------------------------------------------------------*/
//void CreateBitmap(U8_T idata * idata LcdDataPtr);
void CrBitMap(U8_T  * SourcePtr, U8_T * DestinationPtr);







/* display bitmap variable definitions */
// SEGMENT data as defined by c.b. assy 51-7203-01 U1
// LcdBitMap[0]^0 is first segment out;
// LcdBitMap[4]^7 is last segment out;


// U1 definitios
																	  
//sbit  SSS= LCDBitMap[0]^0; // first  bit out, padding bit
//sbit  SSS= LCDBitMap[0]^1; // second bit out, padding bit		holt device only has 38 segments.
sbit  KY2_PL    = LCDBitMap[0]^2; // holt seg 38			                                
//sbit          = LCDBitMap[0]^3; // holt seg 37			                                
//sbit          = LCDBitMap[0]^4; // holt seg 36                                      
//sbit          = LCDBitMap[0]^5; // holt seg 35                                      
//sbit          = LCDBitMap[0]^6; // holt seg 34                                      
//sbit          = LCDBitMap[0]^7; // holt seg 33                                      
//sbit          = LCDBitMap[1]^0; // holt seg 32                                      
//sbit          = LCDBitMap[1]^1; // holt seg 31			                                
//sbit          = LCDBitMap[1]^2; // holt seg 30			                                
//sbit          = LCDBitMap[1]^3; // holt seg 29			                                
//sbit          = LCDBitMap[1]^4; // holt seg 28	BACK PLANE.  SEGMENT OFF            
//sbit          = LCDBitMap[1]^5; // holt seg 27                                      
sbit  KY2C      = LCDBitMap[1]^6; // holt seg 26                                      
sbit  KY2B      = LCDBitMap[1]^7; // holt seg 25                                      
sbit  KY2A      = LCDBitMap[2]^0; // holt seg 24                                      
sbit  KY2F      = LCDBitMap[2]^1; // holt seg 23			                                
sbit  KY2G      = LCDBitMap[2]^2; // holt seg 22			                                
sbit  KY1C      = LCDBitMap[2]^3; // holt seg 21			                                
sbit  KY1B      = LCDBitMap[2]^4; // holt seg 20                                      
sbit  KY1A      = LCDBitMap[2]^5; // holt seg 19                                      
//sbit          = LCDBitMap[2]^6; // holt seg 18	BACK PLANE.  SEGMENT OFF            
sbit  KY1F      = LCDBitMap[2]^7; // holt seg 17                                      
sbit  KY1G      = LCDBitMap[3]^0; // holt seg 16                                      
sbit  KY1E      = LCDBitMap[3]^1; // holt seg 15			                                
sbit  KY1D      = LCDBitMap[3]^2; // holt seg 14			                                
//sbit          = LCDBitMap[3]^3; // holt seg 13			                                
sbit  KY1_DLY   = LCDBitMap[3]^4; // holt seg 12                                      
//sbit          = LCDBitMap[3]^5; // holt seg 11                                      
sbit  KY1_CY    = LCDBitMap[3]^6; // holt seg 10                                      
//sbit          = LCDBitMap[3]^7; // holt seg 9                                       
sbit  KY1_PL    = LCDBitMap[4]^0; // holt seg 8                                       
sbit  KY2E      = LCDBitMap[4]^1; // holt seg 7				                                
sbit  KY2D      = LCDBitMap[4]^2; // holt seg 6				                                
//sbit          = LCDBitMap[4]^3; // holt seg 5				                                
sbit  KY2_DLY   = LCDBitMap[4]^4; // holt seg 4                                       
//sbit          = LCDBitMap[4]^5; // holt seg 3                                       
sbit  KY2_CY    = LCDBitMap[4]^6; // holt seg 2                                       
//sbit          = LCDBitMap[4]^7; // last bit out, seg 1 U1	BACK PLANE.  SEGMENT OFF 



/*
* -----------------------------------------------------------------------------
 * Function Name: SevenSegXlate
 * Purpose: translate ascii code to seven segment data
 * Params: U8_T ascii
 * Returns: U8_T SevenSegmentData
 * Note:
 * ----------------------------------------------------------------------------
 */
/*U8_T SevenSegXlate(U8_T ascii)			// translate the ASCII character into seven segment data
{
	U8_T ch;		// bit     7 6 5 4 3 2 1 0
	switch(ascii)	// segment x g f e d c b a
	{
		case 0x20:ch = 0x00; break;//blank  // translate the ASCII character into seven segment data
		case 0x2D:ch = 0x40; break;//"-"	// translate the ASCII character into seven segment data
		case 0x30:ch = 0x3F; break;//"0"	// translate the ASCII character into seven segment data
		case 0x31:ch = 0x06; break;//"1"	// translate the ASCII character into seven segment data
		case 0x32:ch = 0x5B; break;//"2"	// translate the ASCII character into seven segment data
		case 0x33:ch = 0x4F; break;//"3"	// translate the ASCII character into seven segment data
		case 0x34:ch = 0x66; break;//"4"	// translate the ASCII character into seven segment data
		case 0x35:ch = 0x6D; break;//"5"	// translate the ASCII character into seven segment data
		case 0x36:ch = 0x7D; break;//"6"	// translate the ASCII character into seven segment data
		case 0x37:ch = 0x07; break;//"7"	// translate the ASCII character into seven segment data
		case 0x38:ch = 0x7F; break;//"8"	// translate the ASCII character into seven segment data
		case 0x39:ch = 0x6F; break;//"9"	// translate the ASCII character into seven segment data
		case 0x41:ch = 0x77; break;//"A"	// translate the ASCII character into seven segment data
		case 0x42:ch = 0x7C; break;//"b"	// translate the ASCII character into seven segment data
		case 0x43:ch = 0x39; break;//"C"	// translate the ASCII character into seven segment data
		case 0x44:ch = 0x5E; break;//"d"	// translate the ASCII character into seven segment data
		case 0x45:ch = 0x79; break;//"E"	// translate the ASCII character into seven segment data
		case 0x46:ch = 0x71; break;//"F"	// translate the ASCII character into seven segment data
		default  :ch = 0x00; break;//blank	// translate the ASCII character into seven segment data
	}
	return ch;						// return the seven segment data
}
*/


/*
* -----------------------------------------------------------------------------
 * Function Name: FourteenSegXlate
 * Purpose: translate ascii code to 14 segment data
 * Params: U8_T ascii
 * Returns: U16_T 14SegmentData
 * Note:
 * ----------------------------------------------------------------------------
 */
/*
U16_T FourteenSegXlate(U8_T ascii)			// translate the ASCII character into fourtenn segment data
{
	U16_T ch;		// bit     F E D C B A 9 8 7 6 5 4 3 2 1 0
	switch(ascii)	// segment x x a b c d e f g h j k l m n p
	{
		case 0x20:ch = 0x0000; break;//blank // translate ASCII character into fourteen segment data
		case 0x2B:ch = 0x0055; break;//"+" // translate ASCII character into fourteen segment data
		case 0x2D:ch = 0x0011; break;//"-" // translate ASCII character into fourteen segment data
		case 0x2F:ch = 0x0022; break;//"/" // translate ASCII character into fourteen segment data
		case 0x30:ch = 0x3F22; break;//"0" // translate ASCII character into fourteen segment data
		case 0x31:ch = 0x1800; break;//"1" // translate ASCII character into fourteen segment data
		case 0x32:ch = 0x3611; break;//"2" // translate ASCII character into fourteen segment data
		case 0x33:ch = 0x3C10; break;//"3" // translate ASCII character into fourteen segment data
		case 0x34:ch = 0x1911; break;//"4" // translate ASCII character into fourteen segment data
		case 0x35:ch = 0x2D11; break;//"5" // translate ASCII character into fourteen segment data
		case 0x36:ch = 0x2F11; break;//"6" // translate ASCII character into fourteen segment data
		case 0x37:ch = 0x3800; break;//"7" // translate ASCII character into fourteen segment data
		case 0x38:ch = 0x3F11; break;//"8" // translate ASCII character into fourteen segment data
		case 0x39:ch = 0x3D11; break;//"9" // translate ASCII character into fourteen segment data
		case 0x41:ch = 0x3B11; break;//"A" // translate ASCII character into fourteen segment data
//		case 0x41:ch = 0x2000; break;//"A" // light the A segment
		case 0x42:ch = 0x0F11; break;//"B" // translate ASCII character into fourteen segment data
//		case 0x42:ch = 0x1000; break;//"B" // light the B segment
		case 0x43:ch = 0x2700; break;//"C" // translate ASCII character into fourteen segment data
//		case 0x43:ch = 0x0800; break;//"C" // light the C segment
		case 0x44:ch = 0x1E11; break;//"D" // translate ASCII character into fourteen segment data
//		case 0x44:ch = 0x0400; break;//"D" // light the D segment
		case 0x45:ch = 0x2711; break;//"E" // translate ASCII character into fourteen segment data
//		case 0x45:ch = 0x0200; break;//"E" // light the E segment
		case 0x46:ch = 0x2311; break;//"F" // translate ASCII character into fourteen segment data
//		case 0x46:ch = 0x0100; break;//"F" // light the F segment
		case 0x47:ch = 0x2F10; break;//"G" // translate ASCII character into fourteen segment data
//		case 0x47:ch = 0x0080; break;//"G" // light the G segment
		case 0x48:ch = 0x1B11; break;//"H" // translate ASCII character into fourteen segment data
//		case 0x48:ch = 0x0040; break;//"H" // light the H segment
		case 0x49:ch = 0x2444; break;//"I" // translate ASCII character into fourteen segment data
		case 0x4A:ch = 0x1E00; break;//"J" // translate ASCII character into fourteen segment data
//		case 0x4A:ch = 0x0020; break;//"J" // light the J segment
		case 0x4B:ch = 0x0329; break;//"K" // translate ASCII character into fourteen segment data
//		case 0x4B:ch = 0x0010; break;//"K" // light the K segment
		case 0x4C:ch = 0x0700; break;//"L" // translate ASCII character into fourteen segment data
//		case 0x4C:ch = 0x0008; break;//"L" // light the L segment
		case 0x4D:ch = 0x1BA0; break;//"M" // translate ASCII character into fourteen segment data
//		case 0x4D:ch = 0x0004; break;//"M" // light the M segment
		case 0x4E:ch = 0x1B88; break;//"N" // translate ASCII character into fourteen segment data
//		case 0x4E:ch = 0x0002; break;//"N" // light the N segment
		case 0x4F:ch = 0x3F00; break;//"O" // translate ASCII character into fourteen segment data
		case 0x50:ch = 0x3311; break;//"P" // translate ASCII character into fourteen segment data
//		case 0x50:ch = 0x0001; break;//"P" // light the P segment
		case 0x51:ch = 0x3F08; break;//"Q" // translate ASCII character into fourteen segment data
		case 0x52:ch = 0x3319; break;//"R" // translate ASCII character into fourteen segment data
		case 0x53:ch = 0x2C90; break;//"S" // translate ASCII character into fourteen segment data
		case 0x54:ch = 0x2044; break;//"T" // translate ASCII character into fourteen segment data
		case 0x55:ch = 0x1F00; break;//"U" // translate ASCII character into fourteen segment data
		case 0x56:ch = 0x0322; break;//"V" // translate ASCII character into fourteen segment data
		case 0x57:ch = 0x1B0A; break;//"W" // translate ASCII character into fourteen segment data
		case 0x58:ch = 0x00AA; break;//"X" // translate ASCII character into fourteen segment data
		case 0x59:ch = 0x00A4; break;//"Y" // translate ASCII character into fourteen segment data
		case 0x5A:ch = 0x2422; break;//"Z" // translate ASCII character into fourteen segment data
		case 0x5F:ch = 0x0400; break;//"_" // translate ASCII character into fourteen segment data
		case 0x7F:ch = 0x3FFF; break;//DEL // translate ASCII character into fourteen segment data
		default  :ch = 0x0000; break;//BLANK // translate ASCII character into fourteen segment data
	}
	return ch;						// return the seven segment data
}
*/


/*
 * ----------------------------------------------------------------------------
 * Function Name: CreateBitmap
 * Purpose: stuff bit pattern to serial display buffer memory
 * Params:
 * Returns:
 * Note:
 * ----------------------------------------------------------------------------
 */

void CrBitMap(U8_T * SourcePtr, U8_T * DestinationPtr)
{
U8_T i;
// translate KY1 digit
LCDByte = (*SourcePtr);
KY1A = LCDByteBitZero;				
LCDByte >>=1;
KY1B = LCDByteBitZero;				
LCDByte >>=1;
KY1C = LCDByteBitZero;				
LCDByte >>=1;
KY1D = LCDByteBitZero;				
LCDByte >>=1;
KY1E = LCDByteBitZero;				
LCDByte >>=1;
KY1F = LCDByteBitZero;				
LCDByte >>=1;
KY1G = LCDByteBitZero;				

// translate KY1 Annunciators  
LCDByte = (*(SourcePtr+1));
KY1_PL = LCDByteBitZero;				
LCDByte >>=1;
KY1_CY = LCDByteBitZero;				
LCDByte >>=1;
KY1_DLY = LCDByteBitZero;				

// translate KY2 digit  
LCDByte = (*(SourcePtr+2));
KY2A = LCDByteBitZero;				
LCDByte >>=1;
KY2B = LCDByteBitZero;				
LCDByte >>=1;
KY2C = LCDByteBitZero;				
LCDByte >>=1;
KY2D = LCDByteBitZero;				
LCDByte >>=1;
KY2E = LCDByteBitZero;				
LCDByte >>=1;
KY2F = LCDByteBitZero;				
LCDByte >>=1;
KY2G = LCDByteBitZero;				

// translate KY2 Annunciators  
LCDByte = (*(SourcePtr+3));
KY2_PL = LCDByteBitZero;				
LCDByte >>=1;
KY2_CY = LCDByteBitZero;				
LCDByte >>=1;
KY2_DLY = LCDByteBitZero;				


// save holt driver data U1
 for(i=0; i<5; i++){ // yes, set all bits
  (*(DestinationPtr+i)) = LCDBitMap[i];
  }
}


























