/**
 * @file
 * @brief Hardware initialization.
 */
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
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "gpio_v2.h"
#include "bl_platform.h"

/* public prototypes */
void initHardware(void);


#define USER_LED0_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 21, GPIO_PIN_HIGH)
#define USER_LED0_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 21, GPIO_PIN_LOW)
#define USER_LED1_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 22, GPIO_PIN_HIGH)
#define USER_LED1_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 22, GPIO_PIN_LOW)
#define USER_LED2_ON	GPIOPinWrite(SOC_GPIO_1_REGS, 23, GPIO_PIN_HIGH)
#define USER_LED2_OFF	GPIOPinWrite(SOC_GPIO_1_REGS, 23, GPIO_PIN_LOW)
#define USER_LED3_ON    GPIOPinWrite(SOC_GPIO_1_REGS, 24, GPIO_PIN_HIGH)
#define USER_LED3_OFF   GPIOPinWrite(SOC_GPIO_1_REGS, 24, GPIO_PIN_LOW)

#endif
