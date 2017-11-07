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
#ifndef __UADD_FLOAT32__
#define __UADD_FLOAT32__

#include "CommonFcts.h"

#if !defined(UADD_FLOAT32_ISLINKED)
#define UADD_FLOAT32_ID     ((uint16)4979)

typedef struct {
        uint16       ID;
        float32      *In1;
        float32      *In2;
        float32      Out;
} UADD_FLOAT32;

#define UADD_FLOAT32_FUNCTIONS {UADD_FLOAT32_ID, \
                              (void (*)(void*))uAdd_Float32_Update, \
                              (void (*)(void*))uAdd_Float32_Init, \
                              (uint8 (*)(void*, uint8[]))Common_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Common_Save, \
                              (void* (*)(void*, uint16))uAdd_Float32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void uAdd_Float32_Update(UADD_FLOAT32 *pTuAdd_Float32);
void uAdd_Float32_Init(UADD_FLOAT32 *pTuAdd_Float32);
void* uAdd_Float32_GetAddress(const UADD_FLOAT32* block, uint16 elementId);

#endif

#endif
