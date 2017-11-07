/**
 * \file lwipopts.h - Configuration options for lwIP
 *
 * Copyright (c) 2010 Texas Instruments Incorporated
 */
/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#include "consoleUtils.h"

/*****************************************************************************
**                           CONFIGURATIONS
*****************************************************************************/
/*
** The macro CPSW_DUAL_MAC_MODE shall be defined for using CPSW ports in 
** Dual MAC mode.
*/
#define CPSW_DUAL_MAC_MODE

/*
** The below macro should be defined for using lwIP with cache. For cache
** enabling, pbuf pool shall be cache line aligned. This is done by using
** separate pool for each memory. The alignment of pbuf pool to cache line 
** size is done in /ports/cpsw/include/arch/cc.h. 
*/
#define LWIP_CACHE_ENABLED

#define SOC_CACHELINE_SIZE_BYTES        64            /* Number of bytes in
                                                         a cache line */
/*
** The timeout for DHCP completion. lwIP library will wait for DHCP 
** completion for (LWIP_DHCP_TIMEOUT / 100) seconds.
*/
#define LWIP_DHCP_TIMEOUT               500

/*
** The number of times DHCP is attempted. Each time, the library will wait
** for (LWIP_DHCP_TIMEOUT / 100) seconds for DHCP completion.
*/
#define NUM_DHCP_TRIES                  5

/*****************************************************************************
**            lwIP SPECIFIC DEFINITIONS - To be used by lwIP stack
*****************************************************************************/
#define HOST_TMR_INTERVAL               0         
#define DYNAMIC_HTTP_HEADERS

/*****************************************************************************
**                    Platform specific locking 
*****************************************************************************/
#define SYS_LIGHTWEIGHT_PROT            1          
#define NO_SYS                          1          
#define NO_SYS_NO_TIMERS                1

/*****************************************************************************
**                          Memory Options
*****************************************************************************/
#define MEM_ALIGNMENT                   4         
#define MEM_SIZE                        (128 * 1024) /* 128K */

#define MEMP_NUM_PBUF                   96     
#define MEMP_NUM_TCP_PCB                32    
#define PBUF_POOL_SIZE                  210    

#ifdef LWIP_CACHE_ENABLED
#define MEMP_SEPARATE_POOLS             1            /* We want the pbuf 
                                                        pool cache line
                                                        aligned*/
#endif

/*****************************************************************************
**                           IP Options
*****************************************************************************/
#define IP_REASSEMBLY                   0          
#define IP_FRAG                         0          

/*****************************************************************************
**                           DHCP Options
*****************************************************************************/
#define LWIP_DHCP                       1
#define DHCP_DOES_ARP_CHECK             0

/*****************************************************************************
**                           Auto IP  Options
*****************************************************************************/
#define LWIP_AUTOIP                     0            
#define LWIP_DHCP_AUTOIP_COOP           ((LWIP_DHCP) && (LWIP_AUTOIP))

/*****************************************************************************
**                           TCP  Options
*****************************************************************************/
#define TCP_MSS                         1500           
#define TCP_WND                         (8 * TCP_MSS)  
#define TCP_SND_BUF                     (8 * TCP_MSS)
#define TCP_OVERSIZE                    TCP_MSS

/*****************************************************************************
**                           PBUF  Options
*****************************************************************************/
#define PBUF_LINK_HLEN                  14      
#define PBUF_POOL_BUFSIZE               1520         /* + size of struct pbuf
                                                        shall be cache line
                                                        aligned be enabled */
#define ETH_PAD_SIZE                    0           
#define LWIP_NETCONN                    0             

/*****************************************************************************
**                           Socket  Options
*****************************************************************************/
#define LWIP_SOCKET                     0           

/*****************************************************************************
**                          Debugging options
*****************************************************************************/
#define LWIP_DEBUG						0
#if LWIP_DEBUG
#define LWIP_DBG_MIN_LEVEL				LWIP_DBG_LEVEL_SERIOUS
#define LWIP_DBG_TYPES_ON               (LWIP_DBG_ON | LWIP_DBG_HALT | LWIP_DBG_TRACE | LWIP_DBG_STATE | LWIP_DBG_FRESH)

#define DHCP_DEBUG						LWIP_DBG_OFF
#define UDP_DEBUG						LWIP_DBG_OFF
#define MEM_DEBUG						LWIP_DBG_OFF
#define MEMP_DEBUG						LWIP_DBG_OFF
#define IP_DEBUG                        LWIP_DBG_OFF
#define NETIF_DEBUG                     LWIP_DBG_OFF
#define API_MSG_DEBUG                   LWIP_DBG_OFF
#define API_LIB_DEBUG                   LWIP_DBG_OFF
#define SYS_DEBUG                       LWIP_DBG_OFF
#define PBUF_DEBUG                      LWIP_DBG_OFF
#define RAW_DEBUG                       LWIP_DBG_OFF
#define ICMP_DEBUG                      LWIP_DBG_OFF
#define INET_DEBUG                      LWIP_DBG_OFF
#define ETHARP_DEBUG                    LWIP_DBG_OFF
#define TIMERS_DEBUG                    LWIP_DBG_OFF
#define TCP_DEBUG                       LWIP_DBG_OFF
#define TCP_INPUT_DEBUG                 LWIP_DBG_OFF
#define TCP_OUTPUT_DEBUG                LWIP_DBG_OFF
#define TCPIP_DEBUG                     LWIP_DBG_OFF
#endif

#define X8_F  "02x"
#define U16_F "u"
#define S16_F "d"
#define X16_F "x"
#define U32_F "lu"
#define S32_F "ld"
#define X32_F "x"

#define LWIP_PLATFORM_DIAG(x) do { ConsoleUtilsPrintf x; } while(0)

/**
 * User specific macros.
 */
#define LWIP_NETIF_HOSTNAME				1

#define CPSW0_PORT_1_PHY_ADDR           0
#define CPSW0_PORT_2_PHY_ADDR           1
#define CPSW0_PORT_1_PHY_GIGABIT        FALSE
#define CPSW0_PORT_2_PHY_GIGABIT        FALSE

#define TCP_SND_QUEUELEN                ((4 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))
#define MEMP_NUM_TCP_SEG                TCP_SND_QUEUELEN

#endif /* __LWIPOPTS_H__ */
