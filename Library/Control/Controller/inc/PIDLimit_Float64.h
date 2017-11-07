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
 * $LastChangedRevision: 465 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description: */
/* USERCODE-END:Description                                                                                           */
#ifndef __PIDLIMIT_FLOAT64__
#define __PIDLIMIT_FLOAT64__

#include "CommonFcts.h"

#if !defined(PIDLIMIT_FLOAT64_ISLINKED)
#define PIDLIMIT_FLOAT64_ID ((uint16)3268)

typedef struct {
        uint16       ID;
        float64      *In;
        float64      *Init;
        float64      *max;
        float64      *min;
        int8         *Enable;
        float64      Out;
        float64      b0;
        float64      b1;
        float64      b0d;
        float64      b1d;
        float64      a0d;
        float64      in_old;
        float64      i_old;
        float64      d_old;
        int8         enable_old;
} PIDLIMIT_FLOAT64;

#define PIDLIMIT_FLOAT64_FUNCTIONS {PIDLIMIT_FLOAT64_ID, \
                              (void (*)(void*))PIDLimit_Float64_Update, \
                              (void (*)(void*))PIDLimit_Float64_Init, \
                              (uint8 (*)(void*, uint8[]))PIDLimit_Float64_Load, \
                              (uint8 (*)(void*, uint8[], uint8))PIDLimit_Float64_Save, \
                              (void* (*)(void*, uint16))PIDLimit_Float64_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void PIDLimit_Float64_Update(PIDLIMIT_FLOAT64 *pTPIDLimit_Float64);
void PIDLimit_Float64_Init(PIDLIMIT_FLOAT64 *pTPIDLimit_Float64);
uint8 PIDLimit_Float64_Load(const PIDLIMIT_FLOAT64 *pTPIDLimit_Float64, uint8 data[]);
uint8 PIDLimit_Float64_Save(PIDLIMIT_FLOAT64 *pTPIDLimit_Float64, const uint8 data[], uint8 frameLength);
void* PIDLimit_Float64_GetAddress(const PIDLIMIT_FLOAT64* block, uint16 elementId);

#endif

#endif
