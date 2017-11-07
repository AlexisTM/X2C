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
 * $LastChangedRevision: 737 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Sum of all inputs.                                   										 **/
/**																													 **/
/**						Sign bit field:																				 **/
/**							00->0 ... Input will be ignored.														 **/
/**							01->+ ... Input will be added to result.												 **/
/**							10->- ... Input will be subtracted from result.	 										 **/
/**																			 										 **/
/* USERCODE-END:Description                                                                                           */
#include "Sum_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(Sum_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN1				(*pTSum_FiP8->In1)		/* Q7 */
#define IN2				(*pTSum_FiP8->In2)		/* Q7 */
#define IN3				(*pTSum_FiP8->In3)		/* Q7 */
#define IN4				(*pTSum_FiP8->In4)		/* Q7 */
#define IN5				(*pTSum_FiP8->In5)		/* Q7 */
#define IN6				(*pTSum_FiP8->In6)		/* Q7 */
#define IN7				(*pTSum_FiP8->In7)		/* Q7 */
#define IN8				(*pTSum_FiP8->In8)		/* Q7 */

/* Outputs */
#define OUT	 			(pTSum_FiP8->Out)		/* Q7 */
 													
/* Parameter */
#define	SIGN			(pTSum_FiP8->sign)		/* Bitfield */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sum_FiP8_Update(SUM_FIP8 *pTSum_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16  sum  =  (int16)0;
	uint16 mask = (uint16)0;

	/* Input 1 */
	mask = (uint16)SIGN & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum = (int16)IN1;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum = -(int16)IN1;
		}
	}

	/* Input 2 */
	mask = (((uint16)SIGN) >> 2) & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum += (int16)IN2;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum -= (int16)IN2;
		}
	}

	/* Input 3 */
	mask = (((uint16)SIGN) >> 4) & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum += (int16)IN3;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum -= (int16)IN3;
		}
	}

	/* Input 4 */
	mask = (((uint16)SIGN) >> 6) & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum += (int16)IN4;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum -= (int16)IN4;
		}
	}

	/* Input 5 */
	mask = (((uint16)SIGN) >> 8) & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum += (int16)IN5;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum -= (int16)IN5;
		}
	}

	/* Input 6 */
	mask = (((uint16)SIGN) >> 10) & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum += (int16)IN6;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum -= (int16)IN6;
		}
	}

	/* Input 7 */
	mask = (((uint16)SIGN) >> 12) & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum += (int16)IN7;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum -= (int16)IN7;
		}
	}

	/* Input 8 */
	mask = (((uint16)SIGN) >> 14) & (uint16)0x0003;
	if(mask == (uint16)1)		/* plus */
	{
		sum += (int16)IN8;
	}
	else
	{
		if (mask == (uint16)2)	/* minus */
		{
			sum -= (int16)IN8;
		}
	}



	/* Output */
	if (sum > (int16)INT8_MAX)
	{
		sum = (int16)INT8_MAX;
	}
	else
	{
		if (sum < -(int16)INT8_MAX)
		{
			sum = -(int16)INT8_MAX;
		}
	}
	OUT = (int8)sum;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Sum_FiP8_Init(SUM_FIP8 *pTSum_FiP8)
{
     pTSum_FiP8->ID = SUM_FIP8_ID;
     pTSum_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sum_FiP8_Load(const SUM_FIP8 *pTSum_FiP8, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)(pTSum_FiP8->sign & 0x00FF);
     data[1] = (uint8)((pTSum_FiP8->sign >> 8) & 0x00FF);
     loadSize = (uint8)2;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sum_FiP8_Save(SUM_FIP8 *pTSum_FiP8, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)2)
     {
          error = (uint8)1;
     }
     else
     {
          pTSum_FiP8->sign = ((uint16)data[0] + \
               ((uint16)data[1] << 8));
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SUM_FIP8_ISLINKED)
void* Sum_FiP8_GetAddress(const SUM_FIP8* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In1;
            break;
        case 2:
            addr = (void*)block->In2;
            break;
        case 3:
            addr = (void*)block->In3;
            break;
        case 4:
            addr = (void*)block->In4;
            break;
        case 5:
            addr = (void*)block->In5;
            break;
        case 6:
            addr = (void*)block->In6;
            break;
        case 7:
            addr = (void*)block->In7;
            break;
        case 8:
            addr = (void*)block->In8;
            break;
        case 9:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
