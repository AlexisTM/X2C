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
#include "GlobalDefines.h"
#include "OutputControl.h"

/* private macros */
#define CALC_DUTY_CYCLE(val) (val * (TB_FREQUENCY/PWM_FREQUENCY/2/100))   /* @fPWM=20kHz: 0% duty = 0, 100% duty = 2500 */



/**
 * @brief Routine to set PWM duty cycle.
 */
void setPWM(void)
{
    float32 DutyCycle0, DutyCycle1, DutyCycle2;

    DutyCycle0 = *(Outports.pP9_21_22);
    DutyCycle1 = *(Outports.pP9_14_16);
    DutyCycle2 = *(Outports.pP8_13_19);

    /** - check range of duty cycle */
    if (DutyCycle0 > 100.0 )
    {
        DutyCycle0 = 100.0;
    }
    else if (DutyCycle0 < 0.0 )
    {
        DutyCycle0 = 0.0;
    }

    if (DutyCycle1 > 100.0 )
    {
        DutyCycle0 = 100.0;
    }
    else if (DutyCycle1 < 0.0 )
    {
        DutyCycle1 = 0.0;
    }
    if (DutyCycle2 > 100.0 )
    {
        DutyCycle2 = 100.0;
    }
    else if (DutyCycle2 < 0.0 )
    {
        DutyCycle2 = 0.0;
    }

    /** - set duty cycle in PWM module */
    EHRPWMLoadCMPA(SOC_EPWM_0_REGS, CALC_DUTY_CYCLE(DutyCycle0), EHRPWM_SHADOW_WRITE_DISABLE, 0, 1);
    EHRPWMLoadCMPA(SOC_EPWM_1_REGS, CALC_DUTY_CYCLE(DutyCycle1), EHRPWM_SHADOW_WRITE_DISABLE, 0, 1);
    EHRPWMLoadCMPA(SOC_EPWM_2_REGS, CALC_DUTY_CYCLE(DutyCycle2), EHRPWM_SHADOW_WRITE_DISABLE, 0, 1);
}


/**
 * @brief Routine to write to digital output pins.
 */
void writeDigitalOut(void)
{

    /** - LEDs */
    if (USER_LED0 > 0)
    {
        USER_LED0_ON;
    }
    else
    {
        USER_LED0_OFF;
    }
    if (USER_LED1 > 0)
    {
        USER_LED1_ON;
    }
    else
    {
        USER_LED1_OFF;
    }
    if (USER_LED2 > 0)
    {
        USER_LED2_ON;
    }
    else
    {
        USER_LED2_OFF;
    }
    if (USER_LED3 > 0)
    {
        USER_LED3_ON;
    }
    else
    {
        USER_LED3_OFF;
    }

    /** - General purpose outputs */
    if (*(Outports.pP8_11) > 0)
    {
        GPIO_1_13_ON;
    }
    else
    {
        GPIO_1_13_OFF;
    }
    if (*(Outports.pP8_15) > 0)
    {
        GPIO_1_15_ON;
    }
    else
    {
        GPIO_1_15_OFF;
    }
    if (*(Outports.pP8_7) > 0)
    {
        GPIO_2_2_ON;
    }
    else
    {
        GPIO_2_2_OFF;
    }
    if (*(Outports.pP8_9) > 0)
    {
        GPIO_2_5_ON;
    }
    else
    {
        GPIO_2_5_OFF;
    }

}
