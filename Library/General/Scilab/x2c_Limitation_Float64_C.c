// This file was generated by createCFunction.sci on 03-03-2017 01:17

// Computational function for X2C block Limitation

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
#include <Limitation_Float64.h>
#include <Limitation_Float64.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_Limitation_Float64_C(scicos_block* block, scicos_flag flag);
static void x2c_Limitation_Float64_C__OutputUpdate(scicos_block* block);
static void x2c_Limitation_Float64_C__StateUpdate(scicos_block* block);
static void x2c_Limitation_Float64_C__Initialization(scicos_block* block);
static void x2c_Limitation_Float64_C__Ending(scicos_block* block);


void x2c_Limitation_Float64_C(scicos_block* block, scicos_flag flag) {
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
            x2c_Limitation_Float64_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_Limitation_Float64_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_Limitation_Float64_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_Limitation_Float64_C__Ending(block);
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


static void x2c_Limitation_Float64_C__set_parameter(scicos_block* block, LIMITATION_FLOAT64 *blockParam) {
    int *paramI;
    double *paramR;
    LIMITATION_FLOAT64 *pTLimitation_Float64;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTLimitation_Float64 = GetWorkPtrs(block);
}


static void x2c_Limitation_Float64_C__Initialization(scicos_block* block) {
    LIMITATION_FLOAT64 *pTLimitation_Float64;

    /* Declaration of inports */
    double *inport_In_p;
    float64 inport_In;
    double *inport_max_p;
    float64 inport_max;
    double *inport_min_p;
    float64 inport_min;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTLimitation_Float64 = scicos_malloc(sizeof(LIMITATION_FLOAT64));
    GetWorkPtrs(block) = pTLimitation_Float64;
    x2c_Limitation_Float64_C__set_parameter(block, pTLimitation_Float64);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_float64(*inport_In_p);
    pTLimitation_Float64->In = &inport_In;
    inport_max_p = GetInPortPtrs(block, 2);
    inport_max = convert_double_to_float64(*inport_max_p);
    pTLimitation_Float64->max = &inport_max;
    inport_min_p = GetInPortPtrs(block, 3);
    inport_min = convert_double_to_float64(*inport_min_p);
    pTLimitation_Float64->min = &inport_min;

    /* Assignment of parameter arrays */

    /* Initialization */
    Limitation_Float64_Init(pTLimitation_Float64);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_float64_to_double(pTLimitation_Float64->Out);
}


static void x2c_Limitation_Float64_C__Ending(scicos_block* block) {
    LIMITATION_FLOAT64 *pTLimitation_Float64;
    pTLimitation_Float64 = GetWorkPtrs(block);
    scicos_free(pTLimitation_Float64);
}


static void x2c_Limitation_Float64_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_Limitation_Float64_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_Limitation_Float64_C__StateUpdate_f(block);
    }
}


static void x2c_Limitation_Float64_C__OutputUpdate(scicos_block* block) {
    LIMITATION_FLOAT64 *pTLimitation_Float64;

    /* Declaration of inports */
    double *inport_In_p;
    float64 inport_In;
    double *inport_max_p;
    float64 inport_max;
    double *inport_min_p;
    float64 inport_min;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTLimitation_Float64 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_float64(*inport_In_p);
    pTLimitation_Float64->In = &inport_In;
    inport_max_p = GetInPortPtrs(block, 2);
    inport_max = convert_double_to_float64(*inport_max_p);
    pTLimitation_Float64->max = &inport_max;
    inport_min_p = GetInPortPtrs(block, 3);
    inport_min = convert_double_to_float64(*inport_min_p);
    pTLimitation_Float64->min = &inport_min;

    /* Assignment of parameter arrays */

    /* Update */
    Limitation_Float64_Update(pTLimitation_Float64);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_float64_to_double(pTLimitation_Float64->Out);
}


