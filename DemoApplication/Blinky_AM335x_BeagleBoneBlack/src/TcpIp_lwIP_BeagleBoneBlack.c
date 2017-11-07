/*
 * $LastChangedRevision: 1084 $
 * $LastChangedDate:: 2017-01-23 15:01:40 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "lwiplibHostname.h"
#include "init.h"
#include "interrupt.h"
#include "beaglebone.h"
#include "delay.h"
#include "cache.h"
#include "netif.h"

#include "CircularByteBuffer.h"
#include "TcpIp_lwIP_BeagleBoneBlack.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

/**
 * Debug diagnostic messages.
 * Example:
 * #define TCPIP_DEBUG_DIAG(x) printf x
 */
#ifndef TCPIP_DEBUG_DIAG
#define TCPIP_DEBUG_DIAG(x)
#endif

/* private prototypes */
static uint8 getReceiveDataAvailable(tTcpIp* tcpip);
static uint8 sendByte(tTcpIp* tcpip, uint8 data);
static uint8 receiveByte(tTcpIp* tcpip);
static uint8 isSendDataAvailable(tTcpIp* tcpip);
static void flush(tTcpIp* tcpip);
/* Sets up physical interface */
static void initPhy(LWIP_IF* lwip_if);
/* lwIP callback accept function */
static err_t tcpAcceptCallback(void* arg, struct tcp_pcb* pcb, err_t err);
/* lwIP callback received function */
static err_t tcpReceivedCallback(void* arg, struct tcp_pcb* pcb, struct pbuf* p, err_t err);
static void tcpErrorCallback(void *arg, err_t err);
/* Interrupt Handler for Core 0 Receive interrupt */
static void CPSWCore0RxIsr(void);
/* Interrupt Handler for Core 0 Transmit interrupt */
static void CPSWCore0TxIsr(void);

static void readPendingBuffer(tTcpIp* tcpip);
static void disableMacInterrupts(void);
static void enableMacInterrupts(void);


void linkTcpIp(tProtocol* protocol, tTcpIp* tcpip)
{
	protocol->hwInterface = (tInterface*)tcpip;
}

uint32 initTcpIp(tTcpIp* tcpip, uint32 ipAddress, uint16 port, char* hostname, uint8* rxBuffer, uint16 rxSize, \
		uint8* txBuffer, uint16 txSize)
{
	struct tcp_pcb* pcb;
	LWIP_IF lwipIfPort1;
	uint32 assignedIpAddress;

	initPhy(&lwipIfPort1);

	if (ipAddress > 0)
	{
		lwipIfPort1.instNum = 0;
		lwipIfPort1.slvPortNum = 1;
		lwipIfPort1.ipAddr = ipAddress;
		lwipIfPort1.netMask = 0;
		lwipIfPort1.gwAddr = 0;
		lwipIfPort1.ipMode = IPADDR_USE_STATIC;
		assignedIpAddress = lwIPInitHostname(&lwipIfPort1, hostname);
	}
	else
	{
		lwipIfPort1.instNum = 0;
		lwipIfPort1.slvPortNum = 1;
		lwipIfPort1.ipAddr = 0;
		lwipIfPort1.netMask = 0;
		lwipIfPort1.gwAddr = 0;
		lwipIfPort1.ipMode = IPADDR_USE_DHCP;
		assignedIpAddress = lwIPInitHostname(&lwipIfPort1, hostname);
	}

	pcb = tcp_new();
	tcp_bind(pcb, IP_ADDR_ANY, port);
	pcb = tcp_listen(pcb);
	tcp_arg(pcb, tcpip);
	tcp_accept(pcb, tcpAcceptCallback);

	tcpip->receive = (uint8 (*)(tTcpIp*))receiveByte;
	tcpip->send = (uint8 (*)(tTcpIp*, uint8))sendByte;
	tcpip->isReceiveDataAvailable = (uint8(*)(tTcpIp*))getReceiveDataAvailable;
	tcpip->isSendReady = (uint8 (*)(tTcpIp*))isSendDataAvailable;
	tcpip->flush = (void(*)(tTcpIp*))flush;

	initBuffer(&tcpip->txBuffer, txBuffer, txSize);
	initBuffer(&tcpip->rxBuffer, rxBuffer, rxSize);

	return (assignedIpAddress);
}

