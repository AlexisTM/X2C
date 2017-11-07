/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2016-09-01 10:39                                                                                            */

/* X2C-Version: 1012                                                                                                  */

#include "FlashTable.h"
#include "RamTable.h"
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
CONSTANT_FIP16                TFrequency;
CONSTANT_FIP16                TLED_off;
SIN3GEN_FIP16                 TSin3Gen;
CONSTANT_FIP16                TLED_on;
SINGEN_FIP16                  TSinGen;
AUTOSWITCH_FIP16              TAutoSwitch;
AUTOSWITCH_FIP16              TAutoSwitch1;
CONSTANT_FIP16                TAmplitude;
AUTOSWITCH_FIP16              TOscillator__AutoSwitch;
I_FIP16                       TOscillator__I;
CONSTANT_FIP8                 TOscillator__C_enable;
NEGATION_FIP16                TOscillator__Negation;
CONSTANT_FIP16                TOscillator__C_1;
DELAY_FIP16                   TOscillator__Delay;
CONSTANT_FIP16                TOscillator__C_init;
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

    /* Block Frequency                                                                                                */
    /* Value = 0.0080                                                                                                 */
    TFrequency.K = 262;

    /* Block LEDoff                                                                                                   */
    /* Value = 0.0                                                                                                    */
    TLED_off.K = 0;

    /* Block Sin3Gen                                                                                                  */
    /* fmax = 1000.0                                                                                                  */
    /* Offset = 0.0                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    TSin3Gen.delta_phi = 13107;
    TSin3Gen.offset = 0;
    TSin3Gen.phi = 0;

    /* Block LEDon                                                                                                    */
    /* Value = 1.0                                                                                                    */
    TLED_on.K = 32767;

    /* Block SinGen                                                                                                   */
    /* fmax = 1000.0                                                                                                  */
    /* Offset = 0.0                                                                                                   */
    /* Phase = 0.0                                                                                                    */
    /* ts_fact = 1.0                                                                                                  */
    TSinGen.delta_phi = 13107;
    TSinGen.phase = 0;
    TSinGen.offset = 0;
    TSinGen.phi = 0;

    /* Block AutoSwitch                                                                                               */
    /* Thresh_up = 0.6                                                                                                */
    /* Thresh_down = 0.4                                                                                              */
    TAutoSwitch.Thresh_up = 19661;
    TAutoSwitch.Thresh_down = 13107;
    TAutoSwitch.Status = 0;

    /* Block AutoSwitch1                                                                                              */
    /* Thresh_up = 0.0                                                                                                */
    /* Thresh_down = 0.0                                                                                              */
    TAutoSwitch1.Thresh_up = 0;
    TAutoSwitch1.Thresh_down = 0;
    TAutoSwitch1.Status = 0;

    /* Block Amplitude                                                                                                */
    /* Value = 0.5                                                                                                    */
    TAmplitude.K = 16384;

    /* Block Oscillator__AutoSwitch                                                                                   */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = -0.5                                                                                             */
    TOscillator__AutoSwitch.Thresh_up = 16384;
    TOscillator__AutoSwitch.Thresh_down = -16384;
    TOscillator__AutoSwitch.Status = 0;

    /* Block Oscillator__I                                                                                            */
    /* Ki = 50.0                                                                                                      */
    /* ts_fact = 1.0                                                                                                  */
    TOscillator__I.b0 = 328;
    TOscillator__I.sfr = 15;
    TOscillator__I.i_old = 0;
    TOscillator__I.enable_old = 0;

    /* Block Oscillator__C_enable                                                                                     */
    /* Value = 1.0                                                                                                    */
    TOscillator__C_enable.K = 127;

    /* Block Oscillator__Negation                                                                                     */

    /* Block Oscillator__C_1                                                                                          */
    /* Value = 1.0                                                                                                    */
    TOscillator__C_1.K = 32767;

    /* Block Oscillator__Delay                                                                                        */
    /* ts_fact = 1.0                                                                                                  */
    TOscillator__Delay.In_old = 0;

    /* Block Oscillator__C_init                                                                                       */
    /* Value = 0.0                                                                                                    */
    TOscillator__C_init.K = 0;


    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block Frequency                                                                                                */

    /* Block LEDoff                                                                                                   */

    /* Block Sin3Gen                                                                                                  */
    TSin3Gen.A                       = &TAmplitude.Out;
    TSin3Gen.f                       = &TFrequency.Out;

    /* Block LEDon                                                                                                    */

    /* Block SinGen                                                                                                   */
    TSinGen.A                        = &TAmplitude.Out;
    TSinGen.f                        = &TFrequency.Out;

    /* Block AutoSwitch                                                                                               */
    TAutoSwitch.In1                  = &TLED_off.Out;
    TAutoSwitch.Switch               = &(Inports.Switch1);
    TAutoSwitch.In3                  = &TAutoSwitch1.Out;

    /* Block AutoSwitch1                                                                                              */
    TAutoSwitch1.In1                 = &TLED_off.Out;
    TAutoSwitch1.Switch              = &TSinGen.u;
    TAutoSwitch1.In3                 = &TLED_on.Out;

    /* Block Amplitude                                                                                                */

    /* Block Oscillator__AutoSwitch                                                                                   */
    TOscillator__AutoSwitch.In1      = &TOscillator__Negation.Out;
    TOscillator__AutoSwitch.Switch   = &TOscillator__I.Out;
    TOscillator__AutoSwitch.In3      = &TOscillator__C_1.Out;

    /* Block Oscillator__I                                                                                            */
    TOscillator__I.In                = &TOscillator__Delay.Out;
    TOscillator__I.Init              = &TOscillator__C_init.Out;
    TOscillator__I.Enable            = &TOscillator__C_enable.Out;

    /* Block Oscillator__C_enable                                                                                     */

    /* Block Oscillator__Negation                                                                                     */
    TOscillator__Negation.In         = &TOscillator__C_1.Out;

    /* Block Oscillator__C_1                                                                                          */

    /* Block Oscillator__Delay                                                                                        */
    TOscillator__Delay.In            = &TOscillator__AutoSwitch.Out;

    /* Block Oscillator__C_init                                                                                       */

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    Outports.pLED_green               = &Inports.Cnt;
    Outports.pOsc_out                 = &TOscillator__Delay.Out;
    Outports.pLED_red                 = &TAutoSwitch.Out;
    Outports.pLED_blue                = &Inports.Switch2;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_FiP16_Init(&TFrequency);
    Constant_FiP16_Init(&TLED_off);
    Sin3Gen_FiP16_Init(&TSin3Gen);
    Constant_FiP16_Init(&TLED_on);
    SinGen_FiP16_Init(&TSinGen);
    AutoSwitch_FiP16_Init(&TAutoSwitch);
    AutoSwitch_FiP16_Init(&TAutoSwitch1);
    Constant_FiP16_Init(&TAmplitude);
    AutoSwitch_FiP16_Init(&TOscillator__AutoSwitch);
    I_FiP16_Init(&TOscillator__I);
    Constant_FiP8_Init(&TOscillator__C_enable);
    Negation_FiP16_Init(&TOscillator__Negation);
    Constant_FiP16_Init(&TOscillator__C_1);
    Delay_FiP16_Init(&TOscillator__Delay);
    Constant_FiP16_Init(&TOscillator__C_init);
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
    Delay_FiP16_Update(&TOscillator__Delay);
    SinGen_FiP16_Update(&TSinGen);
    Negation_FiP16_Update(&TOscillator__Negation);
    AutoSwitch_FiP16_Update(&TAutoSwitch1);
    AutoSwitch_FiP16_Update(&TAutoSwitch);
    Sin3Gen_FiP16_Update(&TSin3Gen);
    I_FiP16_Update(&TOscillator__I);
    AutoSwitch_FiP16_Update(&TOscillator__AutoSwitch);
    Scope_Main_Update(&TScope);
}

