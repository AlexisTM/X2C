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
 * $LastChangedRevision: 470 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description:	Constant value.
 */
/* USERCODE-END:Description                                                                                           */
#include "uConstant_FiP16.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Outputs */
#define OUT				(pTuConstant_FiP16->Out)		/* Q15 */
 													
/* Parameter */
#define VALUE 			(pTuConstant_FiP16->K)			/* Q15 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** No Update function                                                                                               **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void uConstant_FiP16_Init(UCONSTANT_FIP16 *pTuConstant_FiP16)
{
     pTuConstant_FiP16->ID = UCONSTANT_FIP16_ID;
     pTuConstant_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     OUT = VALUE;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uConstant_FiP16_Load(const UCONSTANT_FIP16 *pTuConstant_FiP16, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)(pTuConstant_FiP16->K & 0x00FF);
     data[1] = (uint8)((pTuConstant_FiP16->K >> 8) & 0x00FF);
     loadSize = (uint8)2;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uConstant_FiP16_Save(UCONSTANT_FIP16 *pTuConstant_FiP16, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)2)
     {
          error = (uint8)1;
     }
     else
     {
          pTuConstant_FiP16->K = UINT16_TO_INT16((uint16)data[0] + \
               ((uint16)data[1] << 8));
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
          OUT = VALUE;
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(UCONSTANT_FIP16_ISLINKED)
void* uConstant_FiP16_GetAddress(const UCONSTANT_FIP16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
