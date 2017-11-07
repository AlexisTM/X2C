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
/**     Description:	Output change rate limitation                        **/
/**						Calculation:										 **/
/**							u > y:											 **/
/**								y(k)     = y(k-1) + RateUp					 **/
/**								RateUp   = 1/Tr * Ts						 **/
/**							u < y:											 **/
/**								y(k)     = y(k-1) - RateDown				 **/
/**								RateDown = 1/Tf * Ts						 **/
/**                                                                          **/
/* USERCODE-END:Description                                                                                           */
#include "RateLimiter_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(RateLimiter_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTRateLimiter_Float64->In)
#define INIT		(*pTRateLimiter_Float64->Init)
#define ENABLE		(*pTRateLimiter_Float64->Enable)

/* Outputs */
#define OUT 		(pTRateLimiter_Float64->Out)

/* Parameters */
#define RATE_UP		(pTRateLimiter_Float64->RateUp)
#define RATE_DOWN	(pTRateLimiter_Float64->RateDown)

/* Variables */
#define ENABLE_OLD	(pTRateLimiter_Float64->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void RateLimiter_Float64_Update(RATELIMITER_FLOAT64 *pTRateLimiter_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
 	float64	Diff;

 	if (ENABLE == 0)	/* Rate limiting disabled */
 	{
 		OUT = IN;
 	}
 	else				/* Rate limiting enabled */
 	{
 		if (ENABLE_OLD == 0)
 		{
 			/* rising edge of enable signal occurred */
 			OUT = INIT;						/* assign output to init value */
 		}
 		else
 		{
			/* step height */
			Diff = IN - OUT;

			/* check for type of step */
			if (Diff > 0)		/* positive step */
			{
				if (Diff > RATE_UP)		/* step is higher than RateUp */
				{
					OUT = OUT + RATE_UP;	/* increase output */
				}
				else
				{
					OUT = IN;				/* assign output */
				}
			}
			else if (Diff < 0)	/* negative step */
			{
				if (-Diff > RATE_DOWN)	/* step is lower than RateDown */
				{
					OUT = OUT - RATE_DOWN;	/* decrease output */
				}
				else
				{
					OUT = IN;				/* assign output */
				}
			}
 		}
 	}
 	ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void RateLimiter_Float64_Init(RATELIMITER_FLOAT64 *pTRateLimiter_Float64)
{
     pTRateLimiter_Float64->ID = RATELIMITER_FLOAT64_ID;
     pTRateLimiter_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 RateLimiter_Float64_Load(const RATELIMITER_FLOAT64 *pTRateLimiter_Float64, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp)) & 0x00000000000000FF);
     data[1] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp) >> 8) & 0x00000000000000FF);
     data[2] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp) >> 16) & 0x00000000000000FF);
     data[3] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp) >> 24) & 0x00000000000000FF);
     data[4] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp) >> 32) & 0x00000000000000FF);
     data[5] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp) >> 40) & 0x00000000000000FF);
     data[6] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp) >> 48) & 0x00000000000000FF);
     data[7] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateUp) >> 56) & 0x00000000000000FF);
     data[8] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown)) & 0x00000000000000FF);
     data[9] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown) >> 8) & 0x00000000000000FF);
     data[10] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown) >> 16) & 0x00000000000000FF);
     data[11] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown) >> 24) & 0x00000000000000FF);
     data[12] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown) >> 32) & 0x00000000000000FF);
     data[13] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown) >> 40) & 0x00000000000000FF);
     data[14] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown) >> 48) & 0x00000000000000FF);
     data[15] = (uint8)((*(uint64*)&(pTRateLimiter_Float64->RateDown) >> 56) & 0x00000000000000FF);
     loadSize = (uint8)16;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 RateLimiter_Float64_Save(RATELIMITER_FLOAT64 *pTRateLimiter_Float64, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;
     uint64 tmp64;

     if (frameLength != (uint8)16)
     {
          error = (uint8)1;
     }
     else
     {
          tmp64 = (uint64)data[0] + \
               ((uint64)data[1] << 8) + ((uint64)data[2] << 16) + \
               ((uint64)data[3] << 24) + ((uint64)data[4] << 32) + \
               ((uint64)data[5] << 40) + ((uint64)data[6] << 48) + \
               ((uint64)data[7] << 56);
          pTRateLimiter_Float64->RateUp = (float64)(*(float64*)&tmp64);
          tmp64 = (uint64)data[8] + \
               ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
               ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
               ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
               ((uint64)data[15] << 56);
          pTRateLimiter_Float64->RateDown = (float64)(*(float64*)&tmp64);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(RATELIMITER_FLOAT64_ISLINKED)
void* RateLimiter_Float64_GetAddress(const RATELIMITER_FLOAT64* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)block->Init;
            break;
        case 3:
            addr = (void*)block->Enable;
            break;
        case 4:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
