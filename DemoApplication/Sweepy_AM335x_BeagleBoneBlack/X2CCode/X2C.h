/**
 * @file
 * @brief Generated model file.

 * Date:  2017-01-16 16:31
 * X2C-Version: 1072
 */
/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2017-01-16 16:31                                                                                            */

/* X2C-Version: 1072                                                                                                  */

#ifndef __X2C_H__
#define __X2C_H__

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
#include "Constant_Float32.h"
#include "AutoSwitch_Float32.h"
#include "Constant_FiP8.h"
#include "Sin3Gen_Float32.h"
#include "Negation_Float32.h"
#include "LoopBreaker_Float32.h"
#include "I_Float32.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS CONSTANT_FLOAT32_FUNCTIONS , \
                  AUTOSWITCH_FLOAT32_FUNCTIONS , \
                  CONSTANT_FIP8_FUNCTIONS , \
                  SIN3GEN_FLOAT32_FUNCTIONS , \
                  NEGATION_FLOAT32_FUNCTIONS , \
                  LOOPBREAKER_FLOAT32_FUNCTIONS , \
                  I_FLOAT32_FUNCTIONS , \
                  SCOPE_MAIN_FUNCTIONS 

#define PARAMETER_TABLE { (uint16)1, &TAmplitude } , \
                        { (uint16)2, &TAutoSwitch1 } , \
                        { (uint16)3, &TAutoSwitch2 } , \
                        { (uint16)4, &TAutoSwitch3 } , \
                        { (uint16)5, &TDigOut1 } , \
                        { (uint16)6, &TDigOut2 } , \
                        { (uint16)7, &TDigOut3 } , \
                        { (uint16)8, &TDigOut4 } , \
                        { (uint16)9, &TLED_off } , \
                        { (uint16)10, &TLED_on } , \
                        { (uint16)11, &TLED_on_off } , \
                        { (uint16)12, &TSin3Gen } , \
                        { (uint16)13, &TStart_Stop } , \
                        { (uint16)14, &TTriangleGenerator__AutoSwitch0 } , \
                        { (uint16)15, &TTriangleGenerator__I } , \
                        { (uint16)16, &TTriangleGenerator__Init } , \
                        { (uint16)17, &TTriangleGenerator__LoopBreaker } , \
                        { (uint16)18, &TTriangleGenerator__Negation } , \
                        { (uint16)19, &TTriangleGenerator__Slope } , \
                        { (uint16)20, &TScope } , \
                        { (uint16)21, &Inports.P8_10 } , \
                        { (uint16)22, &Inports.P8_12 } , \
                        { (uint16)23, &Inports.P8_16 } , \
                        { (uint16)24, &Inports.P8_8 } , \
                        { (uint16)25, &Inports.P9_33 } , \
                        { (uint16)26, &Inports.P9_35 } , \
                        { (uint16)27, &Inports.P9_36 } , \
                        { (uint16)28, &Inports.P9_37 } , \
                        { (uint16)29, &Inports.P9_38 } , \
                        { (uint16)30, &Inports.P9_39 } , \
                        { (uint16)31, &Inports.P9_40 } , \
                        { (uint16)32, &Outports.pP9_21_22 } , \
                        { (uint16)33, &Outports.pP9_14_16 } , \
                        { (uint16)34, &Outports.pP8_13_19 } , \
                        { (uint16)35, &Outports.pP8_7 } , \
                        { (uint16)36, &Outports.pP8_11 } , \
                        { (uint16)37, &Outports.pP8_9 } , \
                        { (uint16)38, &Outports.pP8_15 } , \
                        { (uint16)39, &Outports.pLED1 } , \
                        { (uint16)40, &Outports.pLED3 } , \
                        { (uint16)41, &Outports.pLED0 } , \
                        { (uint16)42, &Outports.pLED2 } 

/**********************************************************************************************************************/
/**     Typdefs                                                                                                      **/
/**********************************************************************************************************************/

/* Inport structure                                                                                                   */
typedef struct 
{
    float32 P8_8;
    float32 P8_12;
    float32 P8_10;
    float32 P8_16;
    float32 P9_33;
    float32 P9_35;
    float32 P9_37;
    float32 P9_39;
    float32 P9_36;
    float32 P9_38;
    float32 P9_40;
} TInports;

/* Outport structure                                                                                                  */
typedef struct 
{
    float32* pP9_21_22;
    float32* pP9_14_16;
    float32* pP8_13_19;
    float32* pP8_7;
    float32* pP8_11;
    float32* pP8_9;
    float32* pP8_15;
    float32* pLED1;
    float32* pLED3;
    float32* pLED0;
    float32* pLED2;
} TOutports;

/**********************************************************************************************************************/
/**     Externals                                                                                                    **/
/**********************************************************************************************************************/
extern TInports Inports;
extern TOutports Outports;
extern const tBlockFunctions blockFunctionTable[];
extern const tParameterTable parameterIdTable[];


/**********************************************************************************************************************/
/**     Prototypes                                                                                                   **/
/**********************************************************************************************************************/
void X2C_Init(void);
void X2C_Update(void);
void X2C_Update_1(void);


#endif
