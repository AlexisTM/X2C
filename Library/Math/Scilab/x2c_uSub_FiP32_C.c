// This file was generated by createCFunction.sci on 03-03-2017 01:17

// Computational function for X2C block uSub

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
#include <uSub_FiP32.h>
#include <uSub_FiP32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_uSub_FiP32_C(scicos_block* block, scicos_flag flag);
static void x2c_uSub_FiP32_C__OutputUpdate(scicos_block* block);
static void x2c_uSub_FiP32_C__StateUpdate(scicos_block* block);
static void x2c_uSub_FiP32_C__Initialization(scicos_block* block);
static void x2c_uSub_FiP32_C__Ending(scicos_block* block);


void x2c_uSub_FiP32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_uSub_FiP32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_uSub_FiP32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_uSub_FiP32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_uSub_FiP32_C__Ending(block);
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


static void x2c_uSub_FiP32_C__set_parameter(scicos_block* block, USUB_FIP32 *blockParam) {
    int *paramI;
    double *paramR;
    USUB_FIP32 *pTuSub_FiP32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTuSub_FiP32 = GetWorkPtrs(block);
}


static void x2c_uSub_FiP32_C__Initialization(scicos_block* block) {
    USUB_FIP32 *pTuSub_FiP32;

    /* Declaration of inports */
    double *inport_Plus_p;
    int32 inport_Plus;
    double *inport_Minus_p;
    int32 inport_Minus;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTuSub_FiP32 = scicos_malloc(sizeof(USUB_FIP32));
    GetWorkPtrs(block) = pTuSub_FiP32;
    x2c_uSub_FiP32_C__set_parameter(block, pTuSub_FiP32);

    /* Assignment of inports */
    inport_Plus_p = GetInPortPtrs(block, 1);
    inport_Plus = convert_double_to_Q31(*inport_Plus_p);
    pTuSub_FiP32->Plus = &inport_Plus;
    inport_Minus_p = GetInPortPtrs(block, 2);
    inport_Minus = convert_double_to_Q31(*inport_Minus_p);
    pTuSub_FiP32->Minus = &inport_Minus;

    /* Assignment of parameter arrays */

    /* Initialization */
    uSub_FiP32_Init(pTuSub_FiP32);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_Q31_to_double(pTuSub_FiP32->Out);
}


static void x2c_uSub_FiP32_C__Ending(scicos_block* block) {
    USUB_FIP32 *pTuSub_FiP32;
    pTuSub_FiP32 = GetWorkPtrs(block);
    scicos_free(pTuSub_FiP32);
}


static void x2c_uSub_FiP32_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_uSub_FiP32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_uSub_FiP32_C__StateUpdate_f(block);
    }
}


static void x2c_uSub_FiP32_C__OutputUpdate(scicos_block* block) {
    USUB_FIP32 *pTuSub_FiP32;

    /* Declaration of inports */
    double *inport_Plus_p;
    int32 inport_Plus;
    double *inport_Minus_p;
    int32 inport_Minus;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTuSub_FiP32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_Plus_p = GetInPortPtrs(block, 1);
    inport_Plus = convert_double_to_Q31(*inport_Plus_p);
    pTuSub_FiP32->Plus = &inport_Plus;
    inport_Minus_p = GetInPortPtrs(block, 2);
    inport_Minus = convert_double_to_Q31(*inport_Minus_p);
    pTuSub_FiP32->Minus = &inport_Minus;

    /* Assignment of parameter arrays */

    /* Update */
    uSub_FiP32_Update(pTuSub_FiP32);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_Q31_to_double(pTuSub_FiP32->Out);
}


