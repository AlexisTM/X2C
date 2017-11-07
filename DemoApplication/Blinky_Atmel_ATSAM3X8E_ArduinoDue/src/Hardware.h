/**
 * @file
 * @brief Hardware configuration
 *
 * Configuration:
 * - center aligned PWM, 10 kHz
 * - ADC being automatically started (by hardware) on every PWM period
 * - ADC complete interrupt executes X2C Update function
 * - LED 'L' (digital output #13) blink frequency can be controlled by X2C block 'Frequency'
 * - UART configuration using 115200/8/N/1 for X2C communication
 *
 * Uses Atmel ASF functions.
 */
/*
 * $LastChangedRevision: 833 $
 * $LastChangedDate:: 2015-12-15 18:11:05 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "Target.h"

/* public prototypes */
void initHardware(void);
void initSerial(tSerial* serial);

#define resetWatchdog() do { \
	; \
} while (0)

#define BLINKY_LED_ON (gpio_set_pin_high(PIO_PB27_IDX))
#define BLINKY_LED_OFF (gpio_set_pin_low(PIO_PB27_IDX))

#endif /* __HARDWARE_H__ */
