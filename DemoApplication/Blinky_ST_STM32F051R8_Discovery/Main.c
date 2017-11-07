/*
 * Initialization and main function.
 *
 * $LastChangedRevision: 811 $
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
int main(void)
{
	initClock();
	
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

  X2C_Init();
  KICK_DOG;

	initHardware();
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
	
	/* read user button */
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		Inports.User_Button = 0;
	}
	else
	{
		Inports.User_Button = INT16_MAX;
	}	
		
	/* update X2C */
	X2C_Update();

	/* blue LED control */
	if (*Outports.pLED_blue == 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	}
	else
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
	}
	
	/* green LED control */
	if (*Outports.pLED_green == 0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	}
	else
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
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
