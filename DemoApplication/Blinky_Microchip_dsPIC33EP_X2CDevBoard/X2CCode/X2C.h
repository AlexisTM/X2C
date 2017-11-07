/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2016-02-18 12:39                                                                                            */

/* X2C-Version: local                                                                                                 */

#ifndef __X2C_H__
#define __X2C_H__

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
#include "Constant_FiP16.h"
#include "AutoSwitch_FiP16.h"
#include "Negation_FiP16.h"
#include "I_FiP16.h"
#include "Delay_FiP16.h"
#include "Constant_FiP8.h"
#include "SinGen_FiP16.h"
#include "Gain_FiP16.h"
#include "Sin3Gen_FiP16.h"
#include "AdaptivePT1_FiP16.h"
#include "Not_FiP16.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS CONSTANT_FIP16_FUNCTIONS , \
                  AUTOSWITCH_FIP16_FUNCTIONS , \
                  NEGATION_FIP16_FUNCTIONS , \
                  I_FIP16_FUNCTIONS , \
                  DELAY_FIP16_FUNCTIONS , \
                  CONSTANT_FIP8_FUNCTIONS , \
                  SINGEN_FIP16_FUNCTIONS , \
                  GAIN_FIP16_FUNCTIONS , \
                  SIN3GEN_FIP16_FUNCTIONS , \
                  ADAPTIVEPT1_FIP16_FUNCTIONS , \
                  NOT_FIP16_FUNCTIONS , \
                  SCOPE_MAIN_FUNCTIONS 

#define PARAMETER_TABLE { (uint16)1, &TAdaptivePT1 } , \
                        { (uint16)2, &TAmplitude } , \
                        { (uint16)3, &TAutoSwitch } , \
                        { (uint16)4, &TAutoSwitch1 } , \
                        { (uint16)5, &TAutoSwitch2 } , \
                        { (uint16)6, &TFrequency } , \
                        { (uint16)7, &TGain } , \
                        { (uint16)8, &TLED_off } , \
                        { (uint16)9, &TLED_on } , \
                        { (uint16)10, &TNot } , \
                        { (uint16)11, &TOscillator__AutoSwitch } , \
                        { (uint16)12, &TOscillator__C_1 } , \
                        { (uint16)13, &TOscillator__C_enable } , \
                        { (uint16)14, &TOscillator__C_init } , \
                        { (uint16)15, &TOscillator__Delay } , \
                        { (uint16)16, &TOscillator__I } , \
                        { (uint16)17, &TOscillator__Negation } , \
                        { (uint16)18, &TSin3Gen } , \
                        { (uint16)19, &TSinGen } , \
                        { (uint16)20, &Tfc } , \
                        { (uint16)21, &TScope } , \
                        { (uint16)22, &Inports.PB1 } , \
                        { (uint16)23, &Inports.PB2 } , \
                        { (uint16)24, &Inports.VPot } , \
                        { (uint16)25, &Inports.VTouch } , \
                        { (uint16)26, &Outports.pLED1 } , \
                        { (uint16)27, &Outports.pLED3 } , \
                        { (uint16)28, &Outports.pLED2 } , \
                        { (uint16)29, &Outports.pLED4 } 

/**********************************************************************************************************************/
/**     Typdefs                                                                                                      **/
/**********************************************************************************************************************/

/* Inport structure                                                                                                   */
typedef struct 
{
    int16 PB1;
    int16 VPot;
    int16 PB2;
    int16 VTouch;
} TInports;

/* Outport structure                                                                                                  */
typedef struct 
{
    int16* pLED1;
    int16* pLED3;
    int16* pLED2;
    int16* pLED4;
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
