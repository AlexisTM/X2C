/*
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 642 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef __MINMAXPERIODIC_FIP32__
#define __MINMAXPERIODIC_FIP32__

#include "CommonFcts.h"

#if !defined(MINMAXPERIODIC_FIP32_ISLINKED)
#define MINMAXPERIODIC_FIP32_ID ((uint16)466)

typedef struct {
        uint16       ID;
        int32        *In;
        int32        *phi;
        int32        max;
        int32        min;
        int32        min_act;
        int32        max_act;
        int32        phi_old;
} MINMAXPERIODIC_FIP32;

#define MINMAXPERIODIC_FIP32_FUNCTIONS {MINMAXPERIODIC_FIP32_ID, \
                              (void (*)(void*))MinMaxPeriodic_FiP32_Update, \
                              (void (*)(void*))MinMaxPeriodic_FiP32_Init, \
                              (uint8 (*)(void*, uint8[]))Common_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Common_Save, \
                              (void* (*)(void*, uint16))MinMaxPeriodic_FiP32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void MinMaxPeriodic_FiP32_Update(MINMAXPERIODIC_FIP32 *pTMinMaxPeriodic_FiP32);
void MinMaxPeriodic_FiP32_Init(MINMAXPERIODIC_FIP32 *pTMinMaxPeriodic_FiP32);
void* MinMaxPeriodic_FiP32_GetAddress(const MINMAXPERIODIC_FIP32* block, uint16 elementId);

#endif

#endif
