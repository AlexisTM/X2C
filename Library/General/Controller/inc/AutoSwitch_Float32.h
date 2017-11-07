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
/*     Description:  Switch between In1 and In3 dependent on Switch signal:   */
/*    			Switch signal rising:  Switch > Threshold up --> Out = In1	  */
/*    			Switch signal falling: Switch < Threshold down --> Out = In3  */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#ifndef __AUTOSWITCH_FLOAT32__
#define __AUTOSWITCH_FLOAT32__

#include "CommonFcts.h"

#if !defined(AUTOSWITCH_FLOAT32_ISLINKED)
#define AUTOSWITCH_FLOAT32_ID ((uint16)131)

typedef struct {
        uint16       ID;
        float32      *In1;
        float32      *Switch;
        float32      *In3;
        float32      Out;
        float32      Thresh_up;
        float32      Thresh_down;
        int8         Status;
} AUTOSWITCH_FLOAT32;

#define AUTOSWITCH_FLOAT32_FUNCTIONS {AUTOSWITCH_FLOAT32_ID, \
                              (void (*)(void*))AutoSwitch_Float32_Update, \
                              (void (*)(void*))AutoSwitch_Float32_Init, \
                              (uint8 (*)(void*, uint8[]))AutoSwitch_Float32_Load, \
                              (uint8 (*)(void*, uint8[], uint8))AutoSwitch_Float32_Save, \
                              (void* (*)(void*, uint16))AutoSwitch_Float32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void AutoSwitch_Float32_Update(AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32);
void AutoSwitch_Float32_Init(AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32);
uint8 AutoSwitch_Float32_Load(const AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32, uint8 data[]);
uint8 AutoSwitch_Float32_Save(AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32, const uint8 data[], uint8 frameLength);
void* AutoSwitch_Float32_GetAddress(const AUTOSWITCH_FLOAT32* block, uint16 elementId);

#endif

#endif
