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
 * $LastChangedRevision: 705 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/* Description:
 *    Calculation of L2-Norm: ||u|| = sqrt(u1^2 + u2^2)
 */
/* USERCODE-END:Description                                                                                           */
#include "L2Norm_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(L2Norm_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sqrt_Data.h"

/* Inputs */
#define IN1		(*pTL2Norm_FiP32->u1)
#define IN2		(*pTL2Norm_FiP32->u2)

/* Outputs */
#define OUT 	(pTL2Norm_FiP32->Out)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void L2Norm_FiP32_Update(L2NORM_FIP32 *pTL2Norm_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 tmp1, tmp2;
	int32 out;

	tmp1 = (int64)IN1 * (int64)IN1;				/* u1^2 [Q62] */
	tmp2 = (int64)IN2 * (int64)IN2;				/* u2^2 [Q62] */

	tmp1 = (tmp1 + tmp2) >> 31 ;				/* u1^2 + u2^2 [Q31] */
	LIMIT(tmp1, INT32_MAX);

	LOOKUP32(Sqrt_Table32, (int32)tmp1, out);	/* sqrt(u1^2 + u2^2) */

	OUT = out;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void L2Norm_FiP32_Init(L2NORM_FIP32 *pTL2Norm_FiP32)
{
     pTL2Norm_FiP32->ID = L2NORM_FIP32_ID;
     pTL2Norm_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
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
#if !defined(L2NORM_FIP32_ISLINKED)
void* L2Norm_FiP32_GetAddress(const L2NORM_FIP32* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->u1;
            break;
        case 2:
            addr = (void*)block->u2;
            break;
        case 3:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
