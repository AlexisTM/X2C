// This file was generated by createCFunction.sci on 03-03-2017 01:18

// Computational function for X2C block TDSystemO2

#define SCILAB_SIM_FILE /* mark this file as Scilab simulation file */

/* include Scicos / Xcos headers */
#include <scicos.h>
#include <scicos_block4.h>
#include <scicos_malloc.h>
#include <scicos_free.h>
#include <Simulation_PortConversion.h>
//#define DEBUG // uncomment to enable debugging
#ifdef DEBUG
    #include <stdio.h>
#endif

/* include block implementation */
#include <TDSystemO2_Float32.h>
#include <TDSystemO2_Float32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_TDSystemO2_Float32_C(scicos_block* block, scicos_flag flag);
static void x2c_TDSystemO2_Float32_C__OutputUpdate(scicos_block* block);
static void x2c_TDSystemO2_Float32_C__StateUpdate(scicos_block* block);
static void x2c_TDSystemO2_Float32_C__Initialization(scicos_block* block);
static void x2c_TDSystemO2_Float32_C__Ending(scicos_block* block);


void x2c_TDSystemO2_Float32_C(scicos_block* block, scicos_flag flag) {
    /*
     * This function will be called by Xcos
     */
    switch (flag) {
        case DerivativeState:  /* 0 */
        {
            break;
        }
        case OutputUpdate:     /* 1 */
        {
            x2c_TDSystemO2_Float32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_TDSystemO2_Float32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_TDSystemO2_Float32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_TDSystemO2_Float32_C__Ending(block);
            break;
        }
        case ReInitialization: /* 6 */
        {
            break;
        }
        case ContinousPropertiesUpdate: /* 7 */
        {
            break;
        }
        case ZeroCrossing:     /* 9 */
        {
           break;
        }
        default:     /* Jacobian (v5.5.0) or Residute (v5.4.1) or something else */
        {
           break;
        }
    }
}


static void x2c_TDSystemO2_Float32_C__set_parameter(scicos_block* block, TDSYSTEMO2_FLOAT32 *blockParam) {
    int *paramI;
    double *paramR;
    TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTTDSystemO2_Float32 = GetWorkPtrs(block);
    blockParam->a11 = (float32)paramR[0];
    blockParam->a12 = (float32)paramR[1];
    blockParam->a21 = (float32)paramR[2];
    blockParam->a22 = (float32)paramR[3];
    blockParam->b11 = (float32)paramR[4];
    blockParam->b12 = (float32)paramR[5];
    blockParam->b21 = (float32)paramR[6];
    blockParam->b22 = (float32)paramR[7];
}


static void x2c_TDSystemO2_Float32_C__Initialization(scicos_block* block) {
    TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32;

    /* Declaration of inports */
    double *inport_In1_p;
    float32 inport_In1;
    double *inport_In2_p;
    float32 inport_In2;

    /* Declaration of outports */
    double *outport_Out1;
    double *outport_Out2;

    /* *** */
    pTTDSystemO2_Float32 = scicos_malloc(sizeof(TDSYSTEMO2_FLOAT32));
    GetWorkPtrs(block) = pTTDSystemO2_Float32;
    x2c_TDSystemO2_Float32_C__set_parameter(block, pTTDSystemO2_Float32);

    /* Assignment of inports */
    inport_In1_p = GetInPortPtrs(block, 1);
    inport_In1 = convert_double_to_float32(*inport_In1_p);
    pTTDSystemO2_Float32->In1 = &inport_In1;
    inport_In2_p = GetInPortPtrs(block, 2);
    inport_In2 = convert_double_to_float32(*inport_In2_p);
    pTTDSystemO2_Float32->In2 = &inport_In2;

    /* Assignment of parameter arrays */

    /* Initialization */
    TDSystemO2_Float32_Init(pTTDSystemO2_Float32);

    /* Assignment of outports */
    outport_Out1 = GetOutPortPtrs(block, 1);
    *outport_Out1 = convert_float32_to_double(pTTDSystemO2_Float32->Out1);
    outport_Out2 = GetOutPortPtrs(block, 2);
    *outport_Out2 = convert_float32_to_double(pTTDSystemO2_Float32->Out2);
}


static void x2c_TDSystemO2_Float32_C__Ending(scicos_block* block) {
    TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32;
    pTTDSystemO2_Float32 = GetWorkPtrs(block);
    scicos_free(pTTDSystemO2_Float32);
}


static void x2c_TDSystemO2_Float32_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_TDSystemO2_Float32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_TDSystemO2_Float32_C__StateUpdate_f(block);
    }
}


static void x2c_TDSystemO2_Float32_C__OutputUpdate(scicos_block* block) {
    TDSYSTEMO2_FLOAT32 *pTTDSystemO2_Float32;

    /* Declaration of inports */
    double *inport_In1_p;
    float32 inport_In1;
    double *inport_In2_p;
    float32 inport_In2;

    /* Declaration of outports */
    double *outport_Out1;
    double *outport_Out2;

    /* *** */
    pTTDSystemO2_Float32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_In1_p = GetInPortPtrs(block, 1);
    inport_In1 = convert_double_to_float32(*inport_In1_p);
    pTTDSystemO2_Float32->In1 = &inport_In1;
    inport_In2_p = GetInPortPtrs(block, 2);
    inport_In2 = convert_double_to_float32(*inport_In2_p);
    pTTDSystemO2_Float32->In2 = &inport_In2;

    /* Assignment of parameter arrays */

    /* Update */
    TDSystemO2_Float32_Update(pTTDSystemO2_Float32);

    /* Assignment of outports */
    outport_Out1 = GetOutPortPtrs(block, 1);
    *outport_Out1 = convert_float32_to_double(pTTDSystemO2_Float32->Out1);
    outport_Out2 = GetOutPortPtrs(block, 2);
    *outport_Out2 = convert_float32_to_double(pTTDSystemO2_Float32->Out2);
}

