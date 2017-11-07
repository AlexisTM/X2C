/* $LastChangedRevision: 1109 $
 * $LastChangedDate:: 2017-02-27 14:58:50 +0100#$
 *
 * Copyright (c) 2016, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
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


/** 
 * @brief Main function.
 * 
 * @return The main function will never return due to the never ending loop.
 */
int main(void)
{
	/** - initialize system clock */
	initClock();
	
	/** - initialize "integrated monitor":
	 *    - configuration of LNet protocol:
	 *      - Node-ID: 1
	 *      - Buffer size: 255
	 *      .
	 *    .
	 *  - initialize serial interface
	 *    - configuration of USART2:
   *      - Baudrate: 115.2kB/s
   *      - Data bits: 8
   *      - Parity: none
   *      - Stop bits: 1
	 *      .
	 *    .
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
	KICK_DOG;

	initVersionInfo(TableStruct, (uint16)1);	/* version 1 */
	TableStruct->DSPState = PRG_LOADED_STATE;

  TableStruct->TFncTable = blockFunctionTable;
  TableStruct->TParamTable = parameterIdTable;

	/** - initialize X2C */
  X2C_Init();
  KICK_DOG;

	/** - initialize hardware */
	initHardware();
	KICK_DOG;
	
	/** - never ending loop -> interrupt driven algorithm */
  while(1)
	{
		/* serial communication with X2C communicator */
		protocol.pCommunicate((tProtocol*)&protocol);
	}
}


/** 
 * @brief Main control task.
 * 
 * Calling rate = 100us
 */
void mainTask(void)
{
	/** - assign inports */
	/* read user button */
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0)
	{
		Inports.User_Button = INT16_MAX;
	}
	else
	{
		Inports.User_Button = 0;
	}	
		
	/** - update X2C */
	X2C_Update();

	/** - update outports */
	/* green LED control */
	if (*Outports.pLED_green == 0)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
	}

	KICK_DOG;
}


/**
 * @brief Routine to set version.
 *
 *				Adds frame compilation date, time and version info to X2C maintenance structure.
 * 
 * @param tblStruct X2C maintenance structure.
 * @param appVersion Version number.
 */
static void initVersionInfo(volatile tTableStruct* tblStruct, uint16 appVersion)
{
	tblStruct->framePrgVersion = appVersion;
	tblStruct->framePrgCompDateTime = (uint8*)&compilationDate;
}
