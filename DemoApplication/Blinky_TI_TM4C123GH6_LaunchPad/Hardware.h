/**
 * @file
 * @brief Hardware configuration.
 */
/*
 * $LastChangedRevision: 1013 $
 * $LastChangedDate:: 2016-03-04 13:14:00 +0100#$
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

#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "driverlib/watchdog.h"
#include "SerialGeneric.h"

/* public prototypes */
void initHardware(void);
void initSerial(tSerial* serial);

#define LED_RED_ON  (GPIO_PORTF_DATA_R |= 0x02)
#define LED_RED_OFF (GPIO_PORTF_DATA_R &= (~0x02))
#define LED_GREEN_ON  (GPIO_PORTF_DATA_R |= 0x08)
#define LED_GREEN_OFF (GPIO_PORTF_DATA_R &= (~0x08))
#define LED_BLUE_ON  (GPIO_PORTF_DATA_R |= 0x04)
#define LED_BLUE_OFF (GPIO_PORTF_DATA_R &= (~0x04))
#define SWITCH1		(uint8)0x10
#define SWITCH2		(uint8)0x01

#define KICK_DOG \
    do { \
    	ROM_WatchdogUnlock(WATCHDOG0_BASE); \
    	ROM_WatchdogReloadSet(WATCHDOG0_BASE, (uint32)400000); \
    	ROM_WatchdogLock(WATCHDOG0_BASE); \
    } while(0)

#endif
