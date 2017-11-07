/**
 * @file
 * @brief Extended lwIP configuration.
 * 
 * Modified lwiplib from TI StarterWare to support hostname configuration.
 * Requires lwIP 1.4.0.
 */
/*
 * $LastChangedRevision: 1084 $
 * $LastChangedDate:: 2017-01-23 15:01:40 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __LWIPLIBHOSTNAME_H__
#define __LWIPLIBHOSTNAME_H__

#include "Target.h"
#include "lwiplib.h"

/* public prototypes */
uint32 lwIPInitHostname(LWIP_IF *lwipIf, char* hostname);

#endif
