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
/**     Description:	I Controller with                                   **/
/**							- Enable Input									 **/
/**							- Initial Condition Input	 					 **/
/**						Calculation ZOH:									 **/
/**	       						           1          				 		 **/
/** 						y = ( Ki*Ts* -----  ) * u						 **/
/**          					         z - 1	   							 **/
/**																			 **/
/**						-> y(k) = b1.u(k) + b0.u(k-1) + y(k-1)				 **/
/**																			 **/
/* USERCODE-END:Description                                                                                           */
#include "I_FiP32.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(I_FiP32_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTI_FiP32->In)		/* Q31 */
#define ENABLE 			(*pTI_FiP32->Enable)	/* Q0 */
#define INIT 			(*pTI_FiP32->Init)		/* Q31 */

/* Outputs */
#define OUT	 			(pTI_FiP32->Out)		/* Q31 */
													
/* Parameter */
#define	B0				(pTI_FiP32->b0)			/* Qy */
#define SFR0			(pTI_FiP32->sfr)		/* y */

/* Variables */ 
#define I_OLD			(pTI_FiP32->i_old)		/* Q62 */
#define ENABLE_OLD		(pTI_FiP32->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void I_FiP32_Update(I_FIP32 *pTI_FiP32)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int64 y;

	if (ENABLE != 0)	/* Block enabled */
	{
		if (ENABLE_OLD == 0)	/* rising edge of enable signal occurred */
		{
		 	/* preset old value */
		 	I_OLD = ((int64)INIT) << 31;
		}

		/* Calculate output */
		y = I_OLD >> 31;			/* Q31 */

		/* Output limitation */
		if (y > INT32_MAX)
		{
			/* upper limit */
        	y = INT32_MAX;
        	I_OLD = y << 31;		/* Integral term */
        }
		else if (y < -INT32_MAX)
		{
			/* lower limit */
            y = -INT32_MAX;
            I_OLD = y << 31;		/* Integral term */
        }
		else
		{
			/* No output limitation -> no limitation of integral term */
			I_OLD += (((int64)B0 * (int64)IN) << (31-SFR0));	/* Q62 */
		}

		/* Assign output */
		OUT = (int32)y;

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
void I_FiP32_Init(I_FIP32 *pTI_FiP32)
{
     pTI_FiP32->ID = I_FIP32_ID;
     pTI_FiP32->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	/* preset old values */
    I_OLD = ((int64)INIT) << 31;
 	ENABLE_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 I_FiP32_Load(const I_FIP32 *pTI_FiP32, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)(pTI_FiP32->b0 & 0x000000FF);
     data[1] = (uint8)((pTI_FiP32->b0 >> 8) & 0x000000FF);
     data[2] = (uint8)((pTI_FiP32->b0 >> 16) & 0x000000FF);
     data[3] = (uint8)((pTI_FiP32->b0 >> 24) & 0x000000FF);
     data[4] = (uint8)pTI_FiP32->sfr;
     loadSize = (uint8)5;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 I_FiP32_Save(I_FIP32 *pTI_FiP32, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)5)
     {
          error = (uint8)1;
     }
     else
     {
          pTI_FiP32->b0 = UINT32_TO_INT32((uint32)data[0] + \
               ((uint32)data[1] << 8) + ((uint32)data[2] << 16) + \
               ((uint32)data[3] << 24));
          pTI_FiP32->sfr = UINT8_TO_INT8((uint8)data[4]);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(I_FIP32_ISLINKED)
void* I_FiP32_GetAddress(const I_FIP32* block, uint16 elementId)
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
