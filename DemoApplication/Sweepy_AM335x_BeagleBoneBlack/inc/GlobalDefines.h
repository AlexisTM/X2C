/**
 * @file
 * @brief Collection of globally needed defines.
 *
 * Available Preprocessor Definitions:
 * - none
 * .
 */
/*
 * $LastChangedRevision: 1078 $
 * $LastChangedDate:: 2017-01-16 16:51:39 +0100#$
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
#ifndef GLOBALDEFINES_H
	#define GLOBALDEFINES_H
	
	#include "Target.h"
	#include "../X2CCode/X2C.h"

    #include "soc_AM335x.h"
    #include "gpio_v2.h"
    #include "ehrpwm.h"


	/*------------------------------------------------------------------------*/
	/** @name X2C Outports
	  * @{ */
	/*------------------------------------------------------------------------*/
	#define USER_LED0		(*Outports.pLED0)		/* User LED 0 */
	#define USER_LED1		(*Outports.pLED1)		/* User LED 1 */
	#define USER_LED2		(*Outports.pLED2)		/* User LED 2 */
    #define USER_LED3       (*Outports.pLED2)       /* User LED 2 */
	/** @} */


	/*------------------------------------------------------------------------*/
	/** @name X2C Inports
	  * @{ */
	/*------------------------------------------------------------------------*/
	#define AIN0			(Inports.P9_39)		    /* Analog input 0 */
	#define AIN1			(Inports.P9_40)		    /* Analog input 1 */
	#define AIN2			(Inports.P9_37)		    /* Analog input 2 */
	#define AIN3			(Inports.P9_38)		    /* Analog input 3 */
	#define AIN4			(Inports.P9_33)		    /* Analog input 4 */
    #define AIN5            (Inports.P9_36)         /* Analog input 5 */
    #define AIN6            (Inports.P9_35)         /* Analog input 6 */
    /** @} */



    /*------------------------------------------------------------------------*/
    /* Sample time and PWM frequency */
    /*------------------------------------------------------------------------*/
    /*
     * Sample times @ timer clock = 24 MHz.
     */
    #define SAMPLETIME_200US    (4800)
    #define SAMPLETIME_100US    (2400)
    #define SAMPLETIME_50US     (1200)

    /*
     * PWM frequencies
     */
    #define PWM_10KHZ   (10)
    #define PWM_20KHZ   (20)

    /* TODO: PLEASE SELECT YOUR DESIRED SAMPLE TIME! */
    /** Sample time */
    #define SELECTED_SAMPLETIME     SAMPLETIME_100US


    /* TODO: PLEASE SELECT YOUR DESIRED PWM FREQUENCY! */
    /** PWM frequency */
    #define PWM_FREQUENCY       PWM_20KHZ      /* fPWM = 20kHz */

    /* PWM/ADC related macros */
    #define TB_FREQUENCY        100000 /* time base clock */
    #define RISING_EDGE_DELAY   0      /* no rising edge delay */
    #define FALLING_EDGE_DELAY  0      /* no falling edge delay */
    #define ADC_TRIGGER_RATE    ((uint32)0xFFFFFFFF - SELECTED_SAMPLETIME)  /* trigger ADC with the selected sample time */


    /*------------------------------------------------------------------------*/
    /** @name Port Pin Definitions
     * @{ */
    /*------------------------------------------------------------------------*/
    #define USER_LED0_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 21, GPIO_PIN_HIGH)
    #define USER_LED0_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 21, GPIO_PIN_LOW)
    #define USER_LED1_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 22, GPIO_PIN_HIGH)
    #define USER_LED1_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 22, GPIO_PIN_LOW)
    #define USER_LED2_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 23, GPIO_PIN_HIGH)
    #define USER_LED2_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 23, GPIO_PIN_LOW)
    #define USER_LED3_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 24, GPIO_PIN_HIGH)
    #define USER_LED3_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 24, GPIO_PIN_LOW)

    #define GPIO_1_13_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 13, GPIO_PIN_HIGH)
    #define GPIO_1_13_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 13, GPIO_PIN_LOW)
    #define GPIO_1_15_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 15, GPIO_PIN_HIGH)
    #define GPIO_1_15_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 15, GPIO_PIN_LOW)
    #define GPIO_2_2_ON     GPIOPinWrite(SOC_GPIO_2_REGS, 2, GPIO_PIN_HIGH)
    #define GPIO_2_2_OFF    GPIOPinWrite(SOC_GPIO_2_REGS, 2, GPIO_PIN_LOW)
    #define GPIO_2_5_ON     GPIOPinWrite(SOC_GPIO_2_REGS, 5, GPIO_PIN_HIGH)
    #define GPIO_2_5_OFF    GPIOPinWrite(SOC_GPIO_2_REGS, 5, GPIO_PIN_LOW)

    #define READ_GPIO_1_12  GPIOPinRead(SOC_GPIO_1_REGS, 12)
    #define READ_GPIO_1_14  GPIOPinRead(SOC_GPIO_1_REGS, 14)
    #define READ_GPIO_2_3   GPIOPinRead(SOC_GPIO_2_REGS, 3)
    #define READ_GPIO_2_4   GPIOPinRead(SOC_GPIO_2_REGS, 4)
    /** @} */


	/*------------------------------------------------------------------------*/
	/* CPU Load Measurement Macros */
	/*------------------------------------------------------------------------*/
//	#define START_CPU_MEASUREMENT	(CpuTimer2Regs.TIM.all = 0x0000U)
//	#define END_CPU_MEASUREMENT		(CPU_Load  = 0xFFFFU - CpuTimer2Regs.TIM.all)


	/*------------------------------------------------------------------------*/
	/* Global Variables */
	/*------------------------------------------------------------------------*/
    extern unsigned int ADCBuffer[7];   /* ADC conversion results */

	extern uint16 CPU_Load;				/* CPU load */
	extern uint16 CPU_Scale;			/* CPU load scale factor (equals 100%) */

#endif
