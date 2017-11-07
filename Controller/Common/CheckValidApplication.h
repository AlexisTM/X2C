/**
 * @file
 * @brief Checks reset state
 */
/*
 * $LastChangedRevision: 824 $
 * $LastChangedDate:: 2015-11-26 15:56:03 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __CHECKVALIDAPPLICATION_H__
#define __CHECKVALIDAPPLICATION_H__

#include "Target.h"
#include "TableStruct.h"

/* maximum watchdogs reset after propgram stays in monitor */
#define MAX_WATCHDOG_RESTS ((int16)10)

/* public prototypes */
void boot(void);
uint8 checkValidApplication(void);

#endif
