// This file was generated by createCFunction.sci on 03-03-2017 01:17

// Computational function for X2C block Sum

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
#include <Sum_FiP8.h>
#include <Sum_FiP8.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_Sum_FiP8_C(scicos_block* block, scicos_flag flag);
static void x2c_Sum_FiP8_C__OutputUpdate(scicos_block* block);
static void x2c_Sum_FiP8_C__StateUpdate(scicos_block* block);
static void x2c_Sum_FiP8_C__Initialization(scicos_block* block);
static void x2c_Sum_FiP8_C__Ending(scicos_block* block);


void x2c_Sum_FiP8_C(scicos_block* block, scicos_flag flag) {
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
            x2c_Sum_FiP8_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_Sum_FiP8_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_Sum_FiP8_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_Sum_FiP8_C__Ending(block);
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


static void x2c_Sum_FiP8_C__set_parameter(scicos_block* block, SUM_FIP8 *blockParam) {
    int *paramI;
    double *paramR;
    SUM_FIP8 *pTSum_FiP8;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTSum_FiP8 = GetWorkPtrs(block);
    blockParam->sign = (uint16)paramI[0];
}


static void x2c_Sum_FiP8_C__Initialization(scicos_block* block) {
    SUM_FIP8 *pTSum_FiP8;

    /* Declaration of inports */
    double *inport_In1_p;
    int8 inport_In1;
    double *inport_In2_p;
    int8 inport_In2;
    double *inport_In3_p;
    int8 inport_In3;
    double *inport_In4_p;
    int8 inport_In4;
    double *inport_In5_p;
    int8 inport_In5;
    double *inport_In6_p;
    int8 inport_In6;
    double *inport_In7_p;
    int8 inport_In7;
    double *inport_In8_p;
    int8 inport_In8;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTSum_FiP8 = scicos_malloc(sizeof(SUM_FIP8));
    GetWorkPtrs(block) = pTSum_FiP8;
    x2c_Sum_FiP8_C__set_parameter(block, pTSum_FiP8);

    /* Assignment of inports */
    inport_In1_p = GetInPortPtrs(block, 1);
    inport_In1 = convert_double_to_Q7(*inport_In1_p);
    pTSum_FiP8->In1 = &inport_In1;
    inport_In2_p = GetInPortPtrs(block, 2);
    inport_In2 = convert_double_to_Q7(*inport_In2_p);
    pTSum_FiP8->In2 = &inport_In2;
    inport_In3_p = GetInPortPtrs(block, 3);
    inport_In3 = convert_double_to_Q7(*inport_In3_p);
    pTSum_FiP8->In3 = &inport_In3;
    inport_In4_p = GetInPortPtrs(block, 4);
    inport_In4 = convert_double_to_Q7(*inport_In4_p);
    pTSum_FiP8->In4 = &inport_In4;
    inport_In5_p = GetInPortPtrs(block, 5);
    inport_In5 = convert_double_to_Q7(*inport_In5_p);
    pTSum_FiP8->In5 = &inport_In5;
    inport_In6_p = GetInPortPtrs(block, 6);
    inport_In6 = convert_double_to_Q7(*inport_In6_p);
    pTSum_FiP8->In6 = &inport_In6;
    inport_In7_p = GetInPortPtrs(block, 7);
    inport_In7 = convert_double_to_Q7(*inport_In7_p);
    pTSum_FiP8->In7 = &inport_In7;
    inport_In8_p = GetInPortPtrs(block, 8);
    inport_In8 = convert_double_to_Q7(*inport_In8_p);
    pTSum_FiP8->In8 = &inport_In8;

    /* Assignment of parameter arrays */

    /* Initialization */
    Sum_FiP8_Init(pTSum_FiP8);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_Q7_to_double(pTSum_FiP8->Out);
}


static void x2c_Sum_FiP8_C__Ending(scicos_block* block) {
    SUM_FIP8 *pTSum_FiP8;
    pTSum_FiP8 = GetWorkPtrs(block);
    scicos_free(pTSum_FiP8);
}


static void x2c_Sum_FiP8_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_Sum_FiP8_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_Sum_FiP8_C__StateUpdate_f(block);
    }
}


static void x2c_Sum_FiP8_C__OutputUpdate(scicos_block* block) {
    SUM_FIP8 *pTSum_FiP8;

    /* Declaration of inports */
    double *inport_In1_p;
    int8 inport_In1;
    double *inport_In2_p;
    int8 inport_In2;
    double *inport_In3_p;
    int8 inport_In3;
    double *inport_In4_p;
    int8 inport_In4;
    double *inport_In5_p;
    int8 inport_In5;
    double *inport_In6_p;
    int8 inport_In6;
    double *inport_In7_p;
    int8 inport_In7;
    double *inport_In8_p;
    int8 inport_In8;

    /* Declaration of outports */
    double *outport_Out;

    /* *** */
    pTSum_FiP8 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_In1_p = GetInPortPtrs(block, 1);
    inport_In1 = convert_double_to_Q7(*inport_In1_p);
    pTSum_FiP8->In1 = &inport_In1;
    inport_In2_p = GetInPortPtrs(block, 2);
    inport_In2 = convert_double_to_Q7(*inport_In2_p);
    pTSum_FiP8->In2 = &inport_In2;
    inport_In3_p = GetInPortPtrs(block, 3);
    inport_In3 = convert_double_to_Q7(*inport_In3_p);
    pTSum_FiP8->In3 = &inport_In3;
    inport_In4_p = GetInPortPtrs(block, 4);
    inport_In4 = convert_double_to_Q7(*inport_In4_p);
    pTSum_FiP8->In4 = &inport_In4;
    inport_In5_p = GetInPortPtrs(block, 5);
    inport_In5 = convert_double_to_Q7(*inport_In5_p);
    pTSum_FiP8->In5 = &inport_In5;
    inport_In6_p = GetInPortPtrs(block, 6);
    inport_In6 = convert_double_to_Q7(*inport_In6_p);
    pTSum_FiP8->In6 = &inport_In6;
    inport_In7_p = GetInPortPtrs(block, 7);
    inport_In7 = convert_double_to_Q7(*inport_In7_p);
    pTSum_FiP8->In7 = &inport_In7;
    inport_In8_p = GetInPortPtrs(block, 8);
    inport_In8 = convert_double_to_Q7(*inport_In8_p);
    pTSum_FiP8->In8 = &inport_In8;

    /* Assignment of parameter arrays */

    /* Update */
    Sum_FiP8_Update(pTSum_FiP8);

    /* Assignment of outports */
    outport_Out = GetOutPortPtrs(block, 1);
    *outport_Out = convert_Q7_to_double(pTSum_FiP8->Out);
}


