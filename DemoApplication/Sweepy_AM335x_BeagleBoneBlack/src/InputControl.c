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
#include "InputControl.h"

/* private macros */
#define ADC_SCALE   4.3956043956043956043956043956044e-4    /* 1.8V/(2^12-1) */


/**
 * @brief Routine to read values from ADC.
 */
void readAnalogIn(void)
{
    AIN0 = ADCBuffer[0] * ADC_SCALE;
    AIN1 = ADCBuffer[1] * ADC_SCALE;
    AIN2 = ADCBuffer[2] * ADC_SCALE;
    AIN3 = ADCBuffer[3] * ADC_SCALE;
    AIN4 = ADCBuffer[4] * ADC_SCALE;
    AIN5 = ADCBuffer[5] * ADC_SCALE;
    AIN6 = ADCBuffer[6] * ADC_SCALE;
}


/**
 * @brief Routine to read digital input pins.
 */
void readDigitalIn(void)
{
    if (READ_GPIO_2_3 != 0)
    {
        Inports.P8_8 = 1.0;
    }

    if (READ_GPIO_2_4 != 0)
    {
        Inports.P8_10 = 1.0;
    }

    if (READ_GPIO_1_12 != 0)
    {
        Inports.P8_12 = 1.0;
    }

    if (READ_GPIO_1_14 != 0)
    {
        Inports.P8_16 = 1.0;
    }
}
