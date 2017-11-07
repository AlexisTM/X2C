/**
 * @file
 * @brief Generated model file.

 * Date:  2016-12-23 13:23
 * X2C-Version: 1068
 */
/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2016-12-23 13:23                                                                                            */

/* X2C-Version: 1068                                                                                                  */

#ifndef __X2C_H__
#define __X2C_H__

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
#include "AutoSwitch_FiP16.h"
#include "I_FiP16.h"
#include "Negation_FiP16.h"
#include "Delay_FiP16.h"
#include "Constant_FiP16.h"
#include "Constant_FiP8.h"
#include "Sin3Gen_FiP16.h"
#include "SinGen_FiP16.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS AUTOSWITCH_FIP16_FUNCTIONS , \
                  I_FIP16_FUNCTIONS , \
                  NEGATION_FIP16_FUNCTIONS , \
                  DELAY_FIP16_FUNCTIONS , \
                  CONSTANT_FIP16_FUNCTIONS , \
                  CONSTANT_FIP8_FUNCTIONS , \
                  SIN3GEN_FIP16_FUNCTIONS , \
                  SINGEN_FIP16_FUNCTIONS , \
                  SCOPE_MAIN_FUNCTIONS 

#define PARAMETER_TABLE { (uint16)1, &TAmplitude } , \
                        { (uint16)2, &TAutoSwitch } , \
                        { (uint16)3, &TAutoSwitch1 } , \
                        { (uint16)4, &TFrequency } , \
                        { (uint16)5, &TLED_off } , \
                        { (uint16)6, &TLED_on } , \
                        { (uint16)7, &TLED_on_off } , \
                        { (uint16)8, &TOscillator__AutoSwitch } , \
                        { (uint16)9, &TOscillator__Constant } , \
                        { (uint16)10, &TOscillator__Delay } , \
                        { (uint16)11, &TOscillator__Enable } , \
                        { (uint16)12, &TOscillator__Init } , \
                        { (uint16)13, &TOscillator__Integrator } , \
                        { (uint16)14, &TOscillator__Negation } , \
                        { (uint16)15, &TSin3Gen } , \
                        { (uint16)16, &TSinGen } , \
                        { (uint16)17, &TScope } , \
                        { (uint16)18, &Outports.pLED2 } , \
                        { (uint16)19, &Outports.pLED1 } , \
                        { (uint16)20, &Outports.pLED3 } , \
                        { (uint16)21, &Outports.pLED0 } 

/**********************************************************************************************************************/
/**     Typdefs                                                                                                      **/
/**********************************************************************************************************************/

/* No Inports in Model                                                                                                */

/* Outport structure                                                                                                  */
typedef struct 
{
    int16* pLED2;
    int16* pLED1;
    int16* pLED3;
    int16* pLED0;
} TOutports;

/**********************************************************************************************************************/
/**     Externals                                                                                                    **/
/**********************************************************************************************************************/
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
