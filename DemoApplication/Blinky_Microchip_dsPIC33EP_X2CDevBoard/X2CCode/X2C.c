/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2016-02-18 12:39                                                                                            */

/* X2C-Version: local                                                                                                 */

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
CONSTANT_FIP16                Tfc;
AUTOSWITCH_FIP16              TAutoSwitch1;
NEGATION_FIP16                TOscillator__Negation;
CONSTANT_FIP16                TOscillator__C_1;
AUTOSWITCH_FIP16              TOscillator__AutoSwitch;
I_FIP16                       TOscillator__I;
DELAY_FIP16                   TOscillator__Delay;
CONSTANT_FIP16                TOscillator__C_init;
CONSTANT_FIP8                 TOscillator__C_enable;
AUTOSWITCH_FIP16              TAutoSwitch;
SINGEN_FIP16                  TSinGen;
CONSTANT_FIP16                TAmplitude;
CONSTANT_FIP16                TFrequency;
CONSTANT_FIP16                TLED_off;
CONSTANT_FIP16                TLED_on;
GAIN_FIP16                    TGain;
SIN3GEN_FIP16                 TSin3Gen;
AUTOSWITCH_FIP16              TAutoSwitch2;
ADAPTIVEPT1_FIP16             TAdaptivePT1;
NOT_FIP16                     TNot;
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

    /* Block fc                                                                                                       */
    /* Value = 0.0041                                                                                                 */
    Tfc.K = 134;

    /* Block AutoSwitch1                                                                                              */
    /* Thresh_up = 0.6                                                                                                */
    /* Thresh_down = 0.4                                                                                              */
    TAutoSwitch1.Thresh_up = 19661;
    TAutoSwitch1.Thresh_down = 13107;
    TAutoSwitch1.Status = 0;

    /* Block Oscillator__Negation                                                                                     */

    /* Block Oscillator__C_1                                                                                          */
    /* Value = 1.0                                                                                                    */
    TOscillator__C_1.K = 32767;

    /* Block Oscillator__AutoSwitch                                                                                   */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = -0.5                                                                                             */
    TOscillator__AutoSwitch.Thresh_up = 16384;
    TOscillator__AutoSwitch.Thresh_down = -16384;
    TOscillator__AutoSwitch.Status = 0;

    /* Block Oscillator__I                                                                                            */
    /* Ki = 6.05                                                                                                      */
    /* ts_fact = 1.0                                                                                                  */
    TOscillator__I.b0 = 20;
    TOscillator__I.sfr = 15;
    TOscillator__I.i_old = 0;
    TOscillator__I.enable_old = 0;

    /* Block Oscillator__Delay                                                                                        */
    /* ts_fact = 1.0                                                                                                  */
    TOscillator__Delay.In_old = 0;

    /* Block Oscillator__C_init                                                                                       */
    /* Value = 0.0                                                                                                    */
    TOscillator__C_init.K = 0;

    /* Block Oscillator__C_enable                                                                                     */
    /* Value = 1.0                                                                                                    */
    TOscillator__C_enable.K = 127;

    /* Block AutoSwitch                                                                                               */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = 0.5                                                                                              */
    TAutoSwitch.Thresh_up = 16384;
    TAutoSwitch.Thresh_down = 16384;
    TAutoSwitch.Status = 0;

    /* Block SinGen                                                                                                   */
    /* fmax = 100.0                                                                                                   */
    /* Offset = 0.0                                                                                                   */
    /* Phase = 0.0                                                                                                    */
    /* ts_fact = 1.0                                                                                                  */
    TSinGen.delta_phi = 655;
    TSinGen.phase = 0;
    TSinGen.offset = 0;
    TSinGen.phi = 0;

    /* Block Amplitude                                                                                                */
    /* Value = 0.8                                                                                                    */
    TAmplitude.K = 26214;

    /* Block Frequency                                                                                                */
    /* Value = 0.02                                                                                                   */
    TFrequency.K = 655;

    /* Block LEDoff                                                                                                   */
    /* Value = 0.0                                                                                                    */
    TLED_off.K = 0;

    /* Block LEDon                                                                                                    */
    /* Value = 1.0                                                                                                    */
    TLED_on.K = 32767;

    /* Block Gain                                                                                                     */
    /* Gain = 2.0                                                                                                     */
    TGain.V = 16384;
    TGain.sfr = 13;

    /* Block Sin3Gen                                                                                                  */
    /* fmax = 100.0                                                                                                   */
    /* Offset = 0.0                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    TSin3Gen.delta_phi = 655;
    TSin3Gen.offset = 0;
    TSin3Gen.phi = 0;

    /* Block AutoSwitch2                                                                                              */
    /* Thresh_up = 0.0                                                                                                */
    /* Thresh_down = 0.0                                                                                              */
    TAutoSwitch2.Thresh_up = 0;
    TAutoSwitch2.Thresh_down = 0;
    TAutoSwitch2.Status = 0;

    /* Block AdaptivePT1                                                                                              */
    /* V = 1.0                                                                                                        */
    /* fmax = 200.0                                                                                                   */
    /* ts_fact = 1.0                                                                                                  */
    /* method = zoh                                                                                                   */
    TAdaptivePT1.w_scale = -4118;
    TAdaptivePT1.gain = 16384;
    TAdaptivePT1.sfr = 14;
    TAdaptivePT1.in_old = 0;

    /* Block Not                                                                                                      */


    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block fc                                                                                                       */

    /* Block AutoSwitch1                                                                                              */
    TAutoSwitch1.In1                 = &TSin3Gen.w;
    TAutoSwitch1.Switch              = &(Inports.VPot);
    TAutoSwitch1.In3                 = &TSinGen.u;

    /* Block Oscillator__Negation                                                                                     */
    TOscillator__Negation.In         = &TOscillator__C_1.Out;

    /* Block Oscillator__C_1                                                                                          */

    /* Block Oscillator__AutoSwitch                                                                                   */
    TOscillator__AutoSwitch.In1      = &TOscillator__Negation.Out;
    TOscillator__AutoSwitch.Switch   = &TOscillator__I.Out;
    TOscillator__AutoSwitch.In3      = &TOscillator__C_1.Out;

    /* Block Oscillator__I                                                                                            */
    TOscillator__I.In                = &TOscillator__Delay.Out;
    TOscillator__I.Init              = &TOscillator__C_init.Out;
    TOscillator__I.Enable            = &TOscillator__C_enable.Out;

    /* Block Oscillator__Delay                                                                                        */
    TOscillator__Delay.In            = &TOscillator__AutoSwitch.Out;

    /* Block Oscillator__C_init                                                                                       */

    /* Block Oscillator__C_enable                                                                                     */

    /* Block AutoSwitch                                                                                               */
    TAutoSwitch.In1                  = &TAutoSwitch2.Out;
    TAutoSwitch.Switch               = &(Inports.PB2);
    TAutoSwitch.In3                  = &TNot.Out;

    /* Block SinGen                                                                                                   */
    TSinGen.A                        = &TAmplitude.Out;
    TSinGen.f                        = &TGain.Out;

    /* Block Amplitude                                                                                                */

    /* Block Frequency                                                                                                */

    /* Block LEDoff                                                                                                   */

    /* Block LEDon                                                                                                    */

    /* Block Gain                                                                                                     */
    TGain.In                         = &TFrequency.Out;

    /* Block Sin3Gen                                                                                                  */
    TSin3Gen.A                       = &TAmplitude.Out;
    TSin3Gen.f                       = &TFrequency.Out;

    /* Block AutoSwitch2                                                                                              */
    TAutoSwitch2.In1                 = &TLED_off.Out;
    TAutoSwitch2.Switch              = &TAutoSwitch1.Out;
    TAutoSwitch2.In3                 = &TLED_on.Out;

    /* Block AdaptivePT1                                                                                              */
    TAdaptivePT1.In                  = &TSinGen.u;
    TAdaptivePT1.fc                  = &Tfc.Out;

    /* Block Not                                                                                                      */
    TNot.In                          = &TAutoSwitch2.Out;

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    Outports.pLED1                    = &TAutoSwitch2.Out;
    Outports.pLED3                    = &TOscillator__Delay.Out;
    Outports.pLED2                    = &Inports.PB1;
    Outports.pLED4                    = &TAutoSwitch.Out;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_FiP16_Init(&Tfc);
    AutoSwitch_FiP16_Init(&TAutoSwitch1);
    Negation_FiP16_Init(&TOscillator__Negation);
    Constant_FiP16_Init(&TOscillator__C_1);
    AutoSwitch_FiP16_Init(&TOscillator__AutoSwitch);
    I_FiP16_Init(&TOscillator__I);
    Delay_FiP16_Init(&TOscillator__Delay);
    Constant_FiP16_Init(&TOscillator__C_init);
    Constant_FiP8_Init(&TOscillator__C_enable);
    AutoSwitch_FiP16_Init(&TAutoSwitch);
    SinGen_FiP16_Init(&TSinGen);
    Constant_FiP16_Init(&TAmplitude);
    Constant_FiP16_Init(&TFrequency);
    Constant_FiP16_Init(&TLED_off);
    Constant_FiP16_Init(&TLED_on);
    Gain_FiP16_Init(&TGain);
    Sin3Gen_FiP16_Init(&TSin3Gen);
    AutoSwitch_FiP16_Init(&TAutoSwitch2);
    AdaptivePT1_FiP16_Init(&TAdaptivePT1);
    Not_FiP16_Init(&TNot);
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
    Gain_FiP16_Update(&TGain);
    Sin3Gen_FiP16_Update(&TSin3Gen);
    Negation_FiP16_Update(&TOscillator__Negation);
    SinGen_FiP16_Update(&TSinGen);
    AutoSwitch_FiP16_Update(&TAutoSwitch1);
    AdaptivePT1_FiP16_Update(&TAdaptivePT1);
    AutoSwitch_FiP16_Update(&TAutoSwitch2);
    Not_FiP16_Update(&TNot);
    I_FiP16_Update(&TOscillator__I);
    AutoSwitch_FiP16_Update(&TAutoSwitch);
    AutoSwitch_FiP16_Update(&TOscillator__AutoSwitch);
    Scope_Main_Update(&TScope);
}

