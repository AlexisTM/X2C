/**
 * @file
 * @brief Generated model file.

 * Date:  2017-02-27 14:43
 * X2C-Version: 1105
 */
/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2017-02-27 14:43                                                                                            */

/* X2C-Version: 1105                                                                                                  */

#ifndef __X2C_H__
#define __X2C_H__

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
#include "Constant_FiP16.h"
#include "AutoSwitch_FiP16.h"
#include "Gain_FiP16.h"
#include "Sin3Gen_FiP16.h"
#include "SinGen_FiP16.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS CONSTANT_FIP16_FUNCTIONS , \
                  AUTOSWITCH_FIP16_FUNCTIONS , \
                  GAIN_FIP16_FUNCTIONS , \
                  SIN3GEN_FIP16_FUNCTIONS , \
                  SINGEN_FIP16_FUNCTIONS , \
                  SCOPE_MAIN_FUNCTIONS 

#define PARAMETER_TABLE { (uint16)1, &TAmplitude } , \
                        { (uint16)2, &TAutoSwitch } , \
                        { (uint16)3, &TAutoSwitch1 } , \
                        { (uint16)4, &TFrequency } , \
                        { (uint16)5, &TGain } , \
                        { (uint16)6, &TLED_off } , \
                        { (uint16)7, &TLED_on } , \
                        { (uint16)8, &TSin3Gen } , \
                        { (uint16)9, &TSinGen } , \
                        { (uint16)10, &TScope } , \
                        { (uint16)11, &Inports.User_Button } , \
                        { (uint16)12, &Outports.pLED_green } 

/**********************************************************************************************************************/
/**     Typdefs                                                                                                      **/
/**********************************************************************************************************************/

/* Inport structure                                                                                                   */
typedef struct 
{
    int16 User_Button;
} TInports;

/* Outport structure                                                                                                  */
typedef struct 
{
    int16* pLED_green;
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
