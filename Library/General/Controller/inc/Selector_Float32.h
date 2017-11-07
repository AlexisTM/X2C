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
/* Description: 															  */
/*		Passing through of input signal selected by the select inport:		  */
/*		  Select = 0 (DSP): Out = In0										  */
/*		  Select = 1 (DSP): Out = In1										  */
/*  	  ...																  */
/*  	  Select = 7 (DSP): Out = In7										  */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#ifndef __SELECTOR_FLOAT32__
#define __SELECTOR_FLOAT32__

#include "CommonFcts.h"

#if !defined(SELECTOR_FLOAT32_ISLINKED)
#define SELECTOR_FLOAT32_ID ((uint16)403)

typedef struct {
        uint16       ID;
        float32      *In0;
        float32      *In1;
        float32      *In2;
        float32      *In3;
        float32      *In4;
        float32      *In5;
        float32      *In6;
        float32      *In7;
        int8         *Select;
        float32      Out;
} SELECTOR_FLOAT32;

#define SELECTOR_FLOAT32_FUNCTIONS {SELECTOR_FLOAT32_ID, \
                              (void (*)(void*))Selector_Float32_Update, \
                              (void (*)(void*))Selector_Float32_Init, \
                              (uint8 (*)(void*, uint8[]))Common_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Common_Save, \
                              (void* (*)(void*, uint16))Selector_Float32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Selector_Float32_Update(SELECTOR_FLOAT32 *pTSelector_Float32);
void Selector_Float32_Init(SELECTOR_FLOAT32 *pTSelector_Float32);
void* Selector_Float32_GetAddress(const SELECTOR_FLOAT32* block, uint16 elementId);

#endif

#endif
