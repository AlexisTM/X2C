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
#include "uartStdio.h"
#include "bl.h"
#include "MMUConfig.h"

#include "TcpIp_lwIP_BeagleBoneBlack.h"
#include "LNet.h"
#include "VersionInfo.h"
#include "TableStruct.h"
#include "Services.h"
#include "BlockServicesX2C.h"

#include "X2CCode/X2C.h"
#include "Hardware.h"
#include "Main.h"

#define RX_BUF_SIZE (16*1024)
#define TX_BUF_SIZE (16*1024)

#define LNET_BUF_SIZE (255)

/**
 * IPv4 address (byte1.byte2.byte3.byte4)
 * Set all bytes to 0 for DHCP -> else static.
 */
#define IP_BYTE1	0
#define IP_BYTE2	0
#define IP_BYTE3	0
#define IP_BYTE4	0
/**
 * TCP port.
 */
#define TCP_PORT ((uint16)12666)
/**
 * Host name.
 */
#define HOSTNAME ((char*)"bbb-demo")


#define IP_ADDRESS (((uint32)(IP_BYTE1)<<24)|((uint32)(IP_BYTE2)<<16)|((uint32)(IP_BYTE3)<<8)|(uint32)IP_BYTE4)

static tTcpIp tcpip;
static uint8 rxBuffer[RX_BUF_SIZE];
static uint8 txBuffer[TX_BUF_SIZE];

static tLNet lnet;
static uint8 lnetBuffer[LNET_BUF_SIZE];

volatile tTableStruct TheTableStruct;
volatile tTableStruct* TableStruct = &TheTableStruct;

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
 * @return The main function will never return due to the never ending loop.
 */
int main(void)
{
	uint32 assignedIpAddr;

	MMUConfigAndEnable();

    /** - initialize UART as debug output:
     *    - Baudrate: 115200 Bit/s
     *    - Data bytes: 8
     *    - Parity: none
     *    - Stop bytes 1
     *    .
     */
	ConsoleUtilsInit();
	ConsoleUtilsSetType(CONSOLE_UART);

    /** - initialize "integrated monitor":
     *    - configuration of LNet protocol:
     *      - Node-ID: 1
     *      - Buffer size: 255
     *      .
     *    .
     *  - initialize TCP/IP interface:
     *    - IP address: via DHCP
     *    - Port: 12666
     *    - Hostname: "bbb-demo"
     *    .
     */
    initTableStruct();
    assignedIpAddr = initTcpIp(&tcpip, IP_ADDRESS, TCP_PORT, HOSTNAME, rxBuffer, RX_BUF_SIZE, txBuffer, TX_BUF_SIZE);
    if (assignedIpAddr > 0)
    {
    	uint8 ipv4Bytes[4];

    	ipv4Bytes[0] = (uint8)(assignedIpAddr >> 24);
    	ipv4Bytes[1] = (uint8)(assignedIpAddr >> 16);
    	ipv4Bytes[2] = (uint8)(assignedIpAddr >> 8);
    	ipv4Bytes[3] = (uint8)(assignedIpAddr & 0xFF);

    	ConsoleUtilsPrintf("\n*** NETWORK CONFIG ***");
    	ConsoleUtilsPrintf("\nIP address: %d.%d.%d.%d\n", \
    			ipv4Bytes[3], ipv4Bytes[2], ipv4Bytes[1], ipv4Bytes[0]);
    	ConsoleUtilsPrintf("Hostname: %s\n", HOSTNAME);
    }
    initLNet(&lnet, lnetBuffer, LNET_BUF_SIZE, (uint8)1);
    initServiceTable((tProtocol*)&lnet);
    addCoreServices((tProtocol*)&lnet);
    addBlockServices((tProtocol*)&lnet);
    addTableStructProtocol((tProtocol*)&lnet);

    linkTcpIp((tProtocol*)&lnet, &tcpip);

    initVersionInfo(TableStruct, (uint16)0x0002);   /* software version 2 */
    TableStruct->DSPState = PRG_LOADED_STATE;

    TableStruct->TFncTable = blockFunctionTable;
    TableStruct->TParamTable = parameterIdTable;

    /** - initialize X2C */
    X2C_Init();

    /** - initialize hardware */
    initHardware();

    /** - never ending loop -> interrupt driven algorithm */
    while (1)
    {
		/* communication procedure */
		lnet.pCommunicate((tProtocol*)&lnet);
    }
}

/**
 * @brief Adds frame compilation date, time and version info to X2C maintenance structure.
 */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion)
{
	tblStruct->framePrgVersion = appVersion;
	tblStruct->framePrgCompDateTime = (uint8*)&compilationDate;
}


/**
 * @brief Main control task.
 *
 * TODO: This task has to be called periodically.
 * Calling rate = 100us
 */
void mainTask(void)
{
    /*------------------------------------------------------------------------*/
    /** - assign inports (not available in this demo) */
    /*------------------------------------------------------------------------*/

    /*------------------------------------------------------------------------*/
    /** - update X2C */
    /*------------------------------------------------------------------------*/
	X2C_Update();

    /*------------------------------------------------------------------------*/
    /** - update outports */
    /*------------------------------------------------------------------------*/
    if (*(Outports.pLED0) > 0)
    {
        USER_LED0_ON;
    }
    else
    {
        USER_LED0_OFF;
    }
    if (*(Outports.pLED1) > 0)
    {
        USER_LED1_ON;
    }
    else
    {
        USER_LED1_OFF;
    }
	if (*(Outports.pLED2) > 0)
	{
		USER_LED2_ON;
	}
	else
	{
		USER_LED2_OFF;
	}
    if (*(Outports.pLED3) > 0)
    {
        USER_LED3_ON;
    }
    else
    {
        USER_LED3_OFF;
    }
}
