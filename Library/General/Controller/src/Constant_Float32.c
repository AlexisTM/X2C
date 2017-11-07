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
 * $LastChangedRevision: 1000 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Constant value.                                      **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "Constant_Float32.h"

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Outputs */
#define OUT				(pTConstant_Float32->Out)

/* Parameter */
#define VALUE 			(pTConstant_Float32->K)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** No Update function                                                                                               **/
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Constant_Float32_Init(CONSTANT_FLOAT32 *pTConstant_Float32)
{
     pTConstant_Float32->ID = CONSTANT_FLOAT32_ID;
     pTConstant_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     OUT = VALUE;
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Constant_Float32_Load(const CONSTANT_FLOAT32 *pTConstant_Float32, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)((*(uint32*)&(pTConstant_Float32->K)) & 0x000000FF);
     data[1] = (uint8)((*(uint32*)&(pTConstant_Float32->K) >> 8) & 0x000000FF);
     data[2] = (uint8)((*(uint32*)&(pTConstant_Float32->K) >> 16) & 0x000000FF);
     data[3] = (uint8)((*(uint32*)&(pTConstant_Float32->K) >> 24) & 0x000000FF);
     loadSize = (uint8)4;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Constant_Float32_Save(CONSTANT_FLOAT32 *pTConstant_Float32, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;
     uint32 tmp32;

     if (frameLength != (uint8)4)
     {
          error = (uint8)1;
     }
     else
     {
          tmp32 = (uint32)data[0] + \
               ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
               ((uint32)data[3] << 24);
          pTConstant_Float32->K = (float32)(*(float32*)&tmp32);
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
#if !defined(CONSTANT_FLOAT32_ISLINKED)
void* Constant_Float32_GetAddress(const CONSTANT_FLOAT32* block, uint16 elementId)
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
