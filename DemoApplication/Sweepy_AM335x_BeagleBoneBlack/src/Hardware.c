/*
 * $LastChangedRevision: 1088 $
 * $LastChangedDate:: 2017-01-26 18:07:41 +0100#$
 *
 * Copyright (c) 2017, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
/*
 * This file is licensed according to the BSD 3-clause license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the "Linz Center of Mechatronics GmbH" and "LCM" nor
 *       the names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL "Linz Center of Mechatronics GmbH" BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "beaglebone.h"
#include "uartStdio.h"
#include "pin_mux.h"
#include "inttypes.h"
#include "uart_irda_cir.h"

#include "interrupt.h"
#include "dmtimer.h"
#include "tsc_adc.h"
#include "hw_cm_per.h"
#include "hw_types.h"
#include "hw_cm_wkup.h"


#include "Target.h"
#include "GlobalDefines.h"
#include "Main.h"
#include "Hardware.h"


/* private prototypes */
static void ADCIsr();
static void StepConfigure(unsigned int, unsigned int, unsigned int);
void TSCADCModuleClkConfig(void);

extern void PWMSSTBClkEnable(unsigned int);
extern void PWMSSModuleClkConfig(unsigned int instanceNum);


/**
 * @brief Initialization of hardware.
 */
void initHardware(void)
{
    /*------------------------------------------------------------------------*/
    /** - Configuration of IO ports */
    /*------------------------------------------------------------------------*/
    /* GPIO module 1 */
	GPIO1ModuleClkConfig();
	GPIO1Pin23PinMuxSetup();
	GPIOModuleEnable(SOC_GPIO_1_REGS);
	GPIOModuleReset(SOC_GPIO_1_REGS);
	GPIODirModeSet(SOC_GPIO_1_REGS, 21, GPIO_DIR_OUTPUT);   /* LED */
	GPIODirModeSet(SOC_GPIO_1_REGS, 22, GPIO_DIR_OUTPUT);   /* LED */
	GPIODirModeSet(SOC_GPIO_1_REGS, 23, GPIO_DIR_OUTPUT);   /* LED */
	GPIODirModeSet(SOC_GPIO_1_REGS, 24, GPIO_DIR_OUTPUT);   /* LED */

    GpioPinMuxSetup(GPIO_1_12, PAD_FS_RXE_NA_PUPDD(7));     /* fast slew rate, receiver enable, no pull-up/down, mode 7 (GPIO) */
    GpioPinMuxSetup(GPIO_1_13, PAD_FS_RXD_NA_PUPDD(7));     /* fast slew rate, receiver disable, no pull-up/down, mode 7 (GPIO) */
    GpioPinMuxSetup(GPIO_1_14, PAD_FS_RXE_NA_PUPDD(7));     /* fast slew rate, receiver enable, no pull-up/down, mode 7 (GPIO) */
    GpioPinMuxSetup(GPIO_1_15, PAD_FS_RXD_NA_PUPDD(7));     /* fast slew rate, receiver disable, no pull-up/down, mode 7 (GPIO) */

	GPIODirModeSet(SOC_GPIO_1_REGS, 12, GPIO_DIR_INPUT);    /* GPIO_44: input */
	GPIODirModeSet(SOC_GPIO_1_REGS, 13, GPIO_DIR_OUTPUT);   /* GPIO_45: output */
	GPIODirModeSet(SOC_GPIO_1_REGS, 14, GPIO_DIR_INPUT);    /* GPIO_46: input */
	GPIODirModeSet(SOC_GPIO_1_REGS, 15, GPIO_DIR_OUTPUT);   /* GPIO_47: output */

	/* GPIO module 2 */
    GPIO2ModuleClkConfig();

    GpioPinMuxSetup(GPIO_2_2, PAD_FS_RXD_NA_PUPDD(7));  /* fast slew rate, receiver disable, no pull-up/down, mode 7 (GPIO) */
    GpioPinMuxSetup(GPIO_2_3, PAD_FS_RXE_NA_PUPDD(7));  /* fast slew rate, receiver enable, no pull-up/down, mode 7 (GPIO) */
    GpioPinMuxSetup(GPIO_2_4, PAD_FS_RXE_NA_PUPDD(7));  /* fast slew rate, receiver enable, no pull-up/down, mode 7 (GPIO) */
    GpioPinMuxSetup(GPIO_2_5, PAD_FS_RXD_NA_PUPDD(7));  /* fast slew rate, receiver disable, no pull-up/down, mode 7 (GPIO) */

    GPIOModuleEnable(SOC_GPIO_2_REGS);
    GPIOModuleReset(SOC_GPIO_2_REGS);
    GPIODirModeSet(SOC_GPIO_2_REGS, 2, GPIO_DIR_OUTPUT);    /* GPIO_66: output */
    GPIODirModeSet(SOC_GPIO_2_REGS, 3, GPIO_DIR_INPUT);     /* GPIO_67: input */
    GPIODirModeSet(SOC_GPIO_2_REGS, 4, GPIO_DIR_INPUT);     /* GPIO_68: input */
    GPIODirModeSet(SOC_GPIO_2_REGS, 5, GPIO_DIR_OUTPUT);    /* GPIO_69: output */


    /*------------------------------------------------------------------------*/
    /** - Configuration of PWM
     *    - Activation of modules 0, 1, 2
     *    - Frequency set to 20kHz
     *    - Center aligned mode
     *    - Active high complementary output mode
     *    - Dead band module activated, but delay is set to 0 by default
     *    .
     */
    /*------------------------------------------------------------------------*/
    /* EHRPWM module 0 */
    GpioPinMuxSetup(GPIO_0_2, PAD_FS_RXD_NA_PUPDD(3));  /* fast slew rate, receiver disable, no pull-up/down, mode 3 (PWM) */
    GpioPinMuxSetup(GPIO_0_3, PAD_FS_RXD_NA_PUPDD(3));  /* fast slew rate, receiver disable, no pull-up/down, mode 3 (PWM) */

    PWMSSModuleClkConfig(0);
    EHRPWMClockEnable(SOC_PWMSS0_REGS);
    EHRPWMTimebaseClkConfig(SOC_EPWM_0_REGS,TB_FREQUENCY,100000);
    EHRPWMPWMOpFreqSet(SOC_EPWM_0_REGS, TB_FREQUENCY, PWM_FREQUENCY, EHRPWM_COUNT_UP_DOWN, EHRPWM_SHADOW_WRITE_DISABLE);    /* set PWM frequency */
    EHRPWMTBEmulationModeSet(SOC_EPWM_0_REGS,EHRPWM_FREE_RUN);
    EHRPWMTimebaseSyncDisable(SOC_EPWM_0_REGS);                         /* no sync for first PWM module */
    EHRPWMSyncOutModeSet(SOC_EPWM_0_REGS, EHRPWM_SYNCOUT_COUNTER_EQUAL_ZERO);   /* synchronization pulse at CTR=0*/
    EHRPWMLoadCMPA(SOC_EPWM_0_REGS,0,EHRPWM_SHADOW_WRITE_DISABLE,0,1);  /* 0% duty = 0, 100% duty = 2500 */
    //EHRPWMLoadCMPB(SOC_EPWM_0_REGS,0,EHRPWM_SHADOW_WRITE_DISABLE,0,1);/* 0% duty = 0, 100% duty = 2500 */ /* not needed due to complementary mode! */
    EHRPWMConfigureAQActionOnA(SOC_EPWM_0_REGS,0,0,2,1,0,0,0);          /* set on CTR=CAUp, clear on CTR=CADown */
    //EHRPWMConfigureAQActionOnB(SOC_EPWM_0_REGS,0,0,0,0,2,1,0);        /* set on CTR=CBUp, clear on CTR=CBDown */ /* not needed due to complementary mode! */

    EHRPWMDBPolaritySelect(SOC_EPWM_0_REGS, EHRPWM_DBCTL_POLSEL_AHC);   /* active high complementary */
    EHRPWMDBOutput(SOC_EPWM_0_REGS, EHRPWM_DBCTL_OUT_MODE_AREDBFED);    /* enable rising and falling edge delay */
    EHRPWMDBConfigureRED(SOC_EPWM_0_REGS, RISING_EDGE_DELAY);           /* set rising edge delay */
    EHRPWMDBConfigureFED(SOC_EPWM_0_REGS, FALLING_EDGE_DELAY);          /* set falling edge delay */

    /* EHRPWM module 1 */
    GpioPinMuxSetup(GPIO_1_18, PAD_FS_RXD_NA_PUPDD(6));  /* fast slew rate, receiver disable, no pull-up/down, mode 6 (PWM) */
    GpioPinMuxSetup(GPIO_1_19, PAD_FS_RXD_NA_PUPDD(6));  /* fast slew rate, receiver disable, no pull-up/down, mode 6 (PWM) */

    PWMSSModuleClkConfig(1);
    EHRPWMClockEnable(SOC_PWMSS1_REGS);
    EHRPWMTimebaseClkConfig(SOC_EPWM_1_REGS,TB_FREQUENCY,100000);
    EHRPWMPWMOpFreqSet(SOC_EPWM_1_REGS, TB_FREQUENCY, PWM_FREQUENCY, EHRPWM_COUNT_UP_DOWN, EHRPWM_SHADOW_WRITE_DISABLE);    /* set PWM frequency */
    EHRPWMTBEmulationModeSet(SOC_EPWM_1_REGS,EHRPWM_FREE_RUN);
    EHRPWMTimebaseSyncEnable(SOC_EPWM_1_REGS,0,EHRPWM_COUNT_UP_AFTER_SYNC); /* sync with previous PWM module */
    EHRPWMSyncOutModeSet(SOC_EPWM_1_REGS, EHRPWM_SYNCOUT_SYNCIN);       /* pass through synchronization pulse */
    EHRPWMLoadCMPA(SOC_EPWM_1_REGS,0,EHRPWM_SHADOW_WRITE_DISABLE,0,1);  /* 0% duty = 0, 100% duty = 2500 */
    //EHRPWMLoadCMPB(SOC_EPWM_1_REGS,0,EHRPWM_SHADOW_WRITE_DISABLE,0,1);/* 0% duty = 0, 100% duty = 2500 */ /* not needed due to complementary mode! */
    EHRPWMConfigureAQActionOnA(SOC_EPWM_1_REGS,0,0,2,1,0,0,0);          /* set on CTR=CAUp, clear on CTR=CADown */
    //EHRPWMConfigureAQActionOnB(SOC_EPWM_1_REGS,0,0,0,0,2,1,0);        /* set on CTR=CBUp, clear on CTR=CBDown */ /* not needed due to complementary mode! */

    EHRPWMDBPolaritySelect(SOC_EPWM_1_REGS, EHRPWM_DBCTL_POLSEL_AHC);   /* active high complementary */
    EHRPWMDBOutput(SOC_EPWM_1_REGS, EHRPWM_DBCTL_OUT_MODE_AREDBFED);    /* enable rising and falling edge delay */
    EHRPWMDBConfigureRED(SOC_EPWM_1_REGS, RISING_EDGE_DELAY);           /* set rising edge delay */
    EHRPWMDBConfigureFED(SOC_EPWM_1_REGS, FALLING_EDGE_DELAY);          /* set falling edge delay */

    /* EHRPWM module 2 */
    GpioPinMuxSetup(GPIO_0_22, PAD_FS_RXD_NA_PUPDD(4));  /* fast slew rate, receiver disable, no pull-up/down, mode 4 (PWM) */
    GpioPinMuxSetup(GPIO_0_23, PAD_FS_RXD_NA_PUPDD(4));  /* fast slew rate, receiver disable, no pull-up/down, mode 4 (PWM) */

    PWMSSModuleClkConfig(2);
    EHRPWMClockEnable(SOC_PWMSS2_REGS);
    EHRPWMTimebaseClkConfig(SOC_EPWM_2_REGS,TB_FREQUENCY,100000);
    EHRPWMPWMOpFreqSet(SOC_EPWM_2_REGS, TB_FREQUENCY, PWM_FREQUENCY, EHRPWM_COUNT_UP_DOWN, EHRPWM_SHADOW_WRITE_DISABLE);    /* set PWM frequency */
    EHRPWMTBEmulationModeSet(SOC_EPWM_2_REGS,EHRPWM_FREE_RUN);
    EHRPWMTimebaseSyncEnable(SOC_EPWM_2_REGS,0,EHRPWM_COUNT_UP_AFTER_SYNC); /* sync with previous PWM module */
    EHRPWMSyncOutModeSet(SOC_EPWM_2_REGS, EHRPWM_SYNCOUT_SYNCIN);       /* pass through synchronization pulse */
    EHRPWMLoadCMPA(SOC_EPWM_2_REGS,0,EHRPWM_SHADOW_WRITE_DISABLE,0,1);  /* 0% duty = 0, 100% duty = 2500 */
    //EHRPWMLoadCMPB(SOC_EPWM_2_REGS,0,EHRPWM_SHADOW_WRITE_DISABLE,0,1);/* 0% duty = 0, 100% duty = 2500 */ /* not needed due to complementary mode! */
    EHRPWMConfigureAQActionOnA(SOC_EPWM_2_REGS,0,0,2,1,0,0,0);          /* set on CTR=CAUp, clear on CTR=CADown */
    //EHRPWMConfigureAQActionOnB(SOC_EPWM_2_REGS,0,0,0,0,2,1,0);        /* set on CTR=CBUp, clear on CTR=CBDown */ /* not needed due to complementary mode! */

    EHRPWMDBPolaritySelect(SOC_EPWM_2_REGS, EHRPWM_DBCTL_POLSEL_AHC);   /* active high complementary */
    EHRPWMDBOutput(SOC_EPWM_2_REGS, EHRPWM_DBCTL_OUT_MODE_AREDBFED);    /* enable rising and falling edge delay */
    EHRPWMDBConfigureRED(SOC_EPWM_2_REGS, RISING_EDGE_DELAY);           /* set rising edge delay */
    EHRPWMDBConfigureFED(SOC_EPWM_2_REGS, FALLING_EDGE_DELAY);          /* set falling edge delay */


    /*------------------------------------------------------------------------*/
    /** - Configuration of ADC
     *    - Activation of channels 0..6
     *    - 200kSamples/s
     *    - ADC is triggered by timer 4
     *    .
     */
    /*------------------------------------------------------------------------*/
    HWREG( SOC_CONTROL_REGS + CONTROL_CONF_AIN0) = CONTROL_CONF_AIN0_CONF_AIN0_RXACTIVE;
    HWREG( SOC_CONTROL_REGS + CONTROL_CONF_AIN1) = CONTROL_CONF_AIN1_CONF_AIN1_RXACTIVE;
    HWREG( SOC_CONTROL_REGS +  CONTROL_CONF_AIN2)= CONTROL_CONF_AIN2_CONF_AIN2_RXACTIVE;
    HWREG( SOC_CONTROL_REGS + CONTROL_CONF_AIN3) = CONTROL_CONF_AIN3_CONF_AIN3_RXACTIVE;
    HWREG( SOC_CONTROL_REGS + CONTROL_CONF_AIN4) = CONTROL_CONF_AIN4_CONF_AIN4_RXACTIVE;
    HWREG( SOC_CONTROL_REGS + CONTROL_CONF_AIN5) = CONTROL_CONF_AIN5_CONF_AIN5_RXACTIVE;
    HWREG( SOC_CONTROL_REGS + CONTROL_CONF_AIN6) = CONTROL_CONF_AIN6_CONF_AIN6_RXACTIVE;
    HWREG( SOC_CONTROL_REGS + CONTROL_CONF_VREFP)= CONTROL_CONF_VREFP_CONF_VREFP_RXACTIVE;
    HWREG( SOC_CONTROL_REGS +  CONTROL_CONF_VREFN)= CONTROL_CONF_VREFN_CONF_VREFN_RXACTIVE;

    /* Initialize the ARM Interrupt Controller */
    IntRegister(SYS_INT_ADC_TSC_GENINT, ADCIsr);
    IntPrioritySet(SYS_INT_ADC_TSC_GENINT, 0, AINTC_HOSTINT_ROUTE_IRQ);
    IntSystemEnable(SYS_INT_ADC_TSC_GENINT);

    /* Enable the clock for touch screen */
    TSCADCModuleClkConfig();

    /* Configures ADC to 3Mhz */
    TSCADCConfigureAFEClock(SOC_ADC_TSC_0_REGS, 24000000, 3000000);

    /* Disable Transistor bias */
    TSCADCTSTransistorConfig(SOC_ADC_TSC_0_REGS, TSCADC_TRANSISTOR_DISABLE);

    TSCADCStepIDTagConfig(SOC_ADC_TSC_0_REGS, 1);

    /* Disable Write Protection of Step Configuration regs*/
    TSCADCStepConfigProtectionDisable(SOC_ADC_TSC_0_REGS);

    /* Configure steps channel 1(AN0) - channel 7 (AN6)*/
    StepConfigure(0, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL1);
    StepConfigure(1, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL2);
    StepConfigure(2, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL3);
    StepConfigure(3, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL4);
    StepConfigure(4, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL5);
    StepConfigure(5, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL6);
    StepConfigure(6, TSCADC_FIFO_0, TSCADC_POSITIVE_INP_CHANNEL7);

    /* General purpose inputs */
    TSCADCTSModeConfig(SOC_ADC_TSC_0_REGS, TSCADC_GENERAL_PURPOSE_MODE);

    TSCADCConfigHWEventPrempt(SOC_ADC_TSC_0_REGS, 1);
    TSCADCHWEventMapSet(SOC_ADC_TSC_0_REGS, TSCADC_HW_INPUT_EVENT);
    HWREG(SOC_CONTROL_REGS + CONTROL_ADC_EVT_CAPT) = 1; /* Timer 4 as hardware event which triggers ADC */

    /* Enable step 1 */
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 1, 1);
    /* Enable step 2 */
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 2, 1);
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 3, 1);
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 4, 1);
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 5, 1);
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 6, 1);
    TSCADCConfigureStepEnable(SOC_ADC_TSC_0_REGS, 7, 1);

    /* Clear the status of all interrupts */
    TSCADCIntStatusClear(SOC_ADC_TSC_0_REGS, 0x7FF);

    /* End of sequence interrupt is enable */
    TSCADCEventInterruptEnable(SOC_ADC_TSC_0_REGS, TSCADC_END_OF_SEQUENCE_INT);

    /* Enable the TSC_ADC_SS module*/
    TSCADCModuleStateSet(SOC_ADC_TSC_0_REGS, TSCADC_MODULE_ENABLE);



    /*------------------------------------------------------------------------*/
    /** - Configuration of timer 4
     *    - 24MHz timer clock
     *    - Generation of cyclic interrupt with selected sample time
     *    - Interrupt calls X2C main task
     *    .
     */
    /*------------------------------------------------------------------------*/
    /* This function will enable clocks for the DMTimer4 instance */
    DMTimer4ModuleClkConfig();

    /* Load the counter with the initial count value */
    DMTimerCounterSet(SOC_DMTIMER_4_REGS, ADC_TRIGGER_RATE);

    /* Load the load register with the reload count value */
    DMTimerReloadSet(SOC_DMTIMER_4_REGS, ADC_TRIGGER_RATE);

    /* Configure the DMTimer for Auto-reload and compare mode */
    DMTimerModeConfigure(SOC_DMTIMER_4_REGS, DMTIMER_AUTORLD_NOCMP_ENABLE);

    /* Enable the DMTimer interrupts */
    DMTimerIntEnable(SOC_DMTIMER_4_REGS, DMTIMER_INT_OVF_EN_FLAG);


    /*------------------------------------------------------------------------*/
    /* Start timer and PWM */
    /*------------------------------------------------------------------------*/
    /* Start the DMTimer */
    DMTimerEnable(SOC_DMTIMER_4_REGS);
    /* Enable Timer Base Module Clock in control module */
    PWMSSTBClkEnable(0);
    PWMSSTBClkEnable(1);
    PWMSSTBClkEnable(2);

    /* Enable IRQ in CPSR */
    IntMasterIRQEnable();

}


