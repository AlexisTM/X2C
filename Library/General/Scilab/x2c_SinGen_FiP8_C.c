// This file was generated by createCFunction.sci on 03-03-2017 01:17

// Computational function for X2C block SinGen

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
#include <SinGen_FiP8.h>
#include <SinGen_FiP8.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_SinGen_FiP8_C(scicos_block* block, scicos_flag flag);
static void x2c_SinGen_FiP8_C__OutputUpdate(scicos_block* block);
static void x2c_SinGen_FiP8_C__StateUpdate(scicos_block* block);
static void x2c_SinGen_FiP8_C__Initialization(scicos_block* block);
static void x2c_SinGen_FiP8_C__Ending(scicos_block* block);


void x2c_SinGen_FiP8_C(scicos_block* block, scicos_flag flag) {
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
            x2c_SinGen_FiP8_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_SinGen_FiP8_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_SinGen_FiP8_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_SinGen_FiP8_C__Ending(block);
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


static void x2c_SinGen_FiP8_C__set_parameter(scicos_block* block, SINGEN_FIP8 *blockParam) {
    int *paramI;
    double *paramR;
    SINGEN_FIP8 *pTSinGen_FiP8;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTSinGen_FiP8 = GetWorkPtrs(block);
    blockParam->delta_phi = (int8)paramI[0];
    blockParam->phase = (int8)paramI[1];
    blockParam->offset = (int8)paramI[2];
}


static void x2c_SinGen_FiP8_C__Initialization(scicos_block* block) {
    SINGEN_FIP8 *pTSinGen_FiP8;

    /* Declaration of inports */
    double *inport_A_p;
    int8 inport_A;
    double *inport_f_p;
    int8 inport_f;

    /* Declaration of outports */
    double *outport_u;

    /* *** */
    pTSinGen_FiP8 = scicos_malloc(sizeof(SINGEN_FIP8));
    GetWorkPtrs(block) = pTSinGen_FiP8;
    x2c_SinGen_FiP8_C__set_parameter(block, pTSinGen_FiP8);

    /* Assignment of inports */
    inport_A_p = GetInPortPtrs(block, 1);
    inport_A = convert_double_to_Q7(*inport_A_p);
    pTSinGen_FiP8->A = &inport_A;
    inport_f_p = GetInPortPtrs(block, 2);
    inport_f = convert_double_to_Q7(*inport_f_p);
    pTSinGen_FiP8->f = &inport_f;

    /* Assignment of parameter arrays */

    /* Initialization */
    SinGen_FiP8_Init(pTSinGen_FiP8);

    /* Assignment of outports */
    outport_u = GetOutPortPtrs(block, 1);
    *outport_u = convert_Q7_to_double(pTSinGen_FiP8->u);
}


static void x2c_SinGen_FiP8_C__Ending(scicos_block* block) {
    SINGEN_FIP8 *pTSinGen_FiP8;
    pTSinGen_FiP8 = GetWorkPtrs(block);
    scicos_free(pTSinGen_FiP8);
}


static void x2c_SinGen_FiP8_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_SinGen_FiP8_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_SinGen_FiP8_C__StateUpdate_f(block);
    }
}


static void x2c_SinGen_FiP8_C__OutputUpdate(scicos_block* block) {
    SINGEN_FIP8 *pTSinGen_FiP8;

    /* Declaration of inports */
    double *inport_A_p;
    int8 inport_A;
    double *inport_f_p;
    int8 inport_f;

    /* Declaration of outports */
    double *outport_u;

    /* *** */
    pTSinGen_FiP8 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_A_p = GetInPortPtrs(block, 1);
    inport_A = convert_double_to_Q7(*inport_A_p);
    pTSinGen_FiP8->A = &inport_A;
    inport_f_p = GetInPortPtrs(block, 2);
    inport_f = convert_double_to_Q7(*inport_f_p);
    pTSinGen_FiP8->f = &inport_f;

    /* Assignment of parameter arrays */

    /* Update */
    SinGen_FiP8_Update(pTSinGen_FiP8);

    /* Assignment of outports */
    outport_u = GetOutPortPtrs(block, 1);
    *outport_u = convert_Q7_to_double(pTSinGen_FiP8->u);
}


