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
#ifndef __UADD_FIP8__
#define __UADD_FIP8__

#include "CommonFcts.h"

#if !defined(UADD_FIP8_ISLINKED)
#define UADD_FIP8_ID        ((uint16)4976)

typedef struct {
        uint16       ID;
        int8         *In1;
        int8         *In2;
        int8         Out;
} UADD_FIP8;

#define UADD_FIP8_FUNCTIONS {UADD_FIP8_ID, \
                              (void (*)(void*))uAdd_FiP8_Update, \
                              (void (*)(void*))uAdd_FiP8_Init, \
                              (uint8 (*)(void*, uint8[]))Common_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Common_Save, \
                              (void* (*)(void*, uint16))uAdd_FiP8_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void uAdd_FiP8_Update(UADD_FIP8 *pTuAdd_FiP8);
void uAdd_FiP8_Init(UADD_FIP8 *pTuAdd_FiP8);
void* uAdd_FiP8_GetAddress(const UADD_FIP8* block, uint16 elementId);

#endif

#endif
