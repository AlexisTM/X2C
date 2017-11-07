/*
 * Initialization and main function.
 *
 * $LastChangedRevision: 766 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "CommonFcts.h"
#include "TableStruct.h"
#include "LNet.h"
#include "Services.h"
#include "BlockServicesX2C.h"
#include "Hardware.h"
#include "X2C.h"
#include "Main.h"

/* labels from linker file for section ramfuncs */
extern uint16 RamfuncsLoadStart;
extern uint16 RamfuncsLoadEnd;
extern uint16 RamfuncsRunStart;

/* X2C maintenance structure */
volatile tTableStruct TheTableStruct;
volatile tTableStruct *TableStruct = &TheTableStruct;

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
    initLNet(&protocol, bufferLNet, LNET_BUFFERSIZE, LNET_NODEID);
    initServiceTable((tProtocol*)&protocol);
    addCoreServices((tProtocol*)&protocol);
    addBlockServices((tProtocol*)&protocol);
    addTableStructProtocol((tProtocol*)&protocol);
    linkSerial((tProtocol*)&protocol, &interface);
    TableStruct->DSPState = PRG_LOADED_STATE;

	KICK_DOG;

	initVersionInfo(TableStruct, (uint16)0x0001);
    TableStruct->TFncTable = blockFunctionTable;
    TableStruct->TParamTable = parameterIdTable;

    initSerial(&interface);
	initHardware();
	KICK_DOG;

    X2C_Init();
    KICK_DOG;

    while(1)
	{
		/* communication */
		TableStruct->protocols[0]->pCommunicate((struct tProtocol *)TableStruct->protocols[0]);
	}
}

/*
 * Main control task.
 */
void mainTask(void)
{

	/* assign inports */
	/* read ADC-A0 and convert to Q15 format */
	Inports.Adc_A0 = AdcResult.ADCRESULT0 << 3;
	/* read ADC-B0 and convert to Q15 format */
	Inports.Adc_B0 = AdcResult.ADCRESULT1 << 3;
	if (GpioDataRegs.GPBDAT.bit.GPIO33 != 0)	/* read logic state of GPIO-33 */
	{
		Inports.Gpio_33 = INT16_MAX;
	}
	else
	{
		Inports.Gpio_33 = (int16)0;
	}

	/* update X2C */
	X2C_Update();

	/* update outports */
	if (*Outports.pLed2 != 0)
	{
		GpioDataRegs.GPBCLEAR.bit.GPIO34 = (uint16)1;	/* active low -> LED on */
	}
	else
	{
		GpioDataRegs.GPBSET.bit.GPIO34 = (uint16)1;	/* active low -> LED off */
	}

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