/**
 * @brief ADC end of conversion interrupt service routine.
 *
 * Reads data from ADC buffer and calls X2C main task.
 */
static void ADCIsr()
{
    unsigned char i = 0;

    /** - Clear interrupt flags */
    TSCADCIntStatusClear(SOC_ADC_TSC_0_REGS, TSCADC_END_OF_SEQUENCE_INT);
    DMTimerIntStatusClear(SOC_DMTIMER_4_REGS, DMTIMER_INT_OVF_IT_FLAG);


    /** - Read ADC data */
    while(i < 7){
        /* Read data from fifo 0 */
        ADCBuffer[i] = TSCADCFIFOADCDataRead(SOC_ADC_TSC_0_REGS, TSCADC_FIFO_0);
        i++;
    }

    /** - Execute main control task */
    mainTask();

}


/**
 * @brief Sample step configuration for ADC module
 */
static void StepConfigure(unsigned int stepSel, unsigned int fifo,
                   unsigned int positiveInpChannel)
{
    /* Configure ADC to Single ended operation mode */
    TSCADCTSStepOperationModeControl(SOC_ADC_TSC_0_REGS,
                                  TSCADC_SINGLE_ENDED_OPER_MODE, stepSel);

    /* Configure step to select Channel, reference voltages */
    TSCADCTSStepConfig(SOC_ADC_TSC_0_REGS, stepSel, TSCADC_NEGATIVE_REF_VSSA,
                    positiveInpChannel, TSCADC_NEGATIVE_INP_ADCREFM, TSCADC_POSITIVE_REF_VDDA);

    /* Configure oversampling (not used)  */
//    TSCADCTSStepAverageConfig(SOC_ADC_TSC_0_REGS, stepSel,TSCADC_SIXTEEN_SAMPLES_AVG);

    /* XPPSW Pin is on, Which pull up the AN0 line*/
    TSCADCTSStepAnalogSupplyConfig(SOC_ADC_TSC_0_REGS, TSCADC_XPPSW_PIN_ON, TSCADC_XNPSW_PIN_OFF,
                                TSCADC_YPPSW_PIN_OFF, stepSel);

    /* XNNSW Pin is on, Which pull down the AN1 line*/
    TSCADCTSStepAnalogGroundConfig(SOC_ADC_TSC_0_REGS, TSCADC_XNNSW_PIN_ON, TSCADC_YPNSW_PIN_OFF,
                                TSCADC_YNNSW_PIN_OFF,  TSCADC_WPNSW_PIN_OFF, stepSel);

    /* select fifo 0 or 1*/
    TSCADCTSStepFIFOSelConfig(SOC_ADC_TSC_0_REGS, stepSel, fifo);

    /* Configure ADC to one short mode */
    TSCADCTSStepModeConfig(SOC_ADC_TSC_0_REGS, stepSel,  TSCADC_CONTINIOUS_HARDWARE_SYNC);
}


