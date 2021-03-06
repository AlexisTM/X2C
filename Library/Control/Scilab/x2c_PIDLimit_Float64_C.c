// This file was generated by createCFunction.sci on 03-03-2017 01:18

// Computational function for X2C block PIDLimit

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
#include <PIDLimit_Float64.h>
#include <PIDLimit_Float64.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_PIDLimit_Float64_C(scicos_block* block, scicos_flag flag);
static void x2c_PIDLimit_Float64_C__OutputUpdate(scicos_block* block);
static void x2c_PIDLimit_Float64_C__StateUpdate(scicos_block* block);
static void x2c_PIDLimit_Float64_C__Initialization(scicos_block* block);
static void x2c_PIDLimit_Float64_C__Ending(scicos_block* block);


void x2c_PIDLimit_Float64_C(scicos_block* block, scicos_flag flag) {
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
            x2c_PIDLimit_Float64_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_PIDLimit_Float64_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_PIDLimit_Float64_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_PIDLimit_Float64_C__Ending(block);
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


static void x2c_PIDLimit_Float64_C__set_parameter(scicos_block* block, PIDLIMIT_FLOAT64 *blockParam) {
    int *paramI;
    double *paramR;
    PIDLIMIT_FLOAT64 *pTPIDLimit_Float64;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTPIDLimit_Float64 = GetWorkPtrs(block);
    blockParam->b0 = (float64)paramR[0];
    blockParam->b1 = (float64)paramR[1];
    blockParam->b0d = (float64)paramR[2];
    blockParam->b1d = (float64)paramR[3];
    blockParam->a0d = (float64)paramR[4];
}


static void x2c_PIDLimit_Float64_C__Initialization(scicos_block* block) {
    PIDLIMIT_FLOAT64 *pTPIDLimit_Float64;

    /* Declaration of inports */
    double *inport_In_p;
    float64 inport_In;
    double *inport_Init_p;
    float64 inport_Init;
    double *inport_max_p;
    float64 inport_max;
    double *inport_min_p;
    float64 inport_min;
    double *inport_Enable_p;
    int8 inport_Enable;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTPIDLimit_Float64 = scicos_malloc(sizeof(PIDLIMIT_FLOAT64));
    GetWorkPtrs(block) = pTPIDLimit_Float64;
    x2c_PIDLimit_Float64_C__set_parameter(block, pTPIDLimit_Float64);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_float64(*inport_In_p);
    pTPIDLimit_Float64->In = &inport_In;
    inport_Init_p = GetInPortPtrs(block, 2);
    inport_Init = convert_double_to_float64(*inport_Init_p);
    pTPIDLimit_Float64->Init = &inport_Init;
    inport_max_p = GetInPortPtrs(block, 3);
    inport_max = convert_double_to_float64(*inport_max_p);
    pTPIDLimit_Float64->max = &inport_max;
    inport_min_p = GetInPortPtrs(block, 4);
    inport_min = convert_double_to_float64(*inport_min_p);
    pTPIDLimit_Float64->min = &inport_min;
    inport_Enable_p = GetInPortPtrs(block, 5);
    inport_Enable = convert_double_to_Q7(*inport_Enable_p);
    pTPIDLimit_Float64->Enable = &inport_Enable;

    /* Assignment of parameter arrays */

    /* Initialization */
    PIDLimit_Float64_Init(pTPIDLimit_Float64);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_float64_to_double(pTPIDLimit_Float64->Out);
}


static void x2c_PIDLimit_Float64_C__Ending(scicos_block* block) {
    PIDLIMIT_FLOAT64 *pTPIDLimit_Float64;
    pTPIDLimit_Float64 = GetWorkPtrs(block);
    scicos_free(pTPIDLimit_Float64);
}


static void x2c_PIDLimit_Float64_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_PIDLimit_Float64_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_PIDLimit_Float64_C__StateUpdate_f(block);
    }
}


static void x2c_PIDLimit_Float64_C__OutputUpdate(scicos_block* block) {
    PIDLIMIT_FLOAT64 *pTPIDLimit_Float64;

    /* Declaration of inports */
    double *inport_In_p;
    float64 inport_In;
    double *inport_Init_p;
    float64 inport_Init;
    double *inport_max_p;
    float64 inport_max;
    double *inport_min_p;
    float64 inport_min;
    double *inport_Enable_p;
    int8 inport_Enable;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTPIDLimit_Float64 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_float64(*inport_In_p);
    pTPIDLimit_Float64->In = &inport_In;
    inport_Init_p = GetInPortPtrs(block, 2);
    inport_Init = convert_double_to_float64(*inport_Init_p);
    pTPIDLimit_Float64->Init = &inport_Init;
    inport_max_p = GetInPortPtrs(block, 3);
    inport_max = convert_double_to_float64(*inport_max_p);
    pTPIDLimit_Float64->max = &inport_max;
    inport_min_p = GetInPortPtrs(block, 4);
    inport_min = convert_double_to_float64(*inport_min_p);
    pTPIDLimit_Float64->min = &inport_min;
    inport_Enable_p = GetInPortPtrs(block, 5);
    inport_Enable = convert_double_to_Q7(*inport_Enable_p);
    pTPIDLimit_Float64->Enable = &inport_Enable;

    /* Assignment of parameter arrays */

    /* Update */
    PIDLimit_Float64_Update(pTPIDLimit_Float64);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_float64_to_double(pTPIDLimit_Float64->Out);
}


