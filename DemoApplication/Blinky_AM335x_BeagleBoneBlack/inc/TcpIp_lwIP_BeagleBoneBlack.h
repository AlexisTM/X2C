/**
 * @file
 * @brief TCP/IP driver for BeagleBone Black.
 *
 * TCP/IP driver implementation for BeagleBone Black board.
 * Uses lwIP 1.4.0 stack for communication.
 */
/*
 * $LastChangedRevision: 1084 $
 * $LastChangedDate:: 2017-01-23 15:01:40 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#ifndef __TCPIP_LWIP_H__
#define __TCPIP_LWIP_H__

#include "tcp.h"
#include "CommonFcts.h"
#include "CircularByteBuffer.h"

typedef struct tTcpIp tTcpIp;
struct tTcpIp {
	uint8 (*send)(tTcpIp*, uint8);
	uint8 (*receive)(tTcpIp*);
	uint8 (*isReceiveDataAvailable)(tTcpIp*);
	uint8 (*isSendReady)(tTcpIp*);
	uint8 (*getTxFifoFree)(tTcpIp*);
	void (*flush)(tTcpIp*);

	tCircularByteBuffer rxBuffer;
	tCircularByteBuffer txBuffer;

	/* lwIP packet control block (PCB) */
	struct tcp_pcb* pcb;
	/* lwIP packet buffer (queue) */
	struct pbuf* pending;
};

/* public prototypes */
/**
 * Initializes TCP/IP interface.
 *
 * @param tcpip TCP/IP interface
 * @param IP address
 * @param port TCP port
 * @param hostname Hostname being used in DHCP (option #12)
 * @param rxBuffer Receive buffer
 * @param rxSize Receive buffer length
 * @param txBuffer Transmit buffer
 * @param txSize Transmit buffer length
 *
 * @return Assigned IP address
 *
 * @note Static IP address example: 192.168.0.1 => 0xC0A80001
 * @note If DHCP IP address is desired, the IP address has to be set to zero
 */
uint32 initTcpIp(tTcpIp* tcpip, uint32 ipAddress, uint16 port, char* hostname, uint8* rxBuffer, uint16 rxSize, uint8* txBuffer, uint16 txSize);
/* links protocol <-> interface */
/**
 * Links protocol with TCP/IP interface.
 *
 * @param protocol Protocol
 * @param tcpip TCP/IP interface
 */
void linkTcpIp(tProtocol* protocol, tTcpIp* tcpip);
/**
 * Closes connection.
 *
 * @param tcpip TCP/IP interface
 */
void closeConnection(tTcpIp* tcpip);
/**
 * Returns available bytes in receive buffer.
 *
 * @param tcpip TCIP/IP interface
 *
 * @return The number of bytes being available to receive
 */
uint16 getAvailableTcpIpBytes(tTcpIp* tcpip);
/**
 * Reads data from communication buffers.
 *
 * @param tcpip TCIP/IP interface
 * @param data User data buffer
 * @param len User data buffer len
 *
 * @return The number of bytes being transferred
 *
 * @note The caller must guarantee correct buffer size.
 */
uint16 getTcpIpData(tTcpIp* tcpip, uint8* data, uint16 len);

/**
 * Returns free bytes in transmit buffer.
 *
 * @param tcpip TCP/IP interface
 *
 * @return The number of free bytes in the transmit buffer
 */
uint16 getFreeTcpIpBytes(tTcpIp* tcpip);
/**
 * Writes data to communication buffers.
 *
 * @param tcpip TCIP/IP connection
 * @param data User data buffer
 * @param len User data buffer len
 *
 * @return The number of bytes being transferred
 *
 * @note The caller must guarantee correct buffer size.
 */
uint16 putTcpIpData(tTcpIp* tcpip, uint8* data, uint16 len);

#endif
