/*
 * $LastChangedRevision: 1069 $
 * $LastChangedDate:: 2016-12-23 15:05:57 +0100#$
 *
 * Copyright (c) 2016, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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
#include "dmtimer.h"
#include "interrupt.h"

#include "Target.h"
#include "Main.h"
#include "Hardware.h"

/*
 * Sample times @ timer clock = 24 MHz.
 */
#define SAMPLETIME_100US (2400)
#define SAMPLETIME_50US (1200)
#define SAMPLETIME_20US (480)
#define SAMPLETIME_10US (240)

/** Sample time */
#define SELECTED_SAMPLETIME		SAMPLETIME_100US

#define TIMER_INITIAL_COUNT ((uint32)0xFFFFFFFF - SELECTED_SAMPLETIME)
#define TIMER_RLD_COUNT ((uint32)0xFFFFFFFF - SELECTED_SAMPLETIME)

/* private prototypes */
static void setupTimer(void);
static void DMTimerIsr(void);

/**
 * @brief Initialization of hardware.
 */
void initHardware(void)
{
    /*------------------------------------------------------------------------*/
    /** - Configuration of IO ports */
    /*------------------------------------------------------------------------*/
	GPIO1ModuleClkConfig();
	GPIO1Pin23PinMuxSetup();
	GPIOModuleEnable(SOC_GPIO_1_REGS);
	GPIOModuleReset(SOC_GPIO_1_REGS);
	GPIODirModeSet(SOC_GPIO_1_REGS, 21, GPIO_DIR_OUTPUT);
	GPIODirModeSet(SOC_GPIO_1_REGS, 22, GPIO_DIR_OUTPUT);
	GPIODirModeSet(SOC_GPIO_1_REGS, 23, GPIO_DIR_OUTPUT);
	GPIODirModeSet(SOC_GPIO_1_REGS, 24, GPIO_DIR_OUTPUT);

    /*------------------------------------------------------------------------*/
    /** - Configuration of timer 2
     *    - 24MHz timer clock
     *    - Generation of cyclic interrupt with selected sample time
     *    - Interrupt calls X2C main task
     *    .
     */
    /*------------------------------------------------------------------------*/
    setupTimer();

    /* Enable IRQ in CPSR */
    IntMasterIRQEnable();

    /* Registering DMTimerIsr */
    IntRegister(SYS_INT_TINT2, DMTimerIsr);

    /* Set the priority */
    IntPrioritySet(SYS_INT_TINT2, 0, AINTC_HOSTINT_ROUTE_IRQ);

    /* Enable the system interrupt */
    IntSystemEnable(SYS_INT_TINT2);

    /* Start the DMTimer */
    DMTimerEnable(SOC_DMTIMER_2_REGS);

    /* Start the DMTimer */
    DMTimerEnable(SOC_DMTIMER_2_REGS);
}

static void setupTimer(void)
{
    /* This function will enable clocks for the DMTimer2 instance */
    DMTimer2ModuleClkConfig();

    /* Load the counter with the initial count value */
    DMTimerCounterSet(SOC_DMTIMER_2_REGS, TIMER_INITIAL_COUNT);

    /* Load the load register with the reload count value */
    DMTimerReloadSet(SOC_DMTIMER_2_REGS, TIMER_RLD_COUNT);

    /* Configure the DMTimer for Auto-reload and compare mode */
    DMTimerModeConfigure(SOC_DMTIMER_2_REGS, DMTIMER_AUTORLD_NOCMP_ENABLE);

    /* Enable the DMTimer interrupts */
    DMTimerIntEnable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);
}

static void DMTimerIsr(void)
{
    /* Disable the DMTimer interrupts */
//    DMTimerIntDisable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);

    /* Clear the status of the interrupt flags */
    DMTimerIntStatusClear(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_IT_FLAG);

    mainTask();

    /* Enable the DMTimer interrupts */
//    DMTimerIntEnable(SOC_DMTIMER_2_REGS, DMTIMER_INT_OVF_EN_FLAG);
}
