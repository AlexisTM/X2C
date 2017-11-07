// This file was generated by createCFunction.sci on 03-03-2017 01:18

// Computational function for X2C block PILimit

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
#include <PILimit_FiP16.h>
#include <PILimit_FiP16.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_PILimit_FiP16_C(scicos_block* block, scicos_flag flag);
static void x2c_PILimit_FiP16_C__OutputUpdate(scicos_block* block);
static void x2c_PILimit_FiP16_C__StateUpdate(scicos_block* block);
static void x2c_PILimit_FiP16_C__Initialization(scicos_block* block);
static void x2c_PILimit_FiP16_C__Ending(scicos_block* block);


void x2c_PILimit_FiP16_C(scicos_block* block, scicos_flag flag) {
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
            x2c_PILimit_FiP16_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_PILimit_FiP16_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_PILimit_FiP16_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_PILimit_FiP16_C__Ending(block);
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


static void x2c_PILimit_FiP16_C__set_parameter(scicos_block* block, PILIMIT_FIP16 *blockParam) {
    int *paramI;
    double *paramR;
    PILIMIT_FIP16 *pTPILimit_FiP16;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTPILimit_FiP16 = GetWorkPtrs(block);
    blockParam->b0 = (int16)paramI[0];
    blockParam->b1 = (int16)paramI[1];
    blockParam->sfrb0 = (int8)paramI[2];
    blockParam->sfrb1 = (int8)paramI[3];
}


static void x2c_PILimit_FiP16_C__Initialization(scicos_block* block) {
    PILIMIT_FIP16 *pTPILimit_FiP16;

    /* Declaration of inports */
    double *inport_In_p;
    int16 inport_In;
    double *inport_Init_p;
    int16 inport_Init;
    double *inport_max_p;
    int16 inport_max;
    double *inport_min_p;
    int16 inport_min;
    double *inport_Enable_p;
    int8 inport_Enable;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTPILimit_FiP16 = scicos_malloc(sizeof(PILIMIT_FIP16));
    GetWorkPtrs(block) = pTPILimit_FiP16;
    x2c_PILimit_FiP16_C__set_parameter(block, pTPILimit_FiP16);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_Q15(*inport_In_p);
    pTPILimit_FiP16->In = &inport_In;
    inport_Init_p = GetInPortPtrs(block, 2);
    inport_Init = convert_double_to_Q15(*inport_Init_p);
    pTPILimit_FiP16->Init = &inport_Init;
    inport_max_p = GetInPortPtrs(block, 3);
    inport_max = convert_double_to_Q15(*inport_max_p);
    pTPILimit_FiP16->max = &inport_max;
    inport_min_p = GetInPortPtrs(block, 4);
    inport_min = convert_double_to_Q15(*inport_min_p);
    pTPILimit_FiP16->min = &inport_min;
    inport_Enable_p = GetInPortPtrs(block, 5);
    inport_Enable = convert_double_to_Q7(*inport_Enable_p);
    pTPILimit_FiP16->Enable = &inport_Enable;

    /* Assignment of parameter arrays */

    /* Initialization */
    PILimit_FiP16_Init(pTPILimit_FiP16);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_Q15_to_double(pTPILimit_FiP16->Out);
}


static void x2c_PILimit_FiP16_C__Ending(scicos_block* block) {
    PILIMIT_FIP16 *pTPILimit_FiP16;
    pTPILimit_FiP16 = GetWorkPtrs(block);
    scicos_free(pTPILimit_FiP16);
}


static void x2c_PILimit_FiP16_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_PILimit_FiP16_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_PILimit_FiP16_C__StateUpdate_f(block);
    }
}


static void x2c_PILimit_FiP16_C__OutputUpdate(scicos_block* block) {
    PILIMIT_FIP16 *pTPILimit_FiP16;

    /* Declaration of inports */
    double *inport_In_p;
    int16 inport_In;
    double *inport_Init_p;
    int16 inport_Init;
    double *inport_max_p;
    int16 inport_max;
    double *inport_min_p;
    int16 inport_min;
    double *inport_Enable_p;
    int8 inport_Enable;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTPILimit_FiP16 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_Q15(*inport_In_p);
    pTPILimit_FiP16->In = &inport_In;
    inport_Init_p = GetInPortPtrs(block, 2);
    inport_Init = convert_double_to_Q15(*inport_Init_p);
    pTPILimit_FiP16->Init = &inport_Init;
    inport_max_p = GetInPortPtrs(block, 3);
    inport_max = convert_double_to_Q15(*inport_max_p);
    pTPILimit_FiP16->max = &inport_max;
    inport_min_p = GetInPortPtrs(block, 4);
    inport_min = convert_double_to_Q15(*inport_min_p);
    pTPILimit_FiP16->min = &inport_min;
    inport_Enable_p = GetInPortPtrs(block, 5);
    inport_Enable = convert_double_to_Q7(*inport_Enable_p);
    pTPILimit_FiP16->Enable = &inport_Enable;

    /* Assignment of parameter arrays */

    /* Update */
    PILimit_FiP16_Update(pTPILimit_FiP16);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_Q15_to_double(pTPILimit_FiP16->Out);
}

