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
 * $LastChangedRevision: 457 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef __SATURATION_FLOAT32__
#define __SATURATION_FLOAT32__

#include "CommonFcts.h"

#if !defined(SATURATION_FLOAT32_ISLINKED)
#define SATURATION_FLOAT32_ID ((uint16)83)

typedef struct {
        uint16       ID;
        float32      *In;
        float32      Out;
        float32      max;
        float32      min;
} SATURATION_FLOAT32;

#define SATURATION_FLOAT32_FUNCTIONS {SATURATION_FLOAT32_ID, \
                              (void (*)(void*))Saturation_Float32_Update, \
                              (void (*)(void*))Saturation_Float32_Init, \
                              (uint8 (*)(void*, uint8[]))Saturation_Float32_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Saturation_Float32_Save, \
                              (void* (*)(void*, uint16))Saturation_Float32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Saturation_Float32_Update(SATURATION_FLOAT32 *pTSaturation_Float32);
void Saturation_Float32_Init(SATURATION_FLOAT32 *pTSaturation_Float32);
uint8 Saturation_Float32_Load(const SATURATION_FLOAT32 *pTSaturation_Float32, uint8 data[]);
uint8 Saturation_Float32_Save(SATURATION_FLOAT32 *pTSaturation_Float32, const uint8 data[], uint8 frameLength);
void* Saturation_Float32_GetAddress(const SATURATION_FLOAT32* block, uint16 elementId);

#endif

#endif
