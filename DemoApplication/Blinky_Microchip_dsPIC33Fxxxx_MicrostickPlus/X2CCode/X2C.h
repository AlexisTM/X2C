/**
 * @file
 * @brief Generated model file.

 * Date:  2016-09-01 15:04
 * X2C-Version: 1012
 */
/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2016-09-01 15:04                                                                                            */

/* X2C-Version: 1012                                                                                                  */

#ifndef __X2C_H__
#define __X2C_H__

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
#include "Constant_FiP16.h"
#include "AutoSwitch_FiP16.h"
#include "Sin3Gen_FiP16.h"
#include "SinGen_FiP16.h"
#include "I_FiP16.h"
#include "Constant_FiP8.h"
#include "Negation_FiP16.h"
#include "Delay_FiP16.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS CONSTANT_FIP16_FUNCTIONS , \
                  AUTOSWITCH_FIP16_FUNCTIONS , \
                  SIN3GEN_FIP16_FUNCTIONS , \
                  SINGEN_FIP16_FUNCTIONS , \
                  I_FIP16_FUNCTIONS , \
                  CONSTANT_FIP8_FUNCTIONS , \
                  NEGATION_FIP16_FUNCTIONS , \
                  DELAY_FIP16_FUNCTIONS , \
                  SCOPE_MAIN_FUNCTIONS 

#define PARAMETER_TABLE { (uint16)1, &TAmplitude } , \
                        { (uint16)2, &TAutoSwitch } , \
                        { (uint16)3, &TAutoSwitch1 } , \
                        { (uint16)4, &TFrequency } , \
                        { (uint16)5, &TLED_off } , \
                        { (uint16)6, &TLED_on } , \
                        { (uint16)7, &TOscillator__AutoSwitch } , \
                        { (uint16)8, &TOscillator__Constant } , \
                        { (uint16)9, &TOscillator__Delay } , \
                        { (uint16)10, &TOscillator__Enable } , \
                        { (uint16)11, &TOscillator__Init } , \
                        { (uint16)12, &TOscillator__Integrator } , \
                        { (uint16)13, &TOscillator__Negation } , \
                        { (uint16)14, &TSin3Gen } , \
                        { (uint16)15, &TSinGen } , \
                        { (uint16)16, &TScope } , \
                        { (uint16)17, &Inports.Encoder } , \
                        { (uint16)18, &Inports.Potentiometer } , \
                        { (uint16)19, &Inports.Switch1 } , \
                        { (uint16)20, &Outports.pLED_red1 } , \
                        { (uint16)21, &Outports.pLED_red2 } , \
                        { (uint16)22, &Outports.pLED_blue2 } , \
                        { (uint16)23, &Outports.pLED_blue1 } , \
                        { (uint16)24, &Outports.pPiezo } 

/**********************************************************************************************************************/
/**     Typdefs                                                                                                      **/
/**********************************************************************************************************************/

/* Inport structure                                                                                                   */
typedef struct 
{
    int16 Switch1;
    int16 Potentiometer;
    int16 Encoder;
} TInports;

/* Outport structure                                                                                                  */
typedef struct 
{
    int16* pLED_red1;
    int16* pLED_red2;
    int16* pLED_blue2;
    int16* pLED_blue1;
    int16* pPiezo;
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
