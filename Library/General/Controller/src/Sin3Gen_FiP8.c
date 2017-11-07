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
 * $LastChangedRevision: 471 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description:    Sine Wave Generation for 3 Phase System
 *                     Calculation:
 *							u =  A*sin(phi(t)) + Offset
 *							v =  A*sin(phi(t) - 2*pi/3) + Offset
 *							w =  A*sin(phi(t) + 2*pi/3) + Offset
 *							phi(t) = phi(t-1) + 2*pi*Ts*f
 */
/* USERCODE-END:Description                                                                                           */
#include "Sin3Gen_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(Sin3Gen_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin_Data.h"

/* Inputs */
#define AMPLITUDE 		(*pTSin3Gen_FiP8->A)
#define FREQUENCY 		(*pTSin3Gen_FiP8->f)

/* Outputs */
#define OUT_U 			(pTSin3Gen_FiP8->u)
#define OUT_V 			(pTSin3Gen_FiP8->v)
#define OUT_W 			(pTSin3Gen_FiP8->w)

/* Parameter */
#define OFFSET 			(pTSin3Gen_FiP8->offset)
#define DELTA_PHI 		(pTSin3Gen_FiP8->delta_phi)

/* Variables */
#define PHI 	 		(pTSin3Gen_FiP8->phi)

/* Constants */
#define TWOPITHIRDINT8	0x55				/* 2*Pi/3 in Q7 format */
#define TWOPITHIRDINT16	0x5555				/* 2*Pi/3 in Q15 format */
#define ROUNDING		0x40				/* value used for rounding */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sin3Gen_FiP8_Update(SIN3GEN_FIP8 *pTSin3Gen_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int8 	sine, out1, out2, angle;
	int16	temp;

	temp = (int16)DELTA_PHI * (int16)FREQUENCY;	/* calculate angle increment */
	temp += ROUNDING;
	PHI += ((int8)(temp >> 7));					/* scale to 8 Bit (Q14 -> Q7) and increment angle */

	/*------------------------------------------------------------------------*/
	/* Calculation of phase U 												  */
	/*------------------------------------------------------------------------*/
	/* sine calculation */
	#if defined (__C2000__)
		LOOKUP8(Sin_Table8, (PHI & 0x00FF), sine);	/* sin(phi+phase) */
		/* on Texas Instruments DSPs 16 bits are used for int8 datatypes -> masking is required */
	#else
		LOOKUP8(Sin_Table8, PHI, sine);				/* sin(phi+phase) */
	#endif
	/* amplification */
	temp = (int16)AMPLITUDE * (int16)sine;			/* A*sin(phi) */
	temp = (temp + ROUNDING) >> 7;
	/* offset */
	temp += (int16)OFFSET;							/* A*sin(phi) + Offset*/
	/* limitation */
	LIMIT(temp, INT8_MAX);
	out1 = (int8)temp;

	/*------------------------------------------------------------------------*/
	/* Calculation of phase V 												  */
	/*------------------------------------------------------------------------*/
	/* sine calculation */
	angle = PHI - TWOPITHIRDINT8;						/* sin(phi - 2*pi/3) */
	#if defined (__C2000__)
		LOOKUP8(Sin_Table8, (angle & 0x00FF), sine);	/* sin(phi - 2*pi/3) */
		/* on Texas Instruments DSPs 16 bits are used for int8 datatypes -> masking is required */
	#else

		LOOKUP8(Sin_Table8, angle, sine);				/* sin(phi - 2*pi/3) */
	#endif
	/* amplification */
	temp = (int16)AMPLITUDE * (int16)sine;				/* A*sin(phi - 2*pi/3) */
	temp = (temp + ROUNDING) >> 7;
	/* offset */
	temp += (int16)OFFSET;								/* A*sin(phi - 2*pi/3) + Offset*/
	/* limitation */
	LIMIT(temp, INT8_MAX);
	out2 = (int8)temp;

	/*------------------------------------------------------------------------*/
	/* Calculation of phase W 												  */
	/*------------------------------------------------------------------------*/
	/* sine calculation */
	angle = PHI + TWOPITHIRDINT8;						/* sin(phi + 2*pi/3) */
	#if defined (__C2000__)
		LOOKUP8(Sin_Table8, (angle & 0x00FF), sine);	/* sin(phi + 2*pi/3) */
		/* on Texas Instruments DSPs 16 bits are used for int8 datatypes -> masking is required */
	#else

		LOOKUP8(Sin_Table8, angle, sine);				/* sin(phi + 2*pi/3) */
	#endif
	/* amplification */
	temp = (int16)AMPLITUDE * (int16)sine;				/* A*sin(phi + 2*pi/3) */
	temp = (temp + ROUNDING) >> 7;
	/* offset */
	temp += (int16)OFFSET;								/* A*sin(phi + 2*pi/3) + Offset*/
	/* limitation */
	LIMIT(temp, INT8_MAX);

	/*------------------------------------------------------------------------*/
	/* Assigning of outputs													  */
	/*------------------------------------------------------------------------*/
	OUT_U = out1;
	OUT_V = out2;
	OUT_W = (int8)temp;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Sin3Gen_FiP8_Init(SIN3GEN_FIP8 *pTSin3Gen_FiP8)
{
     pTSin3Gen_FiP8->ID = SIN3GEN_FIP8_ID;
     pTSin3Gen_FiP8->u = 0;
     pTSin3Gen_FiP8->v = 0;
     pTSin3Gen_FiP8->w = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	PHI = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin3Gen_FiP8_Load(const SIN3GEN_FIP8 *pTSin3Gen_FiP8, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)pTSin3Gen_FiP8->delta_phi;
     data[1] = (uint8)pTSin3Gen_FiP8->offset;
     loadSize = (uint8)2;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin3Gen_FiP8_Save(SIN3GEN_FIP8 *pTSin3Gen_FiP8, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)2)
     {
          error = (uint8)1;
     }
     else
     {
          pTSin3Gen_FiP8->delta_phi = UINT8_TO_INT8((uint8)data[0]);
          pTSin3Gen_FiP8->offset = UINT8_TO_INT8((uint8)data[1]);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SIN3GEN_FIP8_ISLINKED)
void* Sin3Gen_FiP8_GetAddress(const SIN3GEN_FIP8* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->A;
            break;
        case 2:
            addr = (void*)block->f;
            break;
        case 3:
            addr = (void*)&block->u;
            break;
        case 4:
            addr = (void*)&block->v;
            break;
        case 5:
            addr = (void*)&block->w;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
