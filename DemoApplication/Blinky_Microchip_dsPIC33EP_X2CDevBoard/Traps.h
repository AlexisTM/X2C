/** @file
 * @brief Trap handling.
 */
/* $LastChangedRevision: 874 $
 * $LastChangedDate:: 2016-02-18 14:43:14 +0100#$
 *
 * Copyright (c) 2016, Microchip Technology Inc. http://www.microchip.com/
 * All rights reserved.
 */
#ifndef __TRAPS_H__
#define __TRAPS_H__

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif

/* public prototypes */


#endif

