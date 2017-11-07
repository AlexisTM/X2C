/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2015-07-29 14:29                                                                                            */

#include "X2C.h"


/*                                                       Inports                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/
TInports Inports;

/*                                                      Outports                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/
TOutports Outports;

/**********************************************************************************************************************/
/**                                              Global Variables Block                                              **/
/**********************************************************************************************************************/
CONSTANT_FIP16                TAmplitude;
SINGEN_FIP16                  TSinGen;
CONSTANT_FIP16                TFrequency;
CONSTANT_FIP16                TLED_off;
AUTOSWITCH_FIP16              TAutoSwitch;
CONSTANT_FIP16                TLED_on;
SIN3GEN_FIP16                 TSin3Gen;
SCOPE_MAIN                    TScope;

/* Block function table                                                                                               */
#define END_BLOCKFUNCTIONS { (uint16)0, (void (*)(void*))0, (void (*)(void*))0, \
    (uint8 (*)(void*, uint8[]))0, (uint8 (*)(void*, uint8[], uint8))0, (void* (*)(void*, uint16))0 }

const tBlockFunctions blockFunctionTable[] = {
    FUNCTIONS,
    END_BLOCKFUNCTIONS
};

/* Parameter identifier table                                                                                         */
#define END_PARAMETERTABLE { (uint16)0, (void*)0 }

const tParameterTable parameterIdTable[] = {
    PARAMETER_TABLE,
    END_PARAMETERTABLE
};

/**********************************************************************************************************************/
/**                                                  Initialization                                                  **/
/**********************************************************************************************************************/
void X2C_Init()
{
    /******************************************************************************************************************/
    /**                                          Initialize Block Parameters                                         **/
    /******************************************************************************************************************/

    /* Block Amplitude                                                                                                */
    /* Value = 0.5                                                                                                    */
    TAmplitude.K = 16384;

    /* Block SinGen                                                                                                   */
    /* fmax = 1000.0                                                                                                  */
    /* Offset = 0.0                                                                                                   */
    /* Phase = 0.0                                                                                                    */
    /* ts_fact = 1.0                                                                                                  */
    TSinGen.delta_phi = 6554;
    TSinGen.phase = 0;
    TSinGen.offset = 0;
    TSinGen.phi = 0;

    /* Block Frequency                                                                                                */
    /* Value = 0.0080                                                                                                 */
    TFrequency.K = 262;

    /* Block LEDoff                                                                                                   */
    /* Value = 0.0                                                                                                    */
    TLED_off.K = 0;

    /* Block AutoSwitch                                                                                               */
    /* Thresh_up = 0.0                                                                                                */
    /* Thresh_down = 0.0                                                                                              */
    TAutoSwitch.Thresh_up = 0;
    TAutoSwitch.Thresh_down = 0;
    TAutoSwitch.Status = 0;

    /* Block LEDon                                                                                                    */
    /* Value = 1.0                                                                                                    */
    TLED_on.K = 32767;

    /* Block Sin3Gen                                                                                                  */
    /* fmax = 1000.0                                                                                                  */
    /* Offset = 0.0                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    TSin3Gen.delta_phi = 6554;
    TSin3Gen.offset = 0;
    TSin3Gen.phi = 0;


    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block Amplitude                                                                                                */

    /* Block SinGen                                                                                                   */
    TSinGen.A                        = &TAmplitude.Out;
    TSinGen.f                        = &TFrequency.Out;

    /* Block Frequency                                                                                                */

    /* Block LEDoff                                                                                                   */

    /* Block AutoSwitch                                                                                               */
    TAutoSwitch.In1                  = &TLED_off.Out;
    TAutoSwitch.Switch               = &TSinGen.u;
    TAutoSwitch.In3                  = &TLED_on.Out;

    /* Block LEDon                                                                                                    */

    /* Block Sin3Gen                                                                                                  */
    TSin3Gen.A                       = &TAmplitude.Out;
    TSin3Gen.f                       = &TFrequency.Out;

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    Outports.pLed2                    = &TAutoSwitch.Out;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_FiP16_Init(&TAmplitude);
    SinGen_FiP16_Init(&TSinGen);
    Constant_FiP16_Init(&TFrequency);
    Constant_FiP16_Init(&TLED_off);
    AutoSwitch_FiP16_Init(&TAutoSwitch);
    Constant_FiP16_Init(&TLED_on);
    Sin3Gen_FiP16_Init(&TSin3Gen);
    Scope_Main_Init(&TScope);
}

/**********************************************************************************************************************/
/**                                            Run Block Update Functions                                            **/
/**********************************************************************************************************************/
void X2C_Update(void)
{
    X2C_Update_1();

}

/* X2C_Update for blocks with 1*Ts                                                                                    */
void X2C_Update_1(void)
{
    SinGen_FiP16_Update(&TSinGen);
    AutoSwitch_FiP16_Update(&TAutoSwitch);
    Sin3Gen_FiP16_Update(&TSin3Gen);
    Scope_Main_Update(&TScope);
}

