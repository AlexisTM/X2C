/*
 * $LastChangedRevision: 833 $
 * $LastChangedDate:: 2015-12-15 18:11:05 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include <asf.h>
#include "LNet.h"
#include "Services.h"
#include "BlockServicesX2C.h"
#include "SerialGeneric.h"
#include "TableStruct.h"
#include "Hardware.h"
#include "X2C.h"
#include "Main.h"

/* X2C maintenance structure */
volatile tTableStruct TheTableStruct;
volatile tTableStruct* TableStruct = &TheTableStruct;

/* LNet protocol buffersize & node identifier */
#define LNET_BUFFERSIZE ((uint8)255)
#define LNET_NODEID ((uint8)1)

static tSerial hwInterface;
static tLNet protocol;
static uint8 protocolBuffer[LNET_BUFFERSIZE];

/* used by init version info */
const struct {
	uint8 date[11];
	uint8 time[8];
} compilationDate = { __DATE__, __TIME__ };
	
/* private prototypes */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion);

int main (void)
{
	sysclk_init();
	board_init();
	
	initTableStruct();
	initSerialGeneric(&hwInterface);
	initSerial(&hwInterface);
	initLNet(&protocol, protocolBuffer, LNET_BUFFERSIZE, LNET_NODEID);
	initServiceTable((tProtocol*)&protocol);
	addCoreServices((tProtocol*)&protocol);
	addBlockServices((tProtocol*)&protocol);
	addTableStructProtocol((tProtocol*)&protocol);
	linkSerial((tProtocol*)&protocol, &hwInterface);
	
	initVersionInfo(TableStruct, (uint16)0x0001);
	TableStruct->DSPState = PRG_LOADED_STATE;
	
	TableStruct->TFncTable = blockFunctionTable;
	TableStruct->TParamTable = parameterIdTable;
	
	initHardware();
	resetWatchdog();

	X2C_Init();
	resetWatchdog();

	while (1)
	{		
		protocol.pCommunicate((tProtocol*)&protocol);
	}
}

/* Adds frame compilation date, -time and version info into X2C maintenance structure */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion)
{
	tblStruct->framePrgVersion = appVersion;
	tblStruct->framePrgCompDateTime = (uint8*)&compilationDate;
}

/* X2C model update & LED control */
void mainTask(void)
{
	X2C_Update();
	resetWatchdog();
	
	if (*Outports.pLED_13 > 0)
	{
		BLINKY_LED_ON;
	}
	else
	{
		BLINKY_LED_OFF;
	}
}
