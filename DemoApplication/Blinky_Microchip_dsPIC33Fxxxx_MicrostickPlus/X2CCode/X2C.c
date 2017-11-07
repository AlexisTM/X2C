/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2016-09-01 15:04                                                                                            */

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
CONSTANT_FIP16                TAmplitude;
CONSTANT_FIP16                TFrequency;
AUTOSWITCH_FIP16              TAutoSwitch;
CONSTANT_FIP16                TLED_off;
CONSTANT_FIP16                TLED_on;
SIN3GEN_FIP16                 TSin3Gen;
SINGEN_FIP16                  TSinGen;
AUTOSWITCH_FIP16              TAutoSwitch1;
AUTOSWITCH_FIP16              TOscillator__AutoSwitch;
I_FIP16                       TOscillator__Integrator;
CONSTANT_FIP8                 TOscillator__Enable;
NEGATION_FIP16                TOscillator__Negation;
CONSTANT_FIP16                TOscillator__Constant;
DELAY_FIP16                   TOscillator__Delay;
CONSTANT_FIP16                TOscillator__Init;
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

    /* Block Frequency                                                                                                */
    /* Value = 0.0080                                                                                                 */
    TFrequency.K = 262;

    /* Block AutoSwitch                                                                                               */
    /* Thresh_up = 0.6                                                                                                */
    /* Thresh_down = 0.4                                                                                              */
    TAutoSwitch.Thresh_up = 19661;
    TAutoSwitch.Thresh_down = 13107;
    TAutoSwitch.Status = 0;

    /* Block LEDoff                                                                                                   */
    /* Value = 0.0                                                                                                    */
    TLED_off.K = 0;

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

    /* Block SinGen                                                                                                   */
    /* fmax = 1000.0                                                                                                  */
    /* Offset = 0.0                                                                                                   */
    /* Phase = 0.0                                                                                                    */
    /* ts_fact = 1.0                                                                                                  */
    TSinGen.delta_phi = 6554;
    TSinGen.phase = 0;
    TSinGen.offset = 0;
    TSinGen.phi = 0;

    /* Block AutoSwitch1                                                                                              */
    /* Thresh_up = 0.0                                                                                                */
    /* Thresh_down = 0.0                                                                                              */
    TAutoSwitch1.Thresh_up = 0;
    TAutoSwitch1.Thresh_down = 0;
    TAutoSwitch1.Status = 0;

    /* Block Oscillator__AutoSwitch                                                                                   */
    /* Thresh_up = 0.5                                                                                                */
    /* Thresh_down = -0.5                                                                                             */
    TOscillator__AutoSwitch.Thresh_up = 16384;
    TOscillator__AutoSwitch.Thresh_down = -16384;
    TOscillator__AutoSwitch.Status = 0;

    /* Block Oscillator__Integrator                                                                                   */
    /* Ki = 50.0                                                                                                      */
    /* ts_fact = 1.0                                                                                                  */
    TOscillator__Integrator.b0 = 164;
    TOscillator__Integrator.sfr = 15;
    TOscillator__Integrator.i_old = 0;
    TOscillator__Integrator.enable_old = 0;

    /* Block Oscillator__Enable                                                                                       */
    /* Value = 1.0                                                                                                    */
    TOscillator__Enable.K = 127;

    /* Block Oscillator__Negation                                                                                     */

    /* Block Oscillator__Constant                                                                                     */
    /* Value = 1.0                                                                                                    */
    TOscillator__Constant.K = 32767;

    /* Block Oscillator__Delay                                                                                        */
    /* ts_fact = 1.0                                                                                                  */
    TOscillator__Delay.In_old = 0;

    /* Block Oscillator__Init                                                                                         */
    /* Value = 0.0                                                                                                    */
    TOscillator__Init.K = 0;


    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block Amplitude                                                                                                */

    /* Block Frequency                                                                                                */

    /* Block AutoSwitch                                                                                               */
    TAutoSwitch.In1                  = &TLED_off.Out;
    TAutoSwitch.Switch               = &(Inports.Potentiometer);
    TAutoSwitch.In3                  = &TLED_on.Out;

    /* Block LEDoff                                                                                                   */

    /* Block LEDon                                                                                                    */

    /* Block Sin3Gen                                                                                                  */
    TSin3Gen.A                       = &TAmplitude.Out;
    TSin3Gen.f                       = &TFrequency.Out;

    /* Block SinGen                                                                                                   */
    TSinGen.A                        = &TAmplitude.Out;
    TSinGen.f                        = &TFrequency.Out;

    /* Block AutoSwitch1                                                                                              */
    TAutoSwitch1.In1                 = &TLED_off.Out;
    TAutoSwitch1.Switch              = &TSinGen.u;
    TAutoSwitch1.In3                 = &TLED_on.Out;

    /* Block Oscillator__AutoSwitch                                                                                   */
    TOscillator__AutoSwitch.In1      = &TOscillator__Negation.Out;
    TOscillator__AutoSwitch.Switch   = &TOscillator__Integrator.Out;
    TOscillator__AutoSwitch.In3      = &TOscillator__Constant.Out;

    /* Block Oscillator__Integrator                                                                                   */
    TOscillator__Integrator.In       = &TOscillator__Delay.Out;
    TOscillator__Integrator.Init     = &TOscillator__Init.Out;
    TOscillator__Integrator.Enable   = &TOscillator__Enable.Out;

    /* Block Oscillator__Enable                                                                                       */

    /* Block Oscillator__Negation                                                                                     */
    TOscillator__Negation.In         = &TOscillator__Constant.Out;

    /* Block Oscillator__Constant                                                                                     */

    /* Block Oscillator__Delay                                                                                        */
    TOscillator__Delay.In            = &TOscillator__AutoSwitch.Out;

    /* Block Oscillator__Init                                                                                         */

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    Outports.pLED_red1                = &TAutoSwitch1.Out;
    Outports.pLED_red2                = &Inports.Switch1;
    Outports.pLED_blue2               = &TOscillator__Delay.Out;
    Outports.pLED_blue1               = &TAutoSwitch.Out;
    Outports.pPiezo                   = &Inports.Encoder;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_FiP16_Init(&TAmplitude);
    Constant_FiP16_Init(&TFrequency);
    AutoSwitch_FiP16_Init(&TAutoSwitch);
    Constant_FiP16_Init(&TLED_off);
    Constant_FiP16_Init(&TLED_on);
    Sin3Gen_FiP16_Init(&TSin3Gen);
    SinGen_FiP16_Init(&TSinGen);
    AutoSwitch_FiP16_Init(&TAutoSwitch1);
    AutoSwitch_FiP16_Init(&TOscillator__AutoSwitch);
    I_FiP16_Init(&TOscillator__Integrator);
    Constant_FiP8_Init(&TOscillator__Enable);
    Negation_FiP16_Init(&TOscillator__Negation);
    Constant_FiP16_Init(&TOscillator__Constant);
    Delay_FiP16_Init(&TOscillator__Delay);
    Constant_FiP16_Init(&TOscillator__Init);
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
    Negation_FiP16_Update(&TOscillator__Negation);
    SinGen_FiP16_Update(&TSinGen);
    AutoSwitch_FiP16_Update(&TAutoSwitch);
    AutoSwitch_FiP16_Update(&TAutoSwitch1);
    Sin3Gen_FiP16_Update(&TSin3Gen);
    I_FiP16_Update(&TOscillator__Integrator);
    AutoSwitch_FiP16_Update(&TOscillator__AutoSwitch);
    Scope_Main_Update(&TScope);
}