static void initPhy(LWIP_IF* lwip_if)
{

#ifdef LWIP_CACHE_ENABLED
    CacheEnable(CACHE_ALL);
#endif

    CPSWPinMuxSetup();
    CPSWClkEnable();

    /* Chip configuration RGMII selection */
    EVMPortMIIModeSelect();

    /* Get the MAC address */
    EVMMACAddrGet(0, lwip_if->macArray);
//    EVMMACAddrGet(1, lwipIfPort2.macArray);

    /* Enable IRQ for ARM (in CPSR)*/
    IntMasterIRQEnable();
    IntAINTCInit();
    /* Register the Receive ISR for Core 0 */
    IntRegister(SYS_INT_3PGSWRXINT0, CPSWCore0RxIsr);
    /* Register the Transmit ISR for Core 0 */
    IntRegister(SYS_INT_3PGSWTXINT0, CPSWCore0TxIsr);
    /* Set the priority */
    IntPrioritySet(SYS_INT_3PGSWTXINT0, 0, AINTC_HOSTINT_ROUTE_IRQ);
    IntPrioritySet(SYS_INT_3PGSWRXINT0, 0, AINTC_HOSTINT_ROUTE_IRQ);
    /* Enable the system interrupt */
    IntSystemEnable(SYS_INT_3PGSWTXINT0);
    IntSystemEnable(SYS_INT_3PGSWRXINT0);

    DelayTimerSetup();
}


static err_t tcpAcceptCallback(void* arg, struct tcp_pcb* pcb, err_t err)
{
	tTcpIp* tcpip = (tTcpIp*)arg;

	tcp_accepted(((struct tcp_pcb_listen*)arg));

	tcp_recv(pcb, tcpReceivedCallback);
	tcp_err(pcb, tcpErrorCallback);

	tcpip->pcb = pcb;
	tcpip->pending = NULL;

	return (ERR_OK);
}


static void tcpErrorCallback(void *arg, err_t err)
{
	TCPIP_DEBUG_DIAG(("Error %d\n", err));
}

static void disableMacInterrupts(void)
{
	IntSystemDisable(SYS_INT_3PGSWTXINT0);
	IntSystemDisable(SYS_INT_3PGSWRXINT0);
}

static void enableMacInterrupts(void)
{
	IntSystemEnable(SYS_INT_3PGSWTXINT0);
	IntSystemEnable(SYS_INT_3PGSWRXINT0);
}


static void readPendingBuffer(tTcpIp* tcpip)
{
	uint8 prevLen, curLen;

	disableMacInterrupts();

	while ((tcpip->pending != NULL) && (getFreeBytes(&tcpip->rxBuffer) > tcpip->pending->len))
	{
		struct pbuf* curPacket = tcpip->pending;
		putData(&tcpip->rxBuffer, (uint8*)curPacket->payload, curPacket->len);
		tcp_recved(tcpip->pcb, curPacket->len);

		prevLen = pbuf_clen(tcpip->pending);

		tcpip->pending = pbuf_dechain(curPacket);
		pbuf_free(curPacket);

		curLen = pbuf_clen(tcpip->pending);

		if ((curLen+1) < prevLen)
		{
			TCPIP_DEBUG_DIAG(("diff prev/curr = %d / %d\n", prevLen, curLen));
		}
	}

	enableMacInterrupts();
}


static err_t tcpReceivedCallback(void* arg, struct tcp_pcb* pcb, struct pbuf* p, err_t err)
{
	tTcpIp* tcpip = (tTcpIp*)arg;

	if ((err != ERR_OK) || (p == NULL))
	{
		if (p != NULL)
		{
			pbuf_free(p);
		}
		TCPIP_DEBUG_DIAG(("Closing connection with error %d\n", err));
		closeConnection(tcpip);

		return (err);
	}
	else
	{
		uint8 clen;
		clen = pbuf_clen(p);
		if (clen > 1)
		{
			TCPIP_DEBUG_DIAG(("clen=%d\n", clen));
		}
		if (tcpip->pending != NULL)
		{
			pbuf_chain(tcpip->pending, p);
		}
		else
		{
			tcpip->pending = p;
		}

		while (p->next != NULL)
		{
			pbuf_ref(p->next);
			p = p->next;
		}

		readPendingBuffer(tcpip);
	}
	return (ERR_OK);
}

