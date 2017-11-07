/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: DemoApplication                                                                                             */
/* Date:  2016-01-29 12:40                                                                                            */

#ifndef __X2C_H__
#define __X2C_H__

/**********************************************************************************************************************/
/**     Includes                                                                                                     **/
/**********************************************************************************************************************/
#include "Constant_FiP16.h"
#include "AutoSwitch_FiP16.h"
#include "Sin3Gen_FiP16.h"
#include "SinGen_FiP16.h"
#include "Scope_Main.h"
#include "CommonFcts.h"

/**********************************************************************************************************************/
/**     Defines                                                                                                      **/
/**********************************************************************************************************************/
#define FUNCTIONS CONSTANT_FIP16_FUNCTIONS , \
                  AUTOSWITCH_FIP16_FUNCTIONS , \
                  SIN3GEN_FIP16_FUNCTIONS , \
                  SINGEN_FIP16_FUNCTIONS , \
                  SCOPE_MAIN_FUNCTIONS 

#define PARAMETER_TABLE { (uint16)1, &TAmplitude } , \
                        { (uint16)2, &TAutoSwitch } , \
                        { (uint16)3, &TFrequency } , \
                        { (uint16)4, &TLED_off } , \
                        { (uint16)5, &TLED_on } , \
                        { (uint16)6, &TSin3Gen } , \
                        { (uint16)7, &TSinGen } , \
                        { (uint16)8, &TScope } , \
                        { (uint16)9, &Inports.User_Button } , \
                        { (uint16)10, &Outports.pLED_blue } , \
                        { (uint16)11, &Outports.pLED_green } 

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
    int16* pLED_blue;
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
