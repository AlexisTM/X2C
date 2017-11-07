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
 * $LastChangedRevision: 981 $
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
#include "I_FiP16.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(I_FiP16_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTI_FiP16->In)		/* Q15 */
#define ENABLE 			(*pTI_FiP16->Enable)	/* Q0 */
#define INIT 			(*pTI_FiP16->Init)		/* Q15 */

/* Outputs */
#define OUT	 			(pTI_FiP16->Out)		/* Q15 */
													
/* Parameter */
#define	B0				(pTI_FiP16->b0)			/* Qy */
#define SFR0			(pTI_FiP16->sfr)		/* y */

/* Variables */ 
#define I_OLD			(pTI_FiP16->i_old)		/* Q30 */
#define ENABLE_OLD		(pTI_FiP16->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void I_FiP16_Update(I_FIP16 *pTI_FiP16)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int32 y;

	if (ENABLE != 0)	/* Block enabled */
	{
		if (ENABLE_OLD == 0)	/* rising edge of enable signal occurred */
		{
		 	/* preset old value */
		 	I_OLD = ((int32)INIT) << 15;
		}

		/* Calculate output */
		y = I_OLD >> 15;			/* Q15 */

		/* Output limitation */
		if (y > INT16_MAX)
		{
			/* upper limit */
        	y = INT16_MAX;
        	I_OLD = y << 15;		/* Integral term */
        }
		else if (y < -INT16_MAX)
		{
			/* lower limit */
            y = -INT16_MAX;
            I_OLD = y << 15;		/* Integral term */
        }
		else
		{
			/* No output limitation -> no limitation of integral term */
            #ifdef __XC16__
                I_OLD += ((__builtin_mulss(B0,IN)) << (15-SFR0));	/* Q30 */
            #else
                I_OLD += (((int32)B0 * (int32)IN) << (15-SFR0));	/* Q30 */
            #endif
            
		}

		/* Assign output */
		OUT = (int16)y;

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
void I_FiP16_Init(I_FIP16 *pTI_FiP16)
{
     pTI_FiP16->ID = I_FIP16_ID;
     pTI_FiP16->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
 	/* preset old values */
 	I_OLD = ((int32)INIT) << 15;
 	ENABLE_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 I_FiP16_Load(const I_FIP16 *pTI_FiP16, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)(pTI_FiP16->b0 & 0x00FF);
     data[1] = (uint8)((pTI_FiP16->b0 >> 8) & 0x00FF);
     data[2] = (uint8)pTI_FiP16->sfr;
     loadSize = (uint8)3;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 I_FiP16_Save(I_FIP16 *pTI_FiP16, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)3)
     {
          error = (uint8)1;
     }
     else
     {
          pTI_FiP16->b0 = UINT16_TO_INT16((uint16)data[0] + \
               ((uint16)data[1] << 8));
          pTI_FiP16->sfr = UINT8_TO_INT8((uint8)data[2]);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(I_FIP16_ISLINKED)
void* I_FiP16_GetAddress(const I_FIP16* block, uint16 elementId)
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
