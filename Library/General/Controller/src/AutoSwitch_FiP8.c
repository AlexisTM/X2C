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
 * $LastChangedRevision: 681 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/*     Description:  Switch between In1 and In3 dependent on Switch signal:   */
/*    			Switch signal rising:  Switch > Threshold up --> Out = In1	  */
/*    			Switch signal falling: Switch < Threshold down --> Out = In3  */
/*																			  */
/* USERCODE-END:Description                                                                                           */
#include "AutoSwitch_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(AutoSwitch_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
/* Inputs */
#define IN1 				(*pTAutoSwitch_FiP8->In1)
#define SWITCH 				(*pTAutoSwitch_FiP8->Switch)
#define IN3 				(*pTAutoSwitch_FiP8->In3)

/* Outputs */
#define OUT 				(pTAutoSwitch_FiP8->Out)

/* Parameter */
#define THRESH_UP 			(pTAutoSwitch_FiP8->Thresh_up)
#define THRESH_DOWN 		(pTAutoSwitch_FiP8->Thresh_down)

/* Variables */
#define STATUS 				(pTAutoSwitch_FiP8->Status)

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void AutoSwitch_FiP8_Update(AUTOSWITCH_FIP8 *pTAutoSwitch_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	if (SWITCH >= THRESH_UP)
	{
		/* positive crossing of upper threshold level -> change hysteresis state */
		STATUS = 1;
	}
	else if (SWITCH < THRESH_DOWN)
	{
		/* negative crossing of lower threshold level -> change hysteresis state */
		STATUS = 0;
	}
	/* else: no change in hysteresis state */


	/* set output according to hysteresis status */
	if (STATUS != 0)
	{
		OUT = IN1;
	}
	else
	{
		OUT = IN3;
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void AutoSwitch_FiP8_Init(AUTOSWITCH_FIP8 *pTAutoSwitch_FiP8)
{
     pTAutoSwitch_FiP8->ID = AUTOSWITCH_FIP8_ID;
     pTAutoSwitch_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
     STATUS = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AutoSwitch_FiP8_Load(const AUTOSWITCH_FIP8 *pTAutoSwitch_FiP8, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)pTAutoSwitch_FiP8->Thresh_up;
     data[1] = (uint8)pTAutoSwitch_FiP8->Thresh_down;
     loadSize = (uint8)2;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 AutoSwitch_FiP8_Save(AUTOSWITCH_FIP8 *pTAutoSwitch_FiP8, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)2)
     {
          error = (uint8)1;
     }
     else
     {
          pTAutoSwitch_FiP8->Thresh_up = UINT8_TO_INT8((uint8)data[0]);
          pTAutoSwitch_FiP8->Thresh_down = UINT8_TO_INT8((uint8)data[1]);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(AUTOSWITCH_FIP8_ISLINKED)
void* AutoSwitch_FiP8_GetAddress(const AUTOSWITCH_FIP8* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In1;
            break;
        case 2:
            addr = (void*)block->Switch;
            break;
        case 3:
            addr = (void*)block->In3;
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
