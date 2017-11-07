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
#ifndef __SIN2LIMITER_FLOAT32__
#define __SIN2LIMITER_FLOAT32__

#include "CommonFcts.h"

#if !defined(SIN2LIMITER_FLOAT32_ISLINKED)
#define SIN2LIMITER_FLOAT32_ID ((uint16)115)

typedef struct {
        uint16       ID;
        float32      *In;
        float32      Out;
        float32      RateUp;
        float32      RateDown;
        float32      Scaled_RateUp;
        float32      Scaled_RateDown;
        float32      Out_end;
        float32      Level;
        float32      Step_Height;
        int8         State;
} SIN2LIMITER_FLOAT32;

#define SIN2LIMITER_FLOAT32_FUNCTIONS {SIN2LIMITER_FLOAT32_ID, \
                              (void (*)(void*))Sin2Limiter_Float32_Update, \
                              (void (*)(void*))Sin2Limiter_Float32_Init, \
                              (uint8 (*)(void*, uint8[]))Sin2Limiter_Float32_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Sin2Limiter_Float32_Save, \
                              (void* (*)(void*, uint16))Sin2Limiter_Float32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Sin2Limiter_Float32_Update(SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32);
void Sin2Limiter_Float32_Init(SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32);
uint8 Sin2Limiter_Float32_Load(const SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32, uint8 data[]);
uint8 Sin2Limiter_Float32_Save(SIN2LIMITER_FLOAT32 *pTSin2Limiter_Float32, const uint8 data[], uint8 frameLength);
void* Sin2Limiter_Float32_GetAddress(const SIN2LIMITER_FLOAT32* block, uint16 elementId);

#endif

#endif
