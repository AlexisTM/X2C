// This file was generated by createCFunction.sci on 03-03-2017 01:17

// Computational function for X2C block SaveSignal

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
#include <SaveSignal_Float32.h>
#include <SaveSignal_Float32.c>

/* */
#define BLOCK_ERROR_INPUT_OUT_OF_DOMAIN (-1)
#define BLOCK_ERROR_SINGULARITY (-2)
#define BLOCK_ERROR_INTERNAL (-3)
#define BLOCK_ERROR_CANNOT_ALLOCATE_MEMORY (-16)

/* */
void x2c_SaveSignal_Float32_C(scicos_block* block, scicos_flag flag);
static void x2c_SaveSignal_Float32_C__OutputUpdate(scicos_block* block);
static void x2c_SaveSignal_Float32_C__StateUpdate(scicos_block* block);
static void x2c_SaveSignal_Float32_C__Initialization(scicos_block* block);
static void x2c_SaveSignal_Float32_C__Ending(scicos_block* block);


void x2c_SaveSignal_Float32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_SaveSignal_Float32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_SaveSignal_Float32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_SaveSignal_Float32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_SaveSignal_Float32_C__Ending(block);
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


static void x2c_SaveSignal_Float32_C__set_parameter(scicos_block* block, SAVESIGNAL_FLOAT32 *blockParam) {
    int *paramI;
    double *paramR;
    SAVESIGNAL_FLOAT32 *pTSaveSignal_Float32;
    
    /* *** */
    paramI = GetIparPtrs(block);  /* integer parameters  */
    paramR = GetRparPtrs(block);  /* real parameters     */
    pTSaveSignal_Float32 = GetWorkPtrs(block);
}


static void x2c_SaveSignal_Float32_C__Initialization(scicos_block* block) {
    SAVESIGNAL_FLOAT32 *pTSaveSignal_Float32;

    /* Declaration of inports */
    double *inport_In_p;
    float32 inport_In;

    /* Declaration of outports */

    /* *** */
    pTSaveSignal_Float32 = scicos_malloc(sizeof(SAVESIGNAL_FLOAT32));
    GetWorkPtrs(block) = pTSaveSignal_Float32;
    x2c_SaveSignal_Float32_C__set_parameter(block, pTSaveSignal_Float32);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_float32(*inport_In_p);
    pTSaveSignal_Float32->In = &inport_In;

    /* Assignment of parameter arrays */

    /* Initialization */
    SaveSignal_Float32_Init(pTSaveSignal_Float32);

    /* Assignment of outports */
}


static void x2c_SaveSignal_Float32_C__Ending(scicos_block* block) {
    SAVESIGNAL_FLOAT32 *pTSaveSignal_Float32;
    pTSaveSignal_Float32 = GetWorkPtrs(block);
    scicos_free(pTSaveSignal_Float32);
}


static void x2c_SaveSignal_Float32_C__StateUpdate_f(scicos_block* block) {
/* Do nothing, calling of update function and writing to outputs is done in OutputUpdate */
}


static void x2c_SaveSignal_Float32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_SaveSignal_Float32_C__StateUpdate_f(block);
    }
}


static void x2c_SaveSignal_Float32_C__OutputUpdate(scicos_block* block) {
    SAVESIGNAL_FLOAT32 *pTSaveSignal_Float32;

    /* Declaration of inports */
    double *inport_In_p;
    float32 inport_In;

    /* Declaration of outports */

    /* *** */
    pTSaveSignal_Float32 = GetWorkPtrs(block);

    /* Assignment of inports */
    inport_In_p = GetInPortPtrs(block, 1);
    inport_In = convert_double_to_float32(*inport_In_p);
    pTSaveSignal_Float32->In = &inport_In;

    /* Assignment of parameter arrays */

    /* Update */
/* Present implementation has no update function */

    /* Assignment of outports */
}