/**
 * @brief Clock configuration for touch-screen/ADC module
 */
void TSCADCModuleClkConfig(void)
{
    /* Configuring L3 Interface Clocks. */

    /* Writing to MODULEMODE field of CM_PER_L3_CLKCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) |=
          CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while(CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) &
           CM_PER_L3_CLKCTRL_MODULEMODE));

    /* Writing to MODULEMODE field of CM_PER_L3_INSTR_CLKCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) |=
          CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while(CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) &
           CM_PER_L3_INSTR_CLKCTRL_MODULEMODE));

    /* Writing to CLKTRCTRL field of CM_PER_L3_CLKSTCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) |=
          CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    /* Waiting for CLKTRCTRL field to reflect the written value. */
    while(CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) &
           CM_PER_L3_CLKSTCTRL_CLKTRCTRL));

    /* Writing to CLKTRCTRL field of CM_PER_OCPWP_L3_CLKSTCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) |=
          CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    /*Waiting for CLKTRCTRL field to reflect the written value. */
    while(CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
           CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL));

    /* Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register. */
    HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) |=
          CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    /*Waiting for CLKTRCTRL field to reflect the written value. */
    while(CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) &
           CM_PER_L3S_CLKSTCTRL_CLKTRCTRL));

    /* Checking fields for necessary values.  */

    /* Waiting for IDLEST field in CM_PER_L3_CLKCTRL register to be set to 0x0. */
    while((CM_PER_L3_CLKCTRL_IDLEST_FUNC << CM_PER_L3_CLKCTRL_IDLEST_SHIFT)!=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) & CM_PER_L3_CLKCTRL_IDLEST));

    /*
    ** Waiting for IDLEST field in CM_PER_L3_INSTR_CLKCTRL register to attain the
    ** desired value.
    */
    while((CM_PER_L3_INSTR_CLKCTRL_IDLEST_FUNC <<
           CM_PER_L3_INSTR_CLKCTRL_IDLEST_SHIFT)!=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) &
           CM_PER_L3_INSTR_CLKCTRL_IDLEST));

    /*
    ** Waiting for CLKACTIVITY_L3_GCLK field in CM_PER_L3_CLKSTCTRL register to
    ** attain the desired value.
    */
    while(CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) &
           CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));

    /*
    ** Waiting for CLKACTIVITY_OCPWP_L3_GCLK field in CM_PER_OCPWP_L3_CLKSTCTRL
    ** register to attain the desired value.
    */
    while(CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
           CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK));

    /*
    ** Waiting for CLKACTIVITY_L3S_GCLK field in CM_PER_L3S_CLKSTCTRL register
    ** to attain the desired value.
    */
    while(CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK !=
          (HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) &
          CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));


    /* Configuring registers related to Wake-Up region. */

    /* Writing to MODULEMODE field of CM_WKUP_CONTROL_CLKCTRL register. */
    HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CONTROL_CLKCTRL) |=
          CM_WKUP_CONTROL_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while(CM_WKUP_CONTROL_CLKCTRL_MODULEMODE_ENABLE !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CONTROL_CLKCTRL) &
           CM_WKUP_CONTROL_CLKCTRL_MODULEMODE));

    /* Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register. */
    HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) |=
          CM_WKUP_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    /*Waiting for CLKTRCTRL field to reflect the written value. */
    while(CM_WKUP_CLKSTCTRL_CLKTRCTRL_SW_WKUP !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) &
           CM_WKUP_CLKSTCTRL_CLKTRCTRL));

    /* Writing to CLKTRCTRL field of CM_L3_AON_CLKSTCTRL register. */
    HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L3_AON_CLKSTCTRL) |=
          CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    /*Waiting for CLKTRCTRL field to reflect the written value. */
    while(CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKTRCTRL_SW_WKUP !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L3_AON_CLKSTCTRL) &
           CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKTRCTRL));

    /* Writing to MODULEMODE field of CM_WKUP_TSC_CLKCTRL register. */
    HWREG(SOC_CM_WKUP_REGS + CM_WKUP_ADC_TSC_CLKCTRL) |=
          CM_WKUP_ADC_TSC_CLKCTRL_MODULEMODE_ENABLE;

    /* Waiting for MODULEMODE field to reflect the written value. */
    while(CM_WKUP_ADC_TSC_CLKCTRL_MODULEMODE_ENABLE !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_ADC_TSC_CLKCTRL) &
           CM_WKUP_ADC_TSC_CLKCTRL_MODULEMODE));

    /* Verifying if the other bits are set to required settings. */

    /*
    ** Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL register to attain
    ** desired value.
    */
    while((CM_WKUP_CONTROL_CLKCTRL_IDLEST_FUNC <<
           CM_WKUP_CONTROL_CLKCTRL_IDLEST_SHIFT) !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CONTROL_CLKCTRL) &
           CM_WKUP_CONTROL_CLKCTRL_IDLEST));

    /*
    ** Waiting for CLKACTIVITY_L3_AON_GCLK field in CM_L3_AON_CLKSTCTRL
    ** register to attain desired value.
    */
    while(CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKACTIVITY_L3_AON_GCLK !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L3_AON_CLKSTCTRL) &
           CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKACTIVITY_L3_AON_GCLK));

    /*
    ** Waiting for IDLEST field in CM_WKUP_L4WKUP_CLKCTRL register to attain
    ** desired value.
    */
    while((CM_WKUP_L4WKUP_CLKCTRL_IDLEST_FUNC <<
           CM_WKUP_L4WKUP_CLKCTRL_IDLEST_SHIFT) !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_L4WKUP_CLKCTRL) &
           CM_WKUP_L4WKUP_CLKCTRL_IDLEST));

    /*
    ** Waiting for CLKACTIVITY_L4_WKUP_GCLK field in CM_WKUP_CLKSTCTRL register
    ** to attain desired value.
    */
    while(CM_WKUP_CLKSTCTRL_CLKACTIVITY_L4_WKUP_GCLK !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) &
           CM_WKUP_CLKSTCTRL_CLKACTIVITY_L4_WKUP_GCLK));

    /*
    ** Waiting for CLKACTIVITY_L4_WKUP_AON_GCLK field in CM_L4_WKUP_AON_CLKSTCTRL
    ** register to attain desired value.
    */
    while(CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL_CLKACTIVITY_L4_WKUP_AON_GCLK !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL) &
           CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL_CLKACTIVITY_L4_WKUP_AON_GCLK));

    /*
    ** Waiting for CLKACTIVITY_ADC_FCLK field in CM_WKUP_CLKSTCTRL
    ** register to attain desired value.
    */
    while(CM_WKUP_CLKSTCTRL_CLKACTIVITY_ADC_FCLK !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) &
           CM_WKUP_CLKSTCTRL_CLKACTIVITY_ADC_FCLK));

    /*
    ** Waiting for IDLEST field in CM_WKUP_ADC_TSC_CLKCTRL register to attain
    ** desired value.
    */
    while((CM_WKUP_ADC_TSC_CLKCTRL_IDLEST_FUNC <<
           CM_WKUP_ADC_TSC_CLKCTRL_IDLEST_SHIFT) !=
          (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_ADC_TSC_CLKCTRL) &
           CM_WKUP_ADC_TSC_CLKCTRL_IDLEST));
}
