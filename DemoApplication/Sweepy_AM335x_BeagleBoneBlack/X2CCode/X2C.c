/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2017-01-16 16:31                                                                                            */

/* X2C-Version: 1072                                                                                                  */

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
CONSTANT_FLOAT32              TDigOut4;
AUTOSWITCH_FLOAT32            TAutoSwitch2;
AUTOSWITCH_FLOAT32            TAutoSwitch1;
CONSTANT_FLOAT32              TDigOut2;
CONSTANT_FLOAT32              TDigOut3;
AUTOSWITCH_FLOAT32            TAutoSwitch3;
CONSTANT_FLOAT32              TLED_on_off;
CONSTANT_FIP8                 TStart_Stop;
SIN3GEN_FLOAT32               TSin3Gen;
CONSTANT_FLOAT32              TAmplitude;
NEGATION_FLOAT32              TTriangleGenerator__Negation;
LOOPBREAKER_FLOAT32           TTriangleGenerator__LoopBreaker;
CONSTANT_FLOAT32              TTriangleGenerator__Init;
AUTOSWITCH_FLOAT32            TTriangleGenerator__AutoSwitch0;
CONSTANT_FLOAT32              TTriangleGenerator__Slope;
I_FLOAT32                     TTriangleGenerator__I;
CONSTANT_FLOAT32              TLED_off;
CONSTANT_FLOAT32              TLED_on;
CONSTANT_FLOAT32              TDigOut1;
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

    /* Block DigOut4                                                                                                  */
    /* Value = 0.0                                                                                                    */
    TDigOut4.K = 0;

    /* Block AutoSwitch2                                                                                              */
    /* Thresh_up = 50.0                                                                                               */
    /* Thresh_down = 50.0                                                                                             */
    TAutoSwitch2.Thresh_up = 50;
    TAutoSwitch2.Thresh_down = 50;
    TAutoSwitch2.Status = 0;

    /* Block AutoSwitch1                                                                                              */
    /* Thresh_up = 50.0                                                                                               */
    /* Thresh_down = 50.0                                                                                             */
    TAutoSwitch1.Thresh_up = 50;
    TAutoSwitch1.Thresh_down = 50;
    TAutoSwitch1.Status = 0;

    /* Block DigOut2                                                                                                  */
    /* Value = 0.0                                                                                                    */
    TDigOut2.K = 0;

    /* Block DigOut3                                                                                                  */
    /* Value = 0.0                                                                                                    */
    TDigOut3.K = 0;

    /* Block AutoSwitch3                                                                                              */
    /* Thresh_up = 50.0                                                                                               */
    /* Thresh_down = 50.0                                                                                             */
    TAutoSwitch3.Thresh_up = 50;
    TAutoSwitch3.Thresh_down = 50;
    TAutoSwitch3.Status = 0;

    /* Block LED_on_off                                                                                               */
    /* Value = 0.0                                                                                                    */
    TLED_on_off.K = 0;

    /* Block Start_Stop                                                                                               */
    /* Value = 1.0                                                                                                    */
    TStart_Stop.K = 127;

    /* Block Sin3Gen                                                                                                  */
    /* fmax = 1000.0                                                                                                  */
    /* Offset = 50.0                                                                                                  */
    /* ts_fact = 1.0                                                                                                  */
    TSin3Gen.delta_phi = .000628318530718;
    TSin3Gen.offset = 50;
    TSin3Gen.phi = 0;

    /* Block Amplitude                                                                                                */
    /* Value = 50.0                                                                                                   */
    TAmplitude.K = 50;

    /* Block TriangleGenerator__Negation                                                                              */

    /* Block TriangleGenerator__LoopBreaker                                                                           */

    /* Block TriangleGenerator__Init                                                                                  */
    /* Value = 0.0                                                                                                    */
    TTriangleGenerator__Init.K = 0;

    /* Block TriangleGenerator__AutoSwitch0                                                                           */
    /* Thresh_up = 500.0                                                                                              */
    /* Thresh_down = 0.0                                                                                              */
    TTriangleGenerator__AutoSwitch0.Thresh_up = 500;
    TTriangleGenerator__AutoSwitch0.Thresh_down = 0;
    TTriangleGenerator__AutoSwitch0.Status = 0;

    /* Block TriangleGenerator__Slope                                                                                 */
    /* Value = 10.0                                                                                                   */
    TTriangleGenerator__Slope.K = 10;

    /* Block TriangleGenerator__I                                                                                     */
    /* Ki = 1.0                                                                                                       */
    /* ts_fact = 1.0                                                                                                  */
    TTriangleGenerator__I.b0 = .0001;
    TTriangleGenerator__I.i_old = 0;
    TTriangleGenerator__I.enable_old = 0;

    /* Block LEDoff                                                                                                   */
    /* Value = 0.0                                                                                                    */
    TLED_off.K = 0;

    /* Block LEDon                                                                                                    */
    /* Value = 1.0                                                                                                    */
    TLED_on.K = 1;

    /* Block DigOut1                                                                                                  */
    /* Value = 0.0                                                                                                    */
    TDigOut1.K = 0;


    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block DigOut4                                                                                                  */

    /* Block AutoSwitch2                                                                                              */
    TAutoSwitch2.In1                 = &TLED_off.Out;
    TAutoSwitch2.Switch              = &TSin3Gen.v;
    TAutoSwitch2.In3                 = &TLED_on.Out;

    /* Block AutoSwitch1                                                                                              */
    TAutoSwitch1.In1                 = &TLED_off.Out;
    TAutoSwitch1.Switch              = &TSin3Gen.u;
    TAutoSwitch1.In3                 = &TLED_on.Out;

    /* Block DigOut2                                                                                                  */

    /* Block DigOut3                                                                                                  */

    /* Block AutoSwitch3                                                                                              */
    TAutoSwitch3.In1                 = &TLED_off.Out;
    TAutoSwitch3.Switch              = &TSin3Gen.w;
    TAutoSwitch3.In3                 = &TLED_on.Out;

    /* Block LED_on_off                                                                                               */

    /* Block Start_Stop                                                                                               */

    /* Block Sin3Gen                                                                                                  */
    TSin3Gen.A                       = &TAmplitude.Out;
    TSin3Gen.f                       = &TTriangleGenerator__I.Out;

    /* Block Amplitude                                                                                                */

    /* Block TriangleGenerator__Negation                                                                              */
    TTriangleGenerator__Negation.In  = &TTriangleGenerator__Slope.Out;

    /* Block TriangleGenerator__LoopBreaker                                                                           */
    TTriangleGenerator__LoopBreaker.In = &TTriangleGenerator__I.Out;

    /* Block TriangleGenerator__Init                                                                                  */

    /* Block TriangleGenerator__AutoSwitch0                                                                           */
    TTriangleGenerator__AutoSwitch0.In1 = &TTriangleGenerator__Negation.Out;
    TTriangleGenerator__AutoSwitch0.Switch = &TTriangleGenerator__LoopBreaker.Out;
    TTriangleGenerator__AutoSwitch0.In3 = &TTriangleGenerator__Slope.Out;

    /* Block TriangleGenerator__Slope                                                                                 */

    /* Block TriangleGenerator__I                                                                                     */
    TTriangleGenerator__I.In         = &TTriangleGenerator__AutoSwitch0.Out;
    TTriangleGenerator__I.Init       = &TTriangleGenerator__Init.Out;
    TTriangleGenerator__I.Enable     = &TStart_Stop.Out;

    /* Block LEDoff                                                                                                   */

    /* Block LEDon                                                                                                    */

    /* Block DigOut1                                                                                                  */

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/
    Outports.pP9_21_22                = &TSin3Gen.u;
    Outports.pP9_14_16                = &TSin3Gen.v;
    Outports.pP8_13_19                = &TSin3Gen.w;
    Outports.pP8_7                    = &TDigOut1.Out;
    Outports.pP8_11                   = &TDigOut3.Out;
    Outports.pP8_9                    = &TDigOut2.Out;
    Outports.pP8_15                   = &TDigOut4.Out;
    Outports.pLED1                    = &TAutoSwitch1.Out;
    Outports.pLED3                    = &TAutoSwitch3.Out;
    Outports.pLED0                    = &TLED_on_off.Out;
    Outports.pLED2                    = &TAutoSwitch2.Out;

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_Float32_Init(&TDigOut4);
    AutoSwitch_Float32_Init(&TAutoSwitch2);
    AutoSwitch_Float32_Init(&TAutoSwitch1);
    Constant_Float32_Init(&TDigOut2);
    Constant_Float32_Init(&TDigOut3);
    AutoSwitch_Float32_Init(&TAutoSwitch3);
    Constant_Float32_Init(&TLED_on_off);
    Constant_FiP8_Init(&TStart_Stop);
    Sin3Gen_Float32_Init(&TSin3Gen);
    Constant_Float32_Init(&TAmplitude);
    Negation_Float32_Init(&TTriangleGenerator__Negation);
    LoopBreaker_Float32_Init(&TTriangleGenerator__LoopBreaker);
    Constant_Float32_Init(&TTriangleGenerator__Init);
    AutoSwitch_Float32_Init(&TTriangleGenerator__AutoSwitch0);
    Constant_Float32_Init(&TTriangleGenerator__Slope);
    I_Float32_Init(&TTriangleGenerator__I);
    Constant_Float32_Init(&TLED_off);
    Constant_Float32_Init(&TLED_on);
    Constant_Float32_Init(&TDigOut1);
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
    LoopBreaker_Float32_Update(&TTriangleGenerator__LoopBreaker);
    Negation_Float32_Update(&TTriangleGenerator__Negation);
    AutoSwitch_Float32_Update(&TTriangleGenerator__AutoSwitch0);
    I_Float32_Update(&TTriangleGenerator__I);
    Sin3Gen_Float32_Update(&TSin3Gen);
    AutoSwitch_Float32_Update(&TAutoSwitch1);
    AutoSwitch_Float32_Update(&TAutoSwitch2);
    AutoSwitch_Float32_Update(&TAutoSwitch3);
    Scope_Main_Update(&TScope);
}