void closeConnection(tTcpIp* tcpip)
{
	err_t err;

	tcp_recv(tcpip->pcb, NULL);
	err = tcp_close(tcpip->pcb);
	if (err != ERR_OK)
	{
		tcp_recv(tcpip->pcb, tcpReceivedCallback);
	}
	else
	{
		tcp_arg(tcpip->pcb, NULL);
		tcp_poll(tcpip->pcb, NULL, 0);
	}
}

static void flush(tTcpIp* tcpip)
{
	uint16 txBufFree, bytes2send;
	uint16 bytesSent;
	err_t txErr;

	bytes2send = getUsedBytes(&tcpip->txBuffer);

	if (bytes2send == 0)
	{
		return;
	}

	txErr = ERR_OK;
	bytesSent = 0;
	while ((bytes2send > 0) && (txErr == ERR_OK))
	{
		disableMacInterrupts();

		uint16 curBytes = getLinearUsedSpace(&tcpip->txBuffer);
		uint8* startAddress = getStartAddress(&tcpip->txBuffer);
		txBufFree = tcp_sndbuf(tcpip->pcb);

		if (curBytes > txBufFree)
		{
			curBytes = txBufFree;
		}

		txErr = tcp_write(tcpip->pcb, startAddress, curBytes, TCP_WRITE_FLAG_COPY);
		if (txErr == ERR_OK)
		{
			moveStart(&tcpip->txBuffer, curBytes);
			bytesSent += curBytes;
			bytes2send -= curBytes;
		}
		else
		{
			TCPIP_DEBUG_DIAG(("tcp_write error: %d", txErr));
		}

		txBufFree = tcp_sndbuf(tcpip->pcb);
		if ((txBufFree == 0) || (bytes2send == 0))
		{
			txErr = tcp_output(tcpip->pcb);
			if (txErr != ERR_OK)
			{
				TCPIP_DEBUG_DIAG(("tcp_output error: %d", txErr));
			}
		}
		enableMacInterrupts();
	}
}


uint16 getAvailableTcpIpBytes(tTcpIp* tcpip)
{
	readPendingBuffer(tcpip);
	uint16 usedBytes = getUsedBytes(&tcpip->rxBuffer);
	return (usedBytes);
}


uint16 getFreeTcpIpBytes(tTcpIp* tcpip)
{
	uint16 freeBytes = getFreeBytes(&tcpip->txBuffer);
	return (freeBytes);
}


uint16 getTcpIpData(tTcpIp* tcpip, uint8* data, uint16 len)
{
	uint16 readData;

	readPendingBuffer(tcpip);
	disableMacInterrupts();
	readData = getData(&tcpip->rxBuffer, data, len);
	enableMacInterrupts();
	return (readData);
}


uint16 putTcpIpData(tTcpIp* tcpip, uint8* data, uint16 len)
{
	uint16 writeData;
	writeData = putData(&tcpip->txBuffer, data, len);
	tcpip->flush(tcpip);
	return (writeData);
}


/* Returns the amount of available receive bytes */
static uint8 getReceiveDataAvailable(tTcpIp* tcpip)
{
	uint16 rcvDataAvail;

	rcvDataAvail = tcpip->rxBuffer.used;
	if (rcvDataAvail > UINT8_MAX)
	{
		return (UINT8_MAX);
	}
	else
	{
		return ((uint8)rcvDataAvail);
	}
}

static uint8 sendByte(tTcpIp* tcpip, uint8 data)
{
	writeData(&tcpip->txBuffer, &data);
	if (tcpip->txBuffer.used >= tcpip->txBuffer.size)
	{
		tcpip->flush(tcpip);
	}
	return (0);
}


static uint8 receiveByte(tTcpIp* tcpip)
{
	uint8 data;

	readPendingBuffer(tcpip);
	readData(&tcpip->rxBuffer, &data);
	return (data);
}

static uint8 isSendDataAvailable(tTcpIp* tcpip)
{
	uint8 isSendDataAvailable;
	if (getFreeBytes(&tcpip->txBuffer) > 0)
	{
		isSendDataAvailable = (uint8)1;
	}
	else
	{
		isSendDataAvailable = (uint8)0;
	}
	return (isSendDataAvailable);
}


static void CPSWCore0RxIsr(void)
{
    lwIPRxIntHandler(0);
}


static void CPSWCore0TxIsr(void)
{
    lwIPTxIntHandler(0);
}
