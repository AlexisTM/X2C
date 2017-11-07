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
 * $LastChangedRevision: 461 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description:	 PID Controller with
 *							- Enable Input
 *							- Anti Windup
 *							- Initial Condition Input
 *						Calculation ZOH:
 *	       						          1       	        z - 1
 * 						y = (Kp + Ki*Ts ----- + Kd*wc --------------- )*u
 *          					        z - 1	 	  z - exp(-wc*Ts)
 *
 *						-> y(k) = b1.u(k) + b0.u(k-1) + y(k-1) + b1d.u(k) + b0d.u(k-1) - a0d.yd(k-1)
 *
 *						Note:
 *							PIDLimit source code is used!
 */
/* USERCODE-END:Description                                                                                           */
#include "PID_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(PID_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN 				(*pTPID_Float64->In)
#define ENABLE 			(*pTPID_Float64->Enable)
#define INIT 			(*pTPID_Float64->Init)

/* Outputs */
#define OUT				(pTPID_Float64->Out)

/* Parameter */
#define	B0				(pTPID_Float64->b0)
#define	B1				(pTPID_Float64->b1)
#define	B0D				(pTPID_Float64->b0d)
#define	B1D				(pTPID_Float64->b1d)
#define	A0D				(pTPID_Float64->a0d)

