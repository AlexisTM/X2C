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
/**     Description:	Toggling between the 2 inputs                        **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#ifndef __MANUALSWITCH_FIP16__
#define __MANUALSWITCH_FIP16__

#include "CommonFcts.h"

#if !defined(MANUALSWITCH_FIP16_ISLINKED)
#define MANUALSWITCH_FIP16_ID ((uint16)145)

typedef struct {
        uint16       ID;
        int16        *In1;
        int16        *In2;
        int16        Out;
        int8         Toggle;
} MANUALSWITCH_FIP16;

#define MANUALSWITCH_FIP16_FUNCTIONS {MANUALSWITCH_FIP16_ID, \
                              (void (*)(void*))ManualSwitch_FiP16_Update, \
                              (void (*)(void*))ManualSwitch_FiP16_Init, \
                              (uint8 (*)(void*, uint8[]))ManualSwitch_FiP16_Load, \
                              (uint8 (*)(void*, uint8[], uint8))ManualSwitch_FiP16_Save, \
                              (void* (*)(void*, uint16))ManualSwitch_FiP16_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void ManualSwitch_FiP16_Update(MANUALSWITCH_FIP16 *pTManualSwitch_FiP16);
void ManualSwitch_FiP16_Init(MANUALSWITCH_FIP16 *pTManualSwitch_FiP16);
uint8 ManualSwitch_FiP16_Load(const MANUALSWITCH_FIP16 *pTManualSwitch_FiP16, uint8 data[]);
uint8 ManualSwitch_FiP16_Save(MANUALSWITCH_FIP16 *pTManualSwitch_FiP16, const uint8 data[], uint8 frameLength);
void* ManualSwitch_FiP16_GetAddress(const MANUALSWITCH_FIP16* block, uint16 elementId);

#endif

#endif
