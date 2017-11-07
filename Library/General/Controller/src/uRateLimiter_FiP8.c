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
/*      Description:	Output change rate limitation of angle signals        */
/* 						Calculation:										  */
/* 							u > y:											  */
/* 								y(k)     = y(k-1) + RateUp					  */
/* 								RateUp   = 1/Tr * Ts						  */
/* 							u < y:											  */
/* 								y(k)     = y(k-1) - RateDown				  */
/* 								RateDown = 1/Tf * Ts						  */
/*                                                                            */
/* USERCODE-END:Description                                                                                           */
#include "uRateLimiter_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(uRateLimiter_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 			(*pTuRateLimiter_FiP8->In)			/* Q7 */
#define INIT		(*pTuRateLimiter_FiP8->Init)		/* Q7 */
#define ENABLE		(*pTuRateLimiter_FiP8->Enable)		/* Q0  */

/* Outputs */
#define OUT 		(pTuRateLimiter_FiP8->Out)			/* Q7 */

/* Parameters */
#define RATE_UP		(pTuRateLimiter_FiP8->RateUp)		/* Q15 */
#define RATE_DOWN	(pTuRateLimiter_FiP8->RateDown)		/* Q15 */

/* Variables */
#define OUT_OLD		(pTuRateLimiter_FiP8->out_old)		/* Q15 */
#define ENABLE_OLD	(pTuRateLimiter_FiP8->enable_old)	/* Q0  */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void uRateLimiter_FiP8_Update(URATELIMITER_FIP8 *pTuRateLimiter_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
 	int16	temp;
 	int8	Diff;

 	if (ENABLE == 0)	/* Rate limiting disabled */
 	{
 		OUT     = IN;
 		OUT_OLD = ((int16)OUT) << 8;
 	}
 	else				/* Rate limiting enabled */
 	{
 		if (ENABLE_OLD == 0)
 		{
 			/* rising edge of enable signal occurred */
 			OUT = INIT;						/* assign output to init value */
 			OUT_OLD = ((int16)OUT) << 8;	/* save output for next cycle */
 		}
 		else
 		{
			/* step height */
			Diff = IN - OUT;	/* overflow is allowed */ /* TODO: check for correct behavior with TI compilers! */

			/* check for type of step */
			if (Diff > 0)		/* positive step */
			{
				if (Diff > (RATE_UP>>8))		/* step is higher than RateUp */
				{
				   temp = OUT_OLD + RATE_UP;		/* increase output */
				   OUT_OLD = temp;					/* save output for next cycle */
				   OUT = (int8)(temp >> 8);			/* assign output */
				}
				else
				{
					OUT_OLD = ((int16)IN) << 8;		/* save output for next cycle */
					OUT = IN;						/* assign output */

				}
			}
			else if (Diff < 0)	/* negative step */
			{
				if (-Diff > (RATE_DOWN>>8))/* step is lower than RateDown */
				{
					temp = OUT_OLD - RATE_DOWN;		/* decrease output */
					OUT_OLD = temp;					/* save output for next cycle */
					OUT = (int8)(temp >> 8);		/* assign output */
				}
				else
				{
					OUT_OLD = ((int16)IN) << 8;		/* save output for next cycle */
					OUT = IN;						/* assign output */
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
void uRateLimiter_FiP8_Init(URATELIMITER_FIP8 *pTuRateLimiter_FiP8)
{
     pTuRateLimiter_FiP8->ID = URATELIMITER_FIP8_ID;
     pTuRateLimiter_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     OUT_OLD = ((int16)INIT) << 8;
     ENABLE_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uRateLimiter_FiP8_Load(const URATELIMITER_FIP8 *pTuRateLimiter_FiP8, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)(pTuRateLimiter_FiP8->RateUp & 0x00FF);
     data[1] = (uint8)((pTuRateLimiter_FiP8->RateUp >> 8) & 0x00FF);
     data[2] = (uint8)(pTuRateLimiter_FiP8->RateDown & 0x00FF);
     data[3] = (uint8)((pTuRateLimiter_FiP8->RateDown >> 8) & 0x00FF);
     data[4] = (uint8)(pTuRateLimiter_FiP8->out_old & 0x00FF);
     data[5] = (uint8)((pTuRateLimiter_FiP8->out_old >> 8) & 0x00FF);
     loadSize = (uint8)6;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uRateLimiter_FiP8_Save(URATELIMITER_FIP8 *pTuRateLimiter_FiP8, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)4)
     {
          error = (uint8)1;
     }
     else
     {
          pTuRateLimiter_FiP8->RateUp = UINT16_TO_INT16((uint16)data[0] + \
               ((uint16)data[1] << 8));
          pTuRateLimiter_FiP8->RateDown = UINT16_TO_INT16((uint16)data[2] + \
               ((uint16)data[3] << 8));
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(URATELIMITER_FIP8_ISLINKED)
void* uRateLimiter_FiP8_GetAddress(const URATELIMITER_FIP8* block, uint16 elementId)
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
