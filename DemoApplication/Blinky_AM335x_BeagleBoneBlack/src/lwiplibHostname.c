/*
 * $LastChangedRevision: 1084 $
 * $LastChangedDate:: 2017-01-23 15:01:40 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "ports/cpsw/lwiplib.c"
#include "lwiplibHostname.h"

/**
 * @brief Initializes lwip TCP/IP stack with hostname.
 *
 * @param lwipIf lwIP interface structure
 * @param hostname Hostname
 *
 * @return IP address
 */
uint32 lwIPInitHostname(LWIP_IF *lwipIf, char* hostname)
{
    struct ip_addr ip_addr;
    struct ip_addr net_mask;
    struct ip_addr gw_addr;
    unsigned int *ipAddrPtr;
    static unsigned int lwipInitFlag = 0;
    unsigned int ifNum;
    unsigned int temp;
    
    /* do lwip library init only once */
    if(0 == lwipInitFlag)
    {
        lwip_init();
    }

    /* Setup the network address values. */
    if(lwipIf->ipMode == IPADDR_USE_STATIC)
    {
        ip_addr.addr = htonl(lwipIf->ipAddr);
        net_mask.addr = htonl(lwipIf->netMask);
        gw_addr.addr = htonl(lwipIf->gwAddr);
    }
    else
    {
        ip_addr.addr = 0;
        net_mask.addr = 0;
        gw_addr.addr = 0;
    }

#ifdef CPSW_DUAL_MAC_MODE
    ifNum = (lwipIf->instNum * MAX_SLAVEPORT_PER_INST) + lwipIf->slvPortNum - 1;
#else
    ifNum = lwipIf->instNum;
#endif

    cpswPortIf[ifNum].inst_num = lwipIf->instNum;
    cpswPortIf[ifNum].port_num = lwipIf->slvPortNum;

    /* set MAC hardware address */
    for(temp = 0; temp < LEN_MAC_ADDRESS; temp++) 
    {
        cpswPortIf[ifNum].eth_addr[temp] =
                         lwipIf->macArray[(LEN_MAC_ADDRESS - 1) - temp];
    }
    
    /*
    ** Create, configure and add the Ethernet controller interface with
    ** default settings.  ip_input should be used to send packets directly to
    ** the stack. The lwIP will internaly call the cpswif_init function. 
    */
    if(NULL ==
       netif_add(&cpswNetIF[ifNum], &ip_addr, &net_mask, &gw_addr, 
                 &cpswPortIf[ifNum], cpswif_init, ip_input))
    {
        LWIP_PRINTF("\n\rUnable to add interface for interface %d", ifNum);
        return 0;
    }

#if LWIP_NETIF_HOSTNAME
    netif_set_hostname(&cpswNetIF[ifNum], hostname);
#endif

    if(0 == lwipInitFlag)
    {
        netif_set_default(&cpswNetIF[ifNum]);
        lwipInitFlag = 1;
    }

    /* Start DHCP, if enabled. */
#if LWIP_DHCP
    if(lwipIf->ipMode == IPADDR_USE_DHCP)
    {
        lwIPDHCPComplete(ifNum);
    }
#endif

    /* Start AutoIP, if enabled and DHCP is not. */
#if LWIP_AUTOIP
    if(lwipIf->ipMode == IPADDR_USE_AUTOIP)
    {
        autoip_start(&cpswNetIF[ifNum]);
    }
#endif

    if((lwipIf->ipMode == IPADDR_USE_STATIC)
       ||(lwipIf->ipMode == IPADDR_USE_AUTOIP))
    {
       /* Bring the interface up */
       netif_set_up(&cpswNetIF[ifNum]);
    }
  
    ipAddrPtr = (unsigned int*)&(cpswNetIF[ifNum].ip_addr);

    return (*ipAddrPtr);
}
