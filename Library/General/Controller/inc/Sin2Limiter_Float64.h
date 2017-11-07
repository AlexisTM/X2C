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
#ifndef __SIN2LIMITER_FLOAT64__
#define __SIN2LIMITER_FLOAT64__

#include "CommonFcts.h"

#if !defined(SIN2LIMITER_FLOAT64_ISLINKED)
#define SIN2LIMITER_FLOAT64_ID ((uint16)116)

typedef struct {
        uint16       ID;
        float64      *In;
        float64      Out;
        float64      RateUp;
        float64      RateDown;
        float64      Scaled_RateUp;
        float64      Scaled_RateDown;
        float64      Out_end;
        float64      Level;
        float64      Step_Height;
        int8         State;
} SIN2LIMITER_FLOAT64;

#define SIN2LIMITER_FLOAT64_FUNCTIONS {SIN2LIMITER_FLOAT64_ID, \
                              (void (*)(void*))Sin2Limiter_Float64_Update, \
                              (void (*)(void*))Sin2Limiter_Float64_Init, \
                              (uint8 (*)(void*, uint8[]))Sin2Limiter_Float64_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Sin2Limiter_Float64_Save, \
                              (void* (*)(void*, uint16))Sin2Limiter_Float64_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Sin2Limiter_Float64_Update(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64);
void Sin2Limiter_Float64_Init(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64);
uint8 Sin2Limiter_Float64_Load(const SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64, uint8 data[]);
uint8 Sin2Limiter_Float64_Save(SIN2LIMITER_FLOAT64 *pTSin2Limiter_Float64, const uint8 data[], uint8 frameLength);
void* Sin2Limiter_Float64_GetAddress(const SIN2LIMITER_FLOAT64* block, uint16 elementId);

#endif

#endif
