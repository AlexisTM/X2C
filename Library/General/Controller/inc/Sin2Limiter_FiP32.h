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
#ifndef __SIN2LIMITER_FIP32__
#define __SIN2LIMITER_FIP32__

#include "CommonFcts.h"

#if !defined(SIN2LIMITER_FIP32_ISLINKED)
#define SIN2LIMITER_FIP32_ID ((uint16)114)

typedef struct {
        uint16       ID;
        int32        *In;
        int32        Out;
        int32        RateUp;
        int32        RateDown;
        int32        Scaled_RateUp;
        int32        Scaled_RateDown;
        int32        Out_end;
        uint32       Level;
        int32        Step_Height;
        int8         State;
} SIN2LIMITER_FIP32;

#define SIN2LIMITER_FIP32_FUNCTIONS {SIN2LIMITER_FIP32_ID, \
                              (void (*)(void*))Sin2Limiter_FiP32_Update, \
                              (void (*)(void*))Sin2Limiter_FiP32_Init, \
                              (uint8 (*)(void*, uint8[]))Sin2Limiter_FiP32_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Sin2Limiter_FiP32_Save, \
                              (void* (*)(void*, uint16))Sin2Limiter_FiP32_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Sin2Limiter_FiP32_Update(SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32);
void Sin2Limiter_FiP32_Init(SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32);
uint8 Sin2Limiter_FiP32_Load(const SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32, uint8 data[]);
uint8 Sin2Limiter_FiP32_Save(SIN2LIMITER_FIP32 *pTSin2Limiter_FiP32, const uint8 data[], uint8 frameLength);
void* Sin2Limiter_FiP32_GetAddress(const SIN2LIMITER_FIP32* block, uint16 elementId);

#endif

#endif
