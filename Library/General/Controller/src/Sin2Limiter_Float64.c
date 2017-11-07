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
#include "Sin2Limiter_Float64.h"

/* all used update functions to ram for c2000                                                                         */
#if defined(__ALL_UPDATE_FUNC_2_RAM_C2000__)
     #pragma CODE_SECTION(Sin2Limiter_Float64_Update, "ramfuncs")
#endif

/* USERCODE-BEGIN:PreProcessor                                                                                        */
#include <math.h>

/* Inputs */
#define IN 					(*pTSin2Limiter_Float64->In)

/* Outputs */
#define OUT 				(pTSin2Limiter_Float64->Out)

/* Parameters */
#define RATE_UP				(pTSin2Limiter_Float64->RateUp)				/* rising slew rate */
#define RATE_DOWN			(pTSin2Limiter_Float64->RateDown)			/* falling slew rate */

/* Variables */
#define SCALED_RATE_UP		(pTSin2Limiter_Float64->Scaled_RateUp)		/* to step height adjusted rising slew rate */
#define SCALED_RATE_DOWN	(pTSin2Limiter_Float64->Scaled_RateDown)	/* to step height adjusted falling slew rate */
#define OUT_END				(pTSin2Limiter_Float64->Out_end)			/* desired target value */
#define LEVEL	  			(pTSin2Limiter_Float64->Level)				/* current input level (argument) for sin^2 calculation */
#define STEP_HEIGHT			(pTSin2Limiter_Float64->Step_Height)		/* current step height */
#define STATE				(pTSin2Limiter_Float64->State)				/* 1 -> limiting at rising flank, -1 -> limiting at falling flank, 0 -> no limiting */

/* Constants */
#define HALFPI				(PI_R64/2.0)								/* pi/2 */

/* USERCODE-END:PreProcessor                                                                                          */

/**********************************************************************************************************************/
/** Update                                                                                                           **/
/**********************************************************************************************************************/
void Sin2Limiter_Float64_Update(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64)
{
/* USERCODE-BEGIN:UpdateFnc                                                                                           */
	float64	sin2;
 	float64	derivative, temp;

	if (STATE == 0)
	{
		/* derivative */
		derivative = IN - OUT;

		/* check for change in input signal */
		if (derivative > 0)			/* positive step */
		{
			STATE = 1;						/* save direction information */
			LEVEL = HALFPI;					/* preset level */
			STEP_HEIGHT = derivative;		/* save step height*/
			OUT_END = IN;

			/* justification of rate factor in respect to step height */
			SCALED_RATE_UP = RATE_UP / STEP_HEIGHT;
		}
		else
		{
			if (derivative < 0)		/* negative step */
			{
				STATE = -1;					/* save direction information */
				LEVEL = HALFPI;				/* preset level */
				STEP_HEIGHT = -derivative;	/* save step height*/
				OUT_END = IN;

				/* justification of rate factor in respect to step height */
				SCALED_RATE_DOWN = RATE_DOWN / STEP_HEIGHT;
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
			sin2 = sin(LEVEL);				/* calculate sin(level) */
			sin2 = sin2 * sin2;				/* calculate sin^2(level) */
			temp = sin2 * STEP_HEIGHT;		/* scale sin^2 to step height */
			OUT = OUT_END - temp;			/* subtract sin^2 from desired end value */

			break;

		case -1:	/* negative rate limiting */
			if (LEVEL <= SCALED_RATE_DOWN)	/* check if level has reached final value */
			{
				/* rate limitation has finished */
				LEVEL = 0;
				STATE = 0;
			}
			else
			{
				LEVEL -= SCALED_RATE_DOWN;	/* calculate new level value */
			}
			sin2 = sin(LEVEL);				/* calculate sin(level) */
			sin2 = sin2 * sin2;				/* calculate sin^2(level) */
			sin2 = -sin2;					/* adapt sin^2 to falling flank */
			temp = sin2 * STEP_HEIGHT;		/* scale sin^2 to step height */
			OUT  = OUT_END - temp;			/* subtract sin^2 from desired end value */
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
void Sin2Limiter_Float64_Init(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64)
{
     pTSin2Limiter_Float64->ID = SIN2LIMITER_FLOAT64_ID;
     pTSin2Limiter_Float64->Out = 0;
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
uint8 Sin2Limiter_Float64_Load(const SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64, uint8 data[])
{
     uint8 loadSize;

     data[0] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp)) & 0x00000000000000FF);
     data[1] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp) >> 8) & 0x00000000000000FF);
     data[2] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp) >> 16) & 0x00000000000000FF);
     data[3] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp) >> 24) & 0x00000000000000FF);
     data[4] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp) >> 32) & 0x00000000000000FF);
     data[5] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp) >> 40) & 0x00000000000000FF);
     data[6] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp) >> 48) & 0x00000000000000FF);
     data[7] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateUp) >> 56) & 0x00000000000000FF);
     data[8] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown)) & 0x00000000000000FF);
     data[9] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown) >> 8) & 0x00000000000000FF);
     data[10] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown) >> 16) & 0x00000000000000FF);
     data[11] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown) >> 24) & 0x00000000000000FF);
     data[12] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown) >> 32) & 0x00000000000000FF);
     data[13] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown) >> 40) & 0x00000000000000FF);
     data[14] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown) >> 48) & 0x00000000000000FF);
     data[15] = (uint8)((*(uint64*)&(pTSin2Limiter_Float64->RateDown) >> 56) & 0x00000000000000FF);
     loadSize = (uint8)16;
/* USERCODE-BEGIN:LoadFnc                                                                                             */
/* USERCODE-END:LoadFnc                                                                                               */
     return (loadSize);
}

/**********************************************************************************************************************/
/** Save block data                                                                                                  **/
/**********************************************************************************************************************/
uint8 Sin2Limiter_Float64_Save(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64, const uint8 data[], 
          uint8 frameLength)
{
     uint8 error;
     uint64 tmp64;

     if (frameLength != (uint8)16)
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
          pTSin2Limiter_Float64->RateUp = (float64)(*(float64*)&tmp64);
          tmp64 = (uint64)data[8] + \
               ((uint64)data[9] << 8) + ((uint64)data[10] << 16) + \
               ((uint64)data[11] << 24) + ((uint64)data[12] << 32) + \
               ((uint64)data[13] << 40) + ((uint64)data[14] << 48) + \
               ((uint64)data[15] << 56);
          pTSin2Limiter_Float64->RateDown = (float64)(*(float64*)&tmp64);
          error = (uint8)0;
/* USERCODE-BEGIN:SaveFnc                                                                                             */
/* USERCODE-END:SaveFnc                                                                                               */
     }
     return (error);
}

/**********************************************************************************************************************/
/** Get block element address                                                                                        **/
/**********************************************************************************************************************/
#if !defined(SIN2LIMITER_FLOAT64_ISLINKED)
void* Sin2Limiter_Float64_GetAddress(const SIN2LIMITER_FLOAT64* block, uint16 elementId)
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
