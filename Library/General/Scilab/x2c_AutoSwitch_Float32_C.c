// This file was generated by createCFunction.sci on 03-03-2017 01:17

// Computational function for X2C block AutoSwitch

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
#include <AutoSwitch_Float32.h>
#include <AutoSwitch_Float32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_AutoSwitch_Float32_C(scicos_block* block, scicos_flag flag);
static void x2c_AutoSwitch_Float32_C__OutputUpdate(scicos_block* block);
static void x2c_AutoSwitch_Float32_C__StateUpdate(scicos_block* block);
static void x2c_AutoSwitch_Float32_C__Initialization(scicos_block* block);
static void x2c_AutoSwitch_Float32_C__Ending(scicos_block* block);


void x2c_AutoSwitch_Float32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_AutoSwitch_Float32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_AutoSwitch_Float32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_AutoSwitch_Float32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_AutoSwitch_Float32_C__Ending(block);
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


static void x2c_AutoSwitch_Float32_C__set_parameter(scicos_block* block, AUTOSWITCH_FLOAT32 *blockParam) {
    int *paramI;
    double *paramR;
    AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTAutoSwitch_Float32 = GetWorkPtrs(block);
    blockParam->Thresh_up = (float32)paramR[0];
    blockParam->Thresh_down = (float32)paramR[1];
}


static void x2c_AutoSwitch_Float32_C__Initialization(scicos_block* block) {
    AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32;

    /* Declaration of inports */
    double *inport_In1_p;
    float32 inport_In1;
    double *inport_Switch_p;
    float32 inport_Switch;
    double *inport_In3_p;
    float32 inport_In3;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTAutoSwitch_Float32 = scicos_malloc(sizeof(AUTOSWITCH_FLOAT32));
    GetWorkPtrs(block) = pTAutoSwitch_Float32;
    x2c_AutoSwitch_Float32_C__set_parameter(block, pTAutoSwitch_Float32);

    /* Assignment of inports */
    inport_In1_p = GetInPortPtrs(block, 1);
    inport_In1 = convert_double_to_float32(*inport_In1_p);
    pTAutoSwitch_Float32->In1 = &inport_In1;
    inport_Switch_p = GetInPortPtrs(block, 2);
    inport_Switch = convert_double_to_float32(*inport_Switch_p);
    pTAutoSwitch_Float32->Switch = &inport_Switch;
    inport_In3_p = GetInPortPtrs(block, 3);
    inport_In3 = convert_double_to_float32(*inport_In3_p);
    pTAutoSwitch_Float32->In3 = &inport_In3;

    /* Assignment of parameter arrays */

    /* Initialization */
    AutoSwitch_Float32_Init(pTAutoSwitch_Float32);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_float32_to_double(pTAutoSwitch_Float32->Out);
}


static void x2c_AutoSwitch_Float32_C__Ending(scicos_block* block) {
    AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32;
    pTAutoSwitch_Float32 = GetWorkPtrs(block);
    scicos_free(pTAutoSwitch_Float32);
}


static void x2c_AutoSwitch_Float32_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_AutoSwitch_Float32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_AutoSwitch_Float32_C__StateUpdate_f(block);
    }
}


static void x2c_AutoSwitch_Float32_C__OutputUpdate(scicos_block* block) {
    AUTOSWITCH_FLOAT32 *pTAutoSwitch_Float32;

    /* Declaration of inports */
    double *inport_In1_p;
    float32 inport_In1;
    double *inport_Switch_p;
    float32 inport_Switch;
    double *inport_In3_p;
    float32 inport_In3;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTAutoSwitch_Float32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_In1_p = GetInPortPtrs(block, 1);
    inport_In1 = convert_double_to_float32(*inport_In1_p);
    pTAutoSwitch_Float32->In1 = &inport_In1;
    inport_Switch_p = GetInPortPtrs(block, 2);
    inport_Switch = convert_double_to_float32(*inport_Switch_p);
    pTAutoSwitch_Float32->Switch = &inport_Switch;
    inport_In3_p = GetInPortPtrs(block, 3);
    inport_In3 = convert_double_to_float32(*inport_In3_p);
    pTAutoSwitch_Float32->In3 = &inport_In3;

    /* Assignment of parameter arrays */

    /* Update */
    AutoSwitch_Float32_Update(pTAutoSwitch_Float32);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_float32_to_double(pTAutoSwitch_Float32->Out);
}


