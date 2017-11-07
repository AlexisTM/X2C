/*
 * This file is part of X2C. http://www.mechatronic-simulation.org/
 * $LastChangedRevision: 765 $
 */
/* USERCODE-BEGIN:Description                                                                                         */
/**     Description:	Continuously differentiable output change rate limitation with	sin^2 shape                  **/
/**						Calculation:                               													 **/
/**							du/dt = 0:																				 **/
/**								y = u																				 **/
/**							du/dt <> 0:																				 **/
/**								y = u * sin^2(t)		(simplified)												 **/
/**																													 **/
/**		Caution:	A step in the input signal during a	running limitation process will not abort the running        **/
/**					limitation process!																				 **/
/**																													 **/
/* USERCODE-END:Description                                                                                           */
#include "Sin2Limiter_FiP8.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(Sin2Limiter_FiP8_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include "Sin2_Data.h"

/* Inputs */
#define IN 					(*pTSin2Limiter_FiP8->In)

/* Outputs */
#define OUT 				(pTSin2Limiter_FiP8->Out)

/* Parameters */
#define RATE_UP				(pTSin2Limiter_FiP8->RateUp)			/* rising slew rate */
#define RATE_DOWN			(pTSin2Limiter_FiP8->RateDown)			/* falling slew rate */

/* Variables */
#define SCALED_RATE_UP		(pTSin2Limiter_FiP8->Scaled_RateUp)		/* to step height adjusted rising slew rate */
#define SCALED_RATE_DOWN	(pTSin2Limiter_FiP8->Scaled_RateDown)	/* to step height adjusted falling slew rate */
#define OUT_END				(pTSin2Limiter_FiP8->Out_end)			/* desired target value */
#define LEVEL	  			(pTSin2Limiter_FiP8->Level)				/* current input level (argument) for sin^2 calculation */
#define STEP_HEIGHT			(pTSin2Limiter_FiP8->Step_Height)		/* current step height */
#define STATE				(pTSin2Limiter_FiP8->State)				/* 1 -> limiting at rising flank, -1 -> limiting at falling flank, 0 -> no limiting */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sin2Limiter_FiP8_Update(SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	int8	sin2;
 	int16	derivative, temp;

	if (STATE == 0)
	{
		/* derivative */
		derivative = (int16)IN - (int16)OUT;

		/* check for change in input signal */
		if (derivative > 0)			/* positive step */
		{
			STATE = 1;							/* save direction information */
			LEVEL = UINT16_MAX;					/* preset level */
			STEP_HEIGHT = derivative << 7;		/* save step height [Q14] */
			OUT_END = IN;

			/* justification of rate factor in respect to step height */
			if ((RATE_UP>>1) >= STEP_HEIGHT)	/* result is not in 0..1 range */
			{
				SCALED_RATE_UP = INT16_MAX;		/* positive saturation */
			}
			else								/* result is in 0..1 range */
			{
				SCALED_RATE_UP = (((int32)RATE_UP)<<15) / STEP_HEIGHT;
			}
		}
		else
		{
			if (derivative < 0)		/* negative step */
			{
				STATE = -1;							/* save direction information */
				LEVEL = UINT16_MAX;					/* preset level */
				STEP_HEIGHT = (-derivative) << 7;	/* save step height [Q14] */
				OUT_END = IN;

				/* justification of rate factor in respect to step height */
				if ((RATE_DOWN>>1) >= STEP_HEIGHT)	/* result is not in -1..0 range */
				{
					SCALED_RATE_DOWN = INT16_MAX;	/* negative saturation */
				}
				else								/* result is in -1..0 range */
				{
					SCALED_RATE_DOWN = (((int32)RATE_DOWN)<<15) / STEP_HEIGHT;
				}
			}
		}
	}

	switch(STATE)
	{
		case 0:		/* no rate limiting in progress */
			OUT = IN;
			break;

		case 1:		/* positive rate limiting */
			if (LEVEL <= SCALED_RATE_UP)   /* check if level has reached final value */
			{
				/* rate limitation has finished */
				LEVEL = 0;
				STATE = 0;
			}
			else
			{
				LEVEL -= SCALED_RATE_UP;	/* calculate new level value */
			}
			LOOKUP8(Sin2_Table8, (LEVEL>>8), sin2);			/* calculate sin^2(level) */
			temp = ((int16)sin2 * (STEP_HEIGHT>>7)) >> 7;	/* scale sin^2 to step height */
			OUT = OUT_END - (int8)temp;						/* subtract sin^2 from desired end value */

			break;

		case -1:	/* negative rate limiting */
			if (LEVEL <= SCALED_RATE_DOWN)	   /* check if level has reached final value */
			{
				/* rate limitation has finished */
				LEVEL = 0;
				STATE = 0;
			}
			else
			{
				LEVEL -= SCALED_RATE_DOWN;	/* calculate new level value */
			}
			LOOKUP8(Sin2_Table8, (LEVEL>>8), sin2);			/* calculate sin^2(level) */
			sin2 = -sin2;									/* adapt sin^2 to falling flank */
			temp = ((int16)sin2 * (STEP_HEIGHT>>7)) >> 7;	/* scale sin^2 to step height */
			OUT  = OUT_END - (int8)temp;					/* subtract sin^2 from desired end value */
			break;
		default:	/* should not occur */
			OUT = IN;
			STATE = 0;
			break;
	}

/* USERCODE-END:UpdateFnc                                                                                             */

}

/**********************************************************************************************************************/
/** Initialization                                                                                                   **/
/**********************************************************************************************************************/
void Sin2Limiter_FiP8_Init(SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8)
{
     pTSin2Limiter_FiP8->ID = SIN2LIMITER_FIP8_ID;
     pTSin2Limiter_FiP8->Out = 0;
/* USERCODE-BEGIN:InitFnc                                                                                             */
    SCALED_RATE_UP   = 0;
    SCALED_RATE_DOWN = 0;
	OUT_END = 0;
	LEVEL = 0;
	STEP_HEIGHT = 0;
	STATE = 0;

/* USERCODE-END:InitFnc                                                                                               */
}

/**********************************************************************************************************************/
/** Load block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin2Limiter_FiP8_Load(const SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)(pTSin2Limiter_FiP8->RateUp & 0x00FF);
     data[1] = (uint8)((pTSin2Limiter_FiP8->RateUp >> 8) & 0x00FF);
     data[2] = (uint8)(pTSin2Limiter_FiP8->RateDown & 0x00FF);
     data[3] = (uint8)((pTSin2Limiter_FiP8->RateDown >> 8) & 0x00FF);
     loadSize = (uint8)4;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin2Limiter_FiP8_Save(SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;

     if (frameLength != (uint8)4)
     {
          error = (uint8)1;
     }
     else
     {
          pTSin2Limiter_FiP8->RateUp = UINT16_TO_INT16((uint16)data[0] + \
               ((uint16)data[1] << 8));
          pTSin2Limiter_FiP8->RateDown = UINT16_TO_INT16((uint16)data[2] + \
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
#if !defined(SIN2LIMITER_FIP8_ISLINKED)
void* Sin2Limiter_FiP8_GetAddress(const SIN2LIMITER_FIP8* block, uint16 elementId)
{
    void* addr;
    switch (elementId)
    {
        case 1:
            addr = (void*)block->In;
            break;
        case 2:
            addr = (void*)&block->Out;
            break;
        default:
            addr = (void*)0;
            break;
    }
    return (addr);
}
#endif
