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
 * $LastChangedRevision: 883 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*      Description: With lookup table approximated arc tangent function	  */
/*                      Calculation:                                          */
/* 							theta = atan2(y,x)						 		  */
/* 						Range:												  */
/* 							y:		-1..1								 	  */
/* 							x:		-1..1								 	  */
/* 							theta:	-pi..pi 								  */
/* 										--> with -pi..pi ~ -1..1		 	  */
/* 																			  */
/* USERCODE-END:Description                                                                                           */
#include "Atan2_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(Atan2_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Atan_Data.h"

/* Inputs */
#define IN1					(*pTAtan2_FiP16->y)
#define IN2					(*pTAtan2_FiP16->x)
			
/* Outputs */
#define THETA 				(pTAtan2_FiP16->Out)

/* Quadrant Offset Macros */
#define ATAN2_OFFSET_Q2		0x4000
#define ATAN2_OFFSET_Q34	0x8000
#define ATAN2_OFFSET_COT	0x3FFF

#define QUARTER_PI			0x2000		/* 45� */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Atan2_FiP16_Update(ATAN2_FIP16 *pTAtan2_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int16   iFact, iY, iX;
	int32	arg  = (int32)0;
	int8	iTan =  (int8)1;		/* 1 -> tangent for Q1 & Q3, 0 -> cotangent for Q2 & Q4 */
	int8	Q13  =  (int8)1;		/* 1 -> Q1 or Q3 */
	int16   out1 = (int16)0;

	iY = IN1;
	iX = IN2;

	if ((iY == 0) && (iX == 0))
	{
		out1 = 0;
	}
	else
	{
		/* Check quadrants */
		if (iY < (int16)0)
		{
			iY   = -iY;
			out1 = ATAN2_OFFSET_Q34;
			if (iX > (int16)0)	/* 4th quadrant */
			{
				out1 += ATAN2_OFFSET_Q2;
				Q13   = (int8)0;
			}
			else
			{			/* 3rd quadrant */
				iX   = -iX;
			}
		}
		else
		{
			if (iX < (int16)0)	/* 2nd quadrant */
			{
				iX   = -iX;
				out1 = ATAN2_OFFSET_Q2;
				Q13  = (int8)0;
			}
		}

		/* Check region in quadrant */
		if (iY > iX)	/* angle > 45� */
		{
			iFact = iX;			/* swap input arguments	 (iFact is used as temporary variable) */
			iX	  = iY;			/* swap input arguments */
			iY    = iFact;		/* swap input arguments */
			iTan  = (int8)0;	/* use cotangent */
		}

		if (iY != iX)
		{
			/* Calculation of y/x */
			arg  = (int32)iY << 16;             /* Q15,32 */				
#if defined(__XC16__)
            arg = __builtin_divsd(arg, iX); /* Q16,32 */
#else
            arg = arg / iX;                /* Q16,32 */
#endif

			/* Interpolation */
			LOOKUP16(Atan_Table16, (uint16)arg, iFact);
		}
		else
		{
			iFact = QUARTER_PI;		/* angle = 45� */
		}

		/* Check for need of cotangent correction */
		if (Q13 ^ iTan)
		{
			out1 += ((int16)ATAN2_OFFSET_COT - iFact);
		}
		else
		{
			out1 += iFact;
		}
	}


	THETA = out1;			/* assign output */

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Atan2_FiP16_Init(ATAN2_FIP16 *pTAtan2_FiP16)
{
     pTAtan2_FiP16->ID = ATAN2_FIP16_ID;
     pTAtan2_FiP16->Out = 0;
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
#if !defined(ATAN2_FIP16_ISLINKED)
void* Atan2_FiP16_GetAddress(const ATAN2_FIP16* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->y;
            break;
        case 2:
            addr = (void*)block->x;
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
