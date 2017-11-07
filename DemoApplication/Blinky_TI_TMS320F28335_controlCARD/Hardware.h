/*
 * Hardware configuration.
 *
 * $LastChangedRevision: 541 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <DSP2833x_Device.h>
#include "SerialGeneric.h"

/* public prototypes */
void initHardware(void);
void initSerial(tSerial* serial);
void initInterruptVector(void);
void initFlash(void);

/* resets watchdog timer */
#define KICK_DOG \
	do { \
		EALLOW; \
		SysCtrlRegs.WDKEY = (uint16)0x0055; \
		SysCtrlRegs.WDKEY = (uint16)0x00AA; \
		EDIS; \
	} while (0)

#endif
