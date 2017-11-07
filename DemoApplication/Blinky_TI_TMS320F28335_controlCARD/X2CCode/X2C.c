/* This file is part of X2C. http://www.mechatronic-simulation.org/                                                   */

/* Model: Km63_Simulation                                                                                             */
/* Date:  2016-12-12 17:43                                                                                            */

/* X2C-Version: 1058                                                                                                  */

#include "FlashTable.h"
#include "RamTable.h"
#include "X2C.h"

/*                                                       Inports                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/

/*                                                      Outports                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************/
/**                                              Global Variables Block                                              **/
/**********************************************************************************************************************/
CONSTANT_FIP8                 TEnable;
CONSTANT_FIP16                TIn;
CONSTANT_FIP16                TIn1;
CONSTANT_FIP16                TIn2;
CONSTANT_FIP16                TIn3;
CONSTANT_FIP16                TInit;
KM6X3_FIP16                   TKm6x3;
UI_FIP16                      TuI;
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

    /* Block Enable                                                                                                   */
    /* Value = 1.0                                                                                                    */
    TEnable.K = 127;

    /* Block In                                                                                                       */
    /* Value = 1.0                                                                                                    */
    TIn.K = 32767;

    /* Block In1                                                                                                      */
    /* Value = 0.1                                                                                                    */
    TIn1.K = 3277;

    /* Block In2                                                                                                      */
    /* Value = 0.2                                                                                                    */
    TIn2.K = 6554;

    /* Block In3                                                                                                      */
    /* Value = 0.3                                                                                                    */
    TIn3.K = 9830;

    /* Block Init                                                                                                     */
    /* Value = 0.0                                                                                                    */
    TInit.K = 0;

    /* Block Km6x3                                                                                                    */
    /* Km = [real 1x2304 row vector]                                                                                  */
    TKm6x3.Table = &FlashTable_int16[0];

    /* Block uI                                                                                                       */
    /* Ki = 100.0                                                                                                     */
    /* ts_fact = 1.0                                                                                                  */
    TuI.b0 = 328;
    TuI.sfr = 15;
    TuI.i_old = 0;
    TuI.enable_old = 0;


    /******************************************************************************************************************/
    /**                                               Link Block Inputs                                              **/
    /******************************************************************************************************************/

    /* Block Enable                                                                                                   */

    /* Block In                                                                                                       */

    /* Block In1                                                                                                      */

    /* Block In2                                                                                                      */

    /* Block In3                                                                                                      */

    /* Block Init                                                                                                     */

    /* Block Km6x3                                                                                                    */
    TKm6x3.Fx                        = &TIn1.Out;
    TKm6x3.Fy                        = &TIn2.Out;
    TKm6x3.T                         = &TIn3.Out;
    TKm6x3.phi                       = &TuI.Out;

    /* Block uI                                                                                                       */
    TuI.In                           = &TIn.Out;
    TuI.Init                         = &TInit.Out;
    TuI.Enable                       = &TEnable.Out;

    /******************************************************************************************************************/
    /**                                                 Link Outports                                                **/
    /******************************************************************************************************************/

    /******************************************************************************************************************/
    /**                                           Run Block Init Functions                                           **/
    /******************************************************************************************************************/
    Constant_FiP8_Init(&TEnable);
    Constant_FiP16_Init(&TIn);
    Constant_FiP16_Init(&TIn1);
    Constant_FiP16_Init(&TIn2);
    Constant_FiP16_Init(&TIn3);
    Constant_FiP16_Init(&TInit);
    Km6x3_FiP16_Init(&TKm6x3);
    uI_FiP16_Init(&TuI);
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
    uI_FiP16_Update(&TuI);
    Km6x3_FiP16_Update(&TKm6x3);
    Scope_Main_Update(&TScope);
}

