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
 * $LastChangedRevision: 738 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Second order transfer function                      										 **/
/**						Calculation:																				 **/
/**	       						 b2.z^2 + b1.z + b0					   												 **/
/** 						y = ------------------ u				   												 **/
/**          					  z^2 + a1.z + a0																	 **/
/**							-> y(k) = u(k).b2 + u(k-1).b1 + u(k-2).b0												 **/
/**									- y(k-1).a1 - y(k-2).a0															 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#ifndef __TF2_FLOAT32__
#define __TF2_FLOAT32__

#include "CommonFcts.h"

#if !defined(TF2_FLOAT32_ISLINKED)
#define TF2_FLOAT32_ID      ((uint16)3299)

typedef struct {
        uint16       ID;
        float32      *In;
        float32      Out;
        float32      b0;
        float32      b1;
        float32      b2;
        float32      a0;
        float32      a1;
        float32      in_old;
        float32      in_veryold;
        float32      out_old;
        float32      out_veryold;
} TF2_FLOAT32;

#define TF2_FLOAT32_FUNCTIONS {TF2_FLOAT32_ID, \
                              (void (*)(void*))TF2_Float32_Update, \
                              (void (*)(void*))TF2_Float32_Init, \
                              (uint8 (*)(void*, uint8[]))TF2_Float32_Load, \
                              (uint8 (*)(void*, uint8[], uint8))TF2_Float32_Save, \
                              (void* (*)(void*, uint16))TF2_Float32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void TF2_Float32_Update(TF2_FLOAT32 *pTTF2_Float32);
void TF2_Float32_Init(TF2_FLOAT32 *pTTF2_Float32);
uint8 TF2_Float32_Load(const TF2_FLOAT32 *pTTF2_Float32, uint8 data[]);
uint8 TF2_Float32_Save(TF2_FLOAT32 *pTTF2_Float32, const uint8 data[], uint8 frameLength);
void* TF2_Float32_GetAddress(const TF2_FLOAT32* block, uint16 elementId);

#endif

#endif
