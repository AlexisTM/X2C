// This file was generated by createCFunction.sci on 03-03-2017 01:17

// Computational function for X2C block Sin3Gen

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
#include <Sin3Gen_FiP16.h>
#include <Sin3Gen_FiP16.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_Sin3Gen_FiP16_C(scicos_block* block, scicos_flag flag);
static void x2c_Sin3Gen_FiP16_C__OutputUpdate(scicos_block* block);
static void x2c_Sin3Gen_FiP16_C__StateUpdate(scicos_block* block);
static void x2c_Sin3Gen_FiP16_C__Initialization(scicos_block* block);
static void x2c_Sin3Gen_FiP16_C__Ending(scicos_block* block);


void x2c_Sin3Gen_FiP16_C(scicos_block* block, scicos_flag flag) {
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
            x2c_Sin3Gen_FiP16_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_Sin3Gen_FiP16_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_Sin3Gen_FiP16_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_Sin3Gen_FiP16_C__Ending(block);
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


static void x2c_Sin3Gen_FiP16_C__set_parameter(scicos_block* block, SIN3GEN_FIP16 *blockParam) {
    int *paramI;
    double *paramR;
    SIN3GEN_FIP16 *pTSin3Gen_FiP16;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTSin3Gen_FiP16 = GetWorkPtrs(block);
    blockParam->delta_phi = (int16)paramI[0];
    blockParam->offset = (int16)paramI[1];
}


static void x2c_Sin3Gen_FiP16_C__Initialization(scicos_block* block) {
    SIN3GEN_FIP16 *pTSin3Gen_FiP16;

    /* Declaration of inports */
    double *inport_A_p;
    int16 inport_A;
    double *inport_f_p;
    int16 inport_f;

    /* Declaration of outports */
    double *outport_u;
    double *outport_v;
    double *outport_w;

    /* *** */
    pTSin3Gen_FiP16 = scicos_malloc(sizeof(SIN3GEN_FIP16));
    GetWorkPtrs(block) = pTSin3Gen_FiP16;
    x2c_Sin3Gen_FiP16_C__set_parameter(block, pTSin3Gen_FiP16);

    /* Assignment of inports */
    inport_A_p = GetInPortPtrs(block, 1);
    inport_A = convert_double_to_Q15(*inport_A_p);
    pTSin3Gen_FiP16->A = &inport_A;
    inport_f_p = GetInPortPtrs(block, 2);
    inport_f = convert_double_to_Q15(*inport_f_p);
    pTSin3Gen_FiP16->f = &inport_f;

    /* Assignment of parameter arrays */

    /* Initialization */
    Sin3Gen_FiP16_Init(pTSin3Gen_FiP16);

    /* Assignment of outports */
    outport_u = GetOutPortPtrs(block, 1);
    *outport_u = convert_Q15_to_double(pTSin3Gen_FiP16->u);
    outport_v = GetOutPortPtrs(block, 2);
    *outport_v = convert_Q15_to_double(pTSin3Gen_FiP16->v);
    outport_w = GetOutPortPtrs(block, 3);
    *outport_w = convert_Q15_to_double(pTSin3Gen_FiP16->w);
}


static void x2c_Sin3Gen_FiP16_C__Ending(scicos_block* block) {
    SIN3GEN_FIP16 *pTSin3Gen_FiP16;
    pTSin3Gen_FiP16 = GetWorkPtrs(block);
    scicos_free(pTSin3Gen_FiP16);
}


static void x2c_Sin3Gen_FiP16_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_Sin3Gen_FiP16_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_Sin3Gen_FiP16_C__StateUpdate_f(block);
    }
}


static void x2c_Sin3Gen_FiP16_C__OutputUpdate(scicos_block* block) {
    SIN3GEN_FIP16 *pTSin3Gen_FiP16;

    /* Declaration of inports */
    double *inport_A_p;
    int16 inport_A;
    double *inport_f_p;
    int16 inport_f;

    /* Declaration of outports */
    double *outport_u;
    double *outport_v;
    double *outport_w;

    /* *** */
    pTSin3Gen_FiP16 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_A_p = GetInPortPtrs(block, 1);
    inport_A = convert_double_to_Q15(*inport_A_p);
    pTSin3Gen_FiP16->A = &inport_A;
    inport_f_p = GetInPortPtrs(block, 2);
    inport_f = convert_double_to_Q15(*inport_f_p);
    pTSin3Gen_FiP16->f = &inport_f;

    /* Assignment of parameter arrays */

    /* Update */
    Sin3Gen_FiP16_Update(pTSin3Gen_FiP16);

    /* Assignment of outports */
    outport_u = GetOutPortPtrs(block, 1);
    *outport_u = convert_Q15_to_double(pTSin3Gen_FiP16->u);
    outport_v = GetOutPortPtrs(block, 2);
    *outport_v = convert_Q15_to_double(pTSin3Gen_FiP16->v);
    outport_w = GetOutPortPtrs(block, 3);
    *outport_w = convert_Q15_to_double(pTSin3Gen_FiP16->w);
}


