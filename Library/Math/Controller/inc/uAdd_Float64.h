/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 457 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*      Description:	Addition of Input 1 and Input 2 with output wrapping. */
/*						Calculation:										  */
/* 							Out = In1 + In2									  */
/* 																			  */
/* USERCODE-END:Description                                                                                           */
#ifndef __UADD_FLOAT64__
#define __UADD_FLOAT64__

#include "CommonFcts.h"

#if !defined(UADD_FLOAT64_ISLINKED)
#define UADD_FLOAT64_ID     ((uint16)4980)

typedef struct {
        uint16       ID;
        float64      *In1;
        float64      *In2;
        float64      Out;
} UADD_FLOAT64;

#define UADD_FLOAT64_FUNCTIONS {UADD_FLOAT64_ID, \
                              (void (*)(void*))uAdd_Float64_Update, \
                              (void (*)(void*))uAdd_Float64_Init, \
                              (uint8 (*)(void*, uint8[]))Common_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Common_Save, \
                              (void* (*)(void*, uint16))uAdd_Float64_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void uAdd_Float64_Update(UADD_FLOAT64 *pTuAdd_Float64);
void uAdd_Float64_Init(UADD_FLOAT64 *pTuAdd_Float64);
void* uAdd_Float64_GetAddress(const UADD_FLOAT64* block, uint16 elementId);

#endif

#endif
