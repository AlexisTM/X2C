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
 * $LastChangedRevision: 471 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef __SINGEN_FLOAT64__
#define __SINGEN_FLOAT64__

#include "CommonFcts.h"

#if !defined(SINGEN_FLOAT64_ISLINKED)
#define SINGEN_FLOAT64_ID   ((uint16)420)

typedef struct {
        uint16       ID;
        float64      *A;
        float64      *f;
        float64      u;
        float64      delta_phi;
        float64      phase;
        float64      offset;
        float64      phi;
} SINGEN_FLOAT64;

#define SINGEN_FLOAT64_FUNCTIONS {SINGEN_FLOAT64_ID, \
                              (void (*)(void*))SinGen_Float64_Update, \
                              (void (*)(void*))SinGen_Float64_Init, \
                              (uint8 (*)(void*, uint8[]))SinGen_Float64_Load, \
                              (uint8 (*)(void*, uint8[], uint8))SinGen_Float64_Save, \
                              (void* (*)(void*, uint16))SinGen_Float64_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void SinGen_Float64_Update(SINGEN_FLOAT64 *pTSinGen_Float64);
void SinGen_Float64_Init(SINGEN_FLOAT64 *pTSinGen_Float64);
uint8 SinGen_Float64_Load(const SINGEN_FLOAT64 *pTSinGen_Float64, uint8 data[]);
uint8 SinGen_Float64_Save(SINGEN_FLOAT64 *pTSinGen_Float64, const uint8 data[], uint8 frameLength);
void* SinGen_Float64_GetAddress(const SINGEN_FLOAT64* block, uint16 elementId);

#endif

#endif
