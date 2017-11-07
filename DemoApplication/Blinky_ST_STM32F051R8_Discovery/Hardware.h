/*
 * Hardware initialization.
 *
 * $LastChangedRevision: 609 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <stm32f0xx.h>
#include "SerialGeneric.h"

/* public prototypes */
void initHardware(void);
void initClock(void);
void initSerial(tSerial* serialSTM32F0);
void ADC1_COMP_IRQHandler(void);

/* resets watchdog timer */
#define KICK_DOG \
	do { \
		IWDG_ReloadCounter(); \
	} while (0)

#endif
