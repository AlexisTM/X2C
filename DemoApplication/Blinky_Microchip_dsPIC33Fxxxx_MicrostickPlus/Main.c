/* $LastChangedRevision: 1015 $
 * $LastChangedDate:: 2015-11-05 15:25:38 +0100 $
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

/* Demo application was tested with:
 *      Microstick Plus development board
 *      Microstick II
 *      dsPIC33FJ128MC802
 */
#include "TableStruct.h"
#include "LNet.h"
#include "Services.h"
#include "BlockServicesX2C.h"
#include "Hardware.h"
#include "Main.h"

#define SET_LED1        (LATBbits.LATB12 = 1)
#define CLEAR_LED1      (LATBbits.LATB12 = 0)
#define SET_LED2        (LATBbits.LATB13 = 1)
#define CLEAR_LED2      (LATBbits.LATB13 = 0)
#define SET_LED3        (LATBbits.LATB14 = 1)
#define CLEAR_LED3      (LATBbits.LATB14 = 0)
#define SET_LED4        (LATBbits.LATB15 = 1)
#define CLEAR_LED4      (LATBbits.LATB15 = 0)
#define READ_SW1        (PORTAbits.RA2)

/* used by init version info */
const struct {
	uint8 date[11];
	uint8 time[8];
} compilationDate = { __DATE__, __TIME__ };

/* X2C maintenance structure */
volatile tTableStruct TheTableStruct;
volatile tTableStruct *TableStruct = &TheTableStruct;

/* LNet protocol buffersize & node identifier */
#define LNET_BUFFERSIZE ((uint8)255)
#define LNET_NODEID ((uint8)1)

static tSerial interface;
static tLNet protocol;
static uint8 bufferLNet[LNET_BUFFERSIZE];

/* private prototypes */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion);

/** 
 * @brief Main function.
 * 
 * @return The main function will never return due to the never ending loop.
 */
int main(void)
{
    /** - initialize "integrated monitor":
     *    - configuration of LNet protocol:
     *      - Node-ID: 1
     *      - Buffer size: 255
     *      .
     *    .
     *  - initialize serial interface
     */
    initTableStruct();
    initSerialGeneric(&interface);
    initLNet(&protocol, bufferLNet, LNET_BUFFERSIZE, LNET_NODEID);
    initServiceTable((tProtocol*)&protocol);
    addCoreServices((tProtocol*)&protocol);
    addBlockServices((tProtocol*)&protocol);
    addTableStructProtocol((tProtocol*)&protocol);
    linkSerial((tProtocol*)&protocol, &interface);
    initSerial(&interface);
    TableStruct->DSPState = PRG_LOADED_STATE;

    initVersionInfo(TableStruct, (uint16)0x0002);   /* software version 2 */
    TableStruct->TFncTable = blockFunctionTable;
    TableStruct->TParamTable = parameterIdTable;

    /** - initialize hardware */
    initHardware();
    KICK_DOG;

    /** - initialize X2C */
    X2C_Init();
    KICK_DOG;

    /** - never ending loop -> interrupt driven algorithm */
    while (1)
    {
        /* serial communication */
        protocol.pCommunicate((tProtocol*)&protocol);
    }
    return (0);
}

/** 
 * @brief Main control task.
 * 
 * Calling rate = 100us
 */
void mainTask(void)
{
    /*------------------------------------------------------------------------*/
    /** - assign inports */
    /*------------------------------------------------------------------------*/
    /* digital inputs */
    if (READ_SW1 != 0) {
        Inports.Switch1 = 0;
    } else {
        Inports.Switch1 = INT16_MAX;
    }
    /* analog inputs */
    Inports.Potentiometer = ADC1BUF0 << 5;   /* 10bit to 15bit (Q15 format)*/
    /* encoder */
    Inports.Encoder = POS1CNT;

    /*------------------------------------------------------------------------*/
    /** - update X2C */
    /*------------------------------------------------------------------------*/
    X2C_Update();

    /*------------------------------------------------------------------------*/
    /** - update outports */
    /*------------------------------------------------------------------------*/
    /* LEDs */
    if (*Outports.pLED_red1 != 0) {
        SET_LED1;
    } else {
        CLEAR_LED1;
    }
    if (*Outports.pLED_red2 != 0) {
        SET_LED2;
    } else {
        CLEAR_LED2;
    }
    if (*Outports.pLED_blue1 != 0) {
        SET_LED3;
    } else {
        CLEAR_LED3;
    }
    if (*Outports.pLED_blue2 > (INT16_MAX>>1)) {
        SET_LED4;
    } else {
        CLEAR_LED4;
    }
    /* piezo buzzer */
    OC1RS = ((int32)(*Outports.pPiezo) * (int32)PWM_FREQUENCY) >> 15;

    /* kick watchdog */
    KICK_DOG;
}

/**
 * @brief Routine to set version.
 * 
 * @param tblStruct X2C maintenance structure.
 * @param appVersion Version number.
 */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion)
{
	tblStruct->framePrgVersion = appVersion;
	tblStruct->framePrgCompDateTime = (uint8*)&compilationDate;
}