/* Variables */
#define I_OLD			(pTPID_Float64->i_old)
#define IN_OLD			(pTPID_Float64->in_old)
#define D_OLD			(pTPID_Float64->d_old)
#define ENABLE_OLD		(pTPID_Float64->enable_old)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void PID_Float64_Update(PID_FLOAT64 *pTPID_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64 yp, yd;

	if (ENABLE != 0)	/* Block enabled */
	{
		if (ENABLE_OLD == 0)	/* rising edge of enable signal occurred */
		{
		 	/* preset old values */
		 	I_OLD  = INIT;
			IN_OLD = 0;
			D_OLD  = 0;
		}

		/* Proportional term */
		yp  = B1 * IN;

   		/* Derivative term */
		yd  =  B0D * IN_OLD;
		yd += (B1D * IN);
		yd -= (A0D * D_OLD);

		/* Sum */
		OUT = yp + yd + I_OLD;

		/* Integral term */
		I_OLD += (B0 * IN);

		/* Save relevant data for next call */
		IN_OLD = IN;
		D_OLD  = yd;

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
void PID_Float64_Init(PID_FLOAT64 *pTPID_Float64)
{
     pTPID_Float64->ID = PID_FLOAT64_ID;
     pTPID_Float64->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
   	/* preset old values */
    I_OLD  = INIT;
   	IN_OLD = 0;
   	D_OLD  = 0;
    ENABLE_OLD = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PID_Float64_Load(const PID_FLOAT64 *pTPID_Float64, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)((*(uint64*)&(pTPID_Float64->b0)) & 0x00000000000000FF);
     data[1] = (uint8)((*(uint64*)&(pTPID_Float64->b0) >> 8) & 0x00000000000000FF);
     data[2] = (uint8)((*(uint64*)&(pTPID_Float64->b0) >> 16) & 0x00000000000000FF);
     data[3] = (uint8)((*(uint64*)&(pTPID_Float64->b0) >> 24) & 0x00000000000000FF);
     data[4] = (uint8)((*(uint64*)&(pTPID_Float64->b0) >> 32) & 0x00000000000000FF);
     data[5] = (uint8)((*(uint64*)&(pTPID_Float64->b0) >> 40) & 0x00000000000000FF);
     data[6] = (uint8)((*(uint64*)&(pTPID_Float64->b0) >> 48) & 0x00000000000000FF);
     data[7] = (uint8)((*(uint64*)&(pTPID_Float64->b0) >> 56) & 0x00000000000000FF);
     data[8] = (uint8)((*(uint64*)&(pTPID_Float64->b1)) & 0x00000000000000FF);
     data[9] = (uint8)((*(uint64*)&(pTPID_Float64->b1) >> 8) & 0x00000000000000FF);
     data[10] = (uint8)((*(uint64*)&(pTPID_Float64->b1) >> 16) & 0x00000000000000FF);
     data[11] = (uint8)((*(uint64*)&(pTPID_Float64->b1) >> 24) & 0x00000000000000FF);
     data[12] = (uint8)((*(uint64*)&(pTPID_Float64->b1) >> 32) & 0x00000000000000FF);
     data[13] = (uint8)((*(uint64*)&(pTPID_Float64->b1) >> 40) & 0x00000000000000FF);
     data[14] = (uint8)((*(uint64*)&(pTPID_Float64->b1) >> 48) & 0x00000000000000FF);
     data[15] = (uint8)((*(uint64*)&(pTPID_Float64->b1) >> 56) & 0x00000000000000FF);
     data[16] = (uint8)((*(uint64*)&(pTPID_Float64->b0d)) & 0x00000000000000FF);
     data[17] = (uint8)((*(uint64*)&(pTPID_Float64->b0d) >> 8) & 0x00000000000000FF);
     data[18] = (uint8)((*(uint64*)&(pTPID_Float64->b0d) >> 16) & 0x00000000000000FF);
     data[19] = (uint8)((*(uint64*)&(pTPID_Float64->b0d) >> 24) & 0x00000000000000FF);
     data[20] = (uint8)((*(uint64*)&(pTPID_Float64->b0d) >> 32) & 0x00000000000000FF);
     data[21] = (uint8)((*(uint64*)&(pTPID_Float64->b0d) >> 40) & 0x00000000000000FF);
     data[22] = (uint8)((*(uint64*)&(pTPID_Float64->b0d) >> 48) & 0x00000000000000FF);
     data[23] = (uint8)((*(uint64*)&(pTPID_Float64->b0d) >> 56) & 0x00000000000000FF);
     data[24] = (uint8)((*(uint64*)&(pTPID_Float64->b1d)) & 0x00000000000000FF);
     data[25] = (uint8)((*(uint64*)&(pTPID_Float64->b1d) >> 8) & 0x00000000000000FF);
     data[26] = (uint8)((*(uint64*)&(pTPID_Float64->b1d) >> 16) & 0x00000000000000FF);
     data[27] = (uint8)((*(uint64*)&(pTPID_Float64->b1d) >> 24) & 0x00000000000000FF);
     data[28] = (uint8)((*(uint64*)&(pTPID_Float64->b1d) >> 32) & 0x00000000000000FF);
     data[29] = (uint8)((*(uint64*)&(pTPID_Float64->b1d) >> 40) & 0x00000000000000FF);
     data[30] = (uint8)((*(uint64*)&(pTPID_Float64->b1d) >> 48) & 0x00000000000000FF);
     data[31] = (uint8)((*(uint64*)&(pTPID_Float64->b1d) >> 56) & 0x00000000000000FF);
     data[32] = (uint8)((*(uint64*)&(pTPID_Float64->a0d)) & 0x00000000000000FF);
     data[33] = (uint8)((*(uint64*)&(pTPID_Float64->a0d) >> 8) & 0x00000000000000FF);
     data[34] = (uint8)((*(uint64*)&(pTPID_Float64->a0d) >> 16) & 0x00000000000000FF);
     data[35] = (uint8)((*(uint64*)&(pTPID_Float64->a0d) >> 24) & 0x00000000000000FF);
     data[36] = (uint8)((*(uint64*)&(pTPID_Float64->a0d) >> 32) & 0x00000000000000FF);
     data[37] = (uint8)((*(uint64*)&(pTPID_Float64->a0d) >> 40) & 0x00000000000000FF);
     data[38] = (uint8)((*(uint64*)&(pTPID_Float64->a0d) >> 48) & 0x00000000000000FF);
     data[39] = (uint8)((*(uint64*)&(pTPID_Float64->a0d) >> 56) & 0x00000000000000FF);
     loadSize = (uint8)40;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 PID_Float64_Save(PID_FLOAT64 *pTPID_Float64, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;
     uint64 tmp64;

     if (frameLength != (uint8)40)
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
          pTPID_Float64->b0 = (float64)(*(float64*)&tmp64);
          tmp64 = (uint64)data[8] + \
               ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
               ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
               ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
               ((uint64)data[15] << 56);
          pTPID_Float64->b1 = (float64)(*(float64*)&tmp64);
          tmp64 = (uint64)data[16] + \
               ((uint64)data[17] << 8) + ((uint64)data[18] << 16) + \
               ((uint64)data[19] << 24) + ((uint64)data[20] << 32) + \
               ((uint64)data[21] << 40) + ((uint64)data[22] << 48) + \
               ((uint64)data[23] << 56);
          pTPID_Float64->b0d = (float64)(*(float64*)&tmp64);
          tmp64 = (uint64)data[24] + \
               ((uint64)data[25] << 8) + ((uint64)data[26] << 16) + \
               ((uint64)data[27] << 24) + ((uint64)data[28] << 32) + \
               ((uint64)data[29] << 40) + ((uint64)data[30] << 48) + \
               ((uint64)data[31] << 56);
          pTPID_Float64->b1d = (float64)(*(float64*)&tmp64);
          tmp64 = (uint64)data[32] + \
               ((uint64)data[33] << 8) + ((uint64)data[34] << 16) + \
               ((uint64)data[35] << 24) + ((uint64)data[36] << 32) + \
               ((uint64)data[37] << 40) + ((uint64)data[38] << 48) + \
               ((uint64)data[39] << 56);
          pTPID_Float64->a0d = (float64)(*(float64*)&tmp64);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(PID_FLOAT64_ISLINKED)
void* PID_Float64_GetAddress(const PID_FLOAT64* block, uint16 elementId)
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
