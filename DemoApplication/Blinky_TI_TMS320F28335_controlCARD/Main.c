/*
 * Initialization and main function.
 *
 * $LastChangedRevision: 1084 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "CommonFcts.h"
#include "TableStruct.h"
#include "LNet.h"
#include "Services.h"
#include "BlockServicesX2C.h"
#include "CommonFcts.h"
#include "Hardware.h"
#include "X2C.h"
#include "Main.h"

/* labels from linker file for section ramfuncs */
extern uint16 RamfuncsLoadStart;
extern uint16 RamfuncsLoadEnd;
extern uint16 RamfuncsRunStart;

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

/*
 * Main function.
 */
void main(void)
{
	memcpy(&RamfuncsRunStart,&RamfuncsLoadStart,&RamfuncsLoadEnd - &RamfuncsLoadStart);
	initFlash();

	initInterruptVector();

    initTableStruct();
    initSerialGeneric(&interface);
    initSerial(&interface);
    initLNet(&protocol, bufferLNet, LNET_BUFFERSIZE, LNET_NODEID);
    initServiceTable((tProtocol*)&protocol);
    addCoreServices((tProtocol*)&protocol);
    addBlockServices((tProtocol*)&protocol);
    addTableStructProtocol((tProtocol*)&protocol);
    linkSerial((tProtocol*)&protocol, &interface);
	KICK_DOG;

	initVersionInfo(TableStruct, (uint16)0x0001);
	TableStruct->DSPState = PRG_LOADED_STATE;

    TableStruct->TFncTable = blockFunctionTable;
    TableStruct->TParamTable = parameterIdTable;

	initHardware();
	KICK_DOG;

    X2C_Init();
    KICK_DOG;

    while(1)
	{
		/* communication procedure */
		protocol.pCommunicate((tProtocol*)&protocol);
	}
}


/*
 * Main control task.
 */
void mainTask(void)
{
	/* update X2C */
	X2C_Update();

//	/* update LED LD2 */
//	if (*Outports.pLED_LD2 == 0)
//	{
//		GpioDataRegs.GPADAT.bit.GPIO31 = 1;
//	}
//	else
//	{
//		GpioDataRegs.GPADAT.bit.GPIO31 = 0;
//	}
//
//	/* update LED LD3 */
//	if (*Outports.pLED_LD3 == 0)
//	{
//		GpioDataRegs.GPBDAT.bit.GPIO34 = 1;
//	}
//	else
//	{
//		GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
//	}

	KICK_DOG;
}

/*
 * Adds frame compilation date, time and version info to X2C maintenance structure.
 */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion)
{
	tblStruct->framePrgVersion = appVersion;
	tblStruct->framePrgCompDateTime = (uint8*)&compilationDate;
}
