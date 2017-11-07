/*
 * Copyright (c) 2014, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
 * $LastChangedRevision: 872 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description:	  Delay the input signal by one sample time interval.   	  */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#include "Delay_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(Delay_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTDelay_FiP32->In)

/* Outputs */
#define OUT 			(pTDelay_FiP32->Out)

/* Variables */
#define IN_OLD			(pTDelay_FiP32->In_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Delay_FiP32_Update(DELAY_FIP32 *pTDelay_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	/* Do nothing, just relax and delay! */
	OUT = IN_OLD;
	IN_OLD = IN;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Delay_FiP32_Init(DELAY_FIP32 *pTDelay_FiP32)
{
     pTDelay_FiP32->ID = DELAY_FIP32_ID;
     pTDelay_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     IN_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** No Load function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** No Save function                                                                                                 **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(DELAY_FIP32_ISLINKED)
void* Delay_FiP32_GetAddress(const DELAY_FIP32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
