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
/**     Description:	Saturation of output to adjustable upper and lower	 **/
/**						limit.												 **/	
/**                     Calculation:                                         **/
/**							Out = In										 **/
/**								--> with Out = [min..max]			 		 **/
/**						Range:												 **/
/**							In:		-1..1								 	 **/
/**							Out:	min..max							 	 **/
/**							min:	-1..max									 **/
/**							max:	min..1	 								 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "Saturation_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(Saturation_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 		(*pTSaturation_FiP8->In)		/* Q7 */

/* Outputs */
#define OUT	 	(pTSaturation_FiP8->Out)		/* Q7 */

/* Parameter */
#define MAX		(pTSaturation_FiP8->max)		/* upper limit, Q7 */
#define MIN		(pTSaturation_FiP8->min)		/* lower limit, Q7 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Saturation_FiP8_Update(SATURATION_FIP8 *pTSaturation_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	OUT = IN;
	if (OUT > MAX)
	{
		/* input signal is higher than maximum allowed value */
		OUT = MAX;
	}
	else if (OUT < MIN)
	{
		/* input signal is lower than minimum allowed value */
		OUT = MIN;
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Saturation_FiP8_Init(SATURATION_FIP8 *pTSaturation_FiP8)
{
     pTSaturation_FiP8->ID = SATURATION_FIP8_ID;
     pTSaturation_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Saturation_FiP8_Load(const SATURATION_FIP8 *pTSaturation_FiP8, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)pTSaturation_FiP8->max;
     data[1] = (uint8)pTSaturation_FiP8->min;
     loadSize = (uint8)2;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Saturation_FiP8_Save(SATURATION_FIP8 *pTSaturation_FiP8, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)2)
     {
          error = (uint8)1;
     }
     else
     {
          pTSaturation_FiP8->max = UINT8_TO_INT8((uint8)data[0]);
          pTSaturation_FiP8->min = UINT8_TO_INT8((uint8)data[1]);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SATURATION_FIP8_ISLINKED)
void* Saturation_FiP8_GetAddress(const SATURATION_FIP8* block, uint16 elementId)
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
