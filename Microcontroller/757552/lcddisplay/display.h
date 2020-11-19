/*
 ******************************************************************************
 *     Copyright (c) 2013	Simtek INC.      All rights reserved.
 *
 *     This is unpublished proprietary source code of Simtek INC.
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
/*=============================================================================
 * Module Name:Display.h
 * Purpose: display routines 
 * Author:
 * Date:
 * Notes:
 *=============================================================================
 */
#ifndef __DISPLAY_H
#define __DISPLAY_H

/* INCLUDE FILE DECLARATIONS */

/* GLOBAL CONSTANTS */

/* GLOBAL VARIABLES */


/* EXPORTED SUBPROGRAM SPECIFICATIONS */
/*-------------------------------------------------------------*/
extern void DISPLAY_HI8045DriverLoad(U8_T * bmapptr, U8_T loop);
extern void DISPLAY_Align(void);
//extern void DISPLAY_AllSegmentsOn(void);
//extern void DISPLAY_AllSegmentsOff(void);
extern void DISPLAY_Blank(void);
extern void DISPLAY_Test(void);
extern void LongDelay(U8_T count,U16_T loop);
extern LD8;
extern LD16;

/* End of display.h */

#endif /* End of __DISPLAY_H__ */


