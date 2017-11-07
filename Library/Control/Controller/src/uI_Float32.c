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
/**     Description:	Integrator for angle signals                         **/
/**						Calculation ZOH:									 **/
/**	       						           1          				 		 **/
/** 						y = ( Ki*Ts* -----  ) * u						 **/
/**          					         z - 1	   							 **/
/**																			 **/
/**						-> y(k) = b1.u(k) + b0.u(k-1) + y(k-1)				 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "uI_Float32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(uI_Float32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTuI_Float32->In)
#define ENABLE 			(*pTuI_Float32->Enable)
#define INIT 			(*pTuI_Float32->Init)

/* Outputs */
#define OUT	 			(pTuI_Float32->Out)

/* Parameter */
#define	B0				(pTuI_Float32->b0)

/* Variables */
#define I_OLD			(pTuI_Float32->i_old)
#define ENABLE_OLD		(pTuI_Float32->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void uI_Float32_Update(UI_FLOAT32 *pTuI_Float32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	if (ENABLE != 0)	/* Block enabled */
	{
		if (ENABLE_OLD == 0)	/* rising edge of enable signal occurred */
		{
		 	/* preset old value */
			I_OLD = INIT;
		}

		/* Angle limitation to -pi...+pi */
		while (I_OLD >= PI_R32)
		{
			I_OLD = I_OLD - (2 * PI_R32);
		}
		while (I_OLD < - PI_R32)
		{
			I_OLD = I_OLD + (2 * PI_R32);
		}

		/* Assign output */
		OUT = I_OLD;

		/* Integral term */
		I_OLD += (B0 * IN);

	}
	else				/* Block disabled */
	{
		OUT = 0;	/* reset output */
	}
	ENABLE_OLD = ENABLE;

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void uI_Float32_Init(UI_FLOAT32 *pTuI_Float32)
{
     pTuI_Float32->ID = UI_FLOAT32_ID;
     pTuI_Float32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
   	/* preset old values */
 	I_OLD = INIT;
   	ENABLE_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uI_Float32_Load(const UI_FLOAT32 *pTuI_Float32, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)((*(uint32*)&(pTuI_Float32->b0)) & 0x000000FF);
     data[1] = (uint8)((*(uint32*)&(pTuI_Float32->b0) >> 8) & 0x000000FF);
     data[2] = (uint8)((*(uint32*)&(pTuI_Float32->b0) >> 16) & 0x000000FF);
     data[3] = (uint8)((*(uint32*)&(pTuI_Float32->b0) >> 24) & 0x000000FF);
     loadSize = (uint8)4;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 uI_Float32_Save(UI_FLOAT32 *pTuI_Float32, const uint8 data[], 
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
          pTuI_Float32->b0 = (float32)(*(float32*)&tmp32);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(UI_FLOAT32_ISLINKED)
void* uI_Float32_GetAddress(const UI_FLOAT32* block, uint16 elementId)
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
