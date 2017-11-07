// This file was generated by createCFunctionAux.sci on 03-03-2017 01:17

// Computational function for X2C block Inport

#define SCILAB_SIM_FILE /* mark this file as Scilab simulation file */

/* include Scicos / Xcos headers */
#include <scicos.h>
#include <scicos_block4.h>
#include <Simulation_PortConversion.h>

/* private prototypes */
void x2c_Inport_int32_C(scicos_block* block, scicos_flag flag);
static void x2c_Inport_int32_C__OutputUpdate(scicos_block* block);
static void x2c_Inport_int32_C__StateUpdate(scicos_block* block);
static void x2c_Inport_int32_C__Initialization(scicos_block* block);
static void x2c_Inport_int32_C__Ending(scicos_block* block);


void x2c_Inport_int32_C(scicos_block* block, scicos_flag flag) {
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
            x2c_Inport_int32_C__OutputUpdate(block);
            break;
        }
        case StateUpdate:      /* 2 */
        {
            x2c_Inport_int32_C__StateUpdate(block);
            break;
        }
        case OutputEventTiming: /* 3 */
        {
            break;
        }
        case Initialization:   /* 4 */
        {
            x2c_Inport_int32_C__Initialization(block);
            break;
        }
        case Ending:           /* 5 */
        {
            x2c_Inport_int32_C__Ending(block);
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


static void x2c_Inport_int32_C__Initialization(scicos_block* block) {
}


static void x2c_Inport_int32_C__Ending(scicos_block* block) {
}


static void x2c_Inport_int32_C__StateUpdate_f(scicos_block* block) {
}


static void x2c_Inport_int32_C__StateUpdate(scicos_block* block) {
    if (GetNevIn(block) > 0) {
        /*
        * GetNevIn(block) returns -1 in in case this function was called due to an internal zero-crossing.
        * GetNevIn(block)  ... activation index
        */
        x2c_Inport_int32_C__StateUpdate_f(block);
    }
}


static void x2c_Inport_int32_C__OutputUpdate(scicos_block* block) {
    double *outport_Out;
    double *inport_In_p;
    
    outport_Out = GetOutPortPtrs(block, 1);
    inport_In_p = GetInPortPtrs(block, 1);
    *outport_Out = convert_Q31_to_double(convert_double_to_Q31(*inport_In_p));
}

