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
#ifndef __SIN2LIMITER_FIP8__
#define __SIN2LIMITER_FIP8__

#include "CommonFcts.h"

#if !defined(SIN2LIMITER_FIP8_ISLINKED)
#define SIN2LIMITER_FIP8_ID ((uint16)112)

typedef struct {
        uint16       ID;
        int8         *In;
        int8         Out;
        int16        RateUp;
        int16        RateDown;
        int16        Scaled_RateUp;
        int16        Scaled_RateDown;
        int8         Out_end;
        uint16       Level;
        int16        Step_Height;
        int8         State;
} SIN2LIMITER_FIP8;

#define SIN2LIMITER_FIP8_FUNCTIONS {SIN2LIMITER_FIP8_ID, \
                              (void (*)(void*))Sin2Limiter_FiP8_Update, \
                              (void (*)(void*))Sin2Limiter_FiP8_Init, \
                              (uint8 (*)(void*, uint8[]))Sin2Limiter_FiP8_Load, \
                              (uint8 (*)(void*, uint8[], uint8))Sin2Limiter_FiP8_Save, \
                              (void* (*)(void*, uint16))Sin2Limiter_FiP8_GetAddress}

/**********************************************************************************************************************/
/** Public prototypes                                                                                                **/
/**********************************************************************************************************************/
void Sin2Limiter_FiP8_Update(SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8);
void Sin2Limiter_FiP8_Init(SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8);
uint8 Sin2Limiter_FiP8_Load(const SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8, uint8 data[]);
uint8 Sin2Limiter_FiP8_Save(SIN2LIMITER_FIP8 *pTSin2Limiter_FiP8, const uint8 data[], uint8 frameLength);
void* Sin2Limiter_FiP8_GetAddress(const SIN2LIMITER_FIP8* block, uint16 elementId);

#endif

#endif
