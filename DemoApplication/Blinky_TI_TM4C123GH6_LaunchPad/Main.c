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

#include <stdint.h>
#include "CommonFcts.h"
#include "TableStruct.h"
#include "LNet.h"
#include "Services.h"
#include "BlockServicesX2C.h"
#include "CommonFcts.h"
#include "Hardware.h"
#include "X2C.h"
#include "Main.h"

/* X2C maintenance structure */
volatile tTableStruct TheTableStruct;
volatile tTableStruct* TableStruct = &TheTableStruct;

/* LNet protocol buffersize & node identifier */
#define LNET_BUFFERSIZE ((uint8)255)
#define LNET_NODEID ((uint8)1)

static tSerial interface;
static tLNet protocol;
static uint8 bufferLNet[LNET_BUFFERSIZE];

/* used by init version info */
const struct {
	uint8 date[11];
	uint8 time[8];
} compilationDate = { __DATE__, __TIME__ };

/* private prototypes */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion);


/**
 * @brief Main function.
 *
 * The main function will never end due to the never ending loop.
 */
void main(void)
{
    /** - Initialize "integrated monitor":
     *    - configuration of LNet protocol:
     *      - Node-ID: 1
     *      - Buffer size: 255
     *      .
     *    .
     *  - Initialize serial interface
     */
    initTableStruct();
    initSerialGeneric(&interface);
    initSerial(&interface);
    initLNet(&protocol, bufferLNet, LNET_BUFFERSIZE, LNET_NODEID);
    initServiceTable((tProtocol*)&protocol);
    addCoreServices((tProtocol*)&protocol);
    addBlockServices((tProtocol*)&protocol);
    addTableStructProtocol((tProtocol*)&protocol);
    linkSerial((tProtocol*)&protocol, &interface);

	initVersionInfo(TableStruct, (uint16)0x0001);	/* software version 1 */
	TableStruct->DSPState = PRG_LOADED_STATE;

    TableStruct->TFncTable = blockFunctionTable;
    TableStruct->TParamTable = parameterIdTable;

    /** - Initialize hardware */
	initHardware();
	KICK_DOG;

	/** - Initialize X2C */
    X2C_Init();
    KICK_DOG;

    /** - Initialize LEDs */
    LED_BLUE_OFF;
    LED_GREEN_OFF;
    LED_RED_OFF;

    /** - Never ending loop -> interrupt driven algorithm */
    while(1)
	{
		/* communication procedure */
		protocol.pCommunicate((tProtocol*)&protocol);
	}
}


/**
 * @brief Main control task.
 *
 * The main control task is called by the timer 0 interrupt service
 * routine with a frequency of 5kHz.
 */
void mainTask(void)
{
    static int16 cnt = 0;

    /** - Assign inports */
    Inports.Cnt = cnt++;

    /* check buttons */
    if((ROM_GPIOPinRead(GPIO_PORTF_BASE, SWITCH1)&SWITCH1) == 0){	/* SW1 pressed */
    	Inports.Switch1 = INT16_MAX;
    }else{
    	Inports.Switch1 = 0;
    }

    if((ROM_GPIOPinRead(GPIO_PORTF_BASE, SWITCH2)&SWITCH2) == 0){	/* SW2 pressed */
    	Inports.Switch2 = INT16_MAX;
    }else{
    	Inports.Switch2 = 0;
    }

    /** - Update X2C */
    X2C_Update();

    /**  - Update outports */
    if (*Outports.pLED_red > 0) {
        LED_RED_ON;
    } else {
        LED_RED_OFF;
    }

    if (*Outports.pLED_green > 0) {
        LED_GREEN_ON;
    } else {
        LED_GREEN_OFF;
    }

    if (*Outports.pLED_blue > 0) {
        LED_BLUE_ON;
    } else {
        LED_BLUE_OFF;
    }


    /* reset watchdog timer */
    KICK_DOG;
}


/**
 * @brief Adds frame compilation date, time and version info to X2C maintenance structure.
 *
 * @param tblStruct		X2C maintenance structure
 * @param appVersion	Software version number
 */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion)
{
	tblStruct->framePrgVersion = appVersion;
	tblStruct->framePrgCompDateTime = (uint8*)&compilationDate;
}
