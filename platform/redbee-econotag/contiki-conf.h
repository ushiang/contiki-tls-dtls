/*
 * Copyright (c) 2010, Mariano Alvira <mar@devl.org> and other contributors
 * to the MC1322x project (http://mc1322x.devl.org) and Contiki.
 *
 * Copyright (c) 2006, Technical University of Munich
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * @(#)$$
 */

/**
 * \file
 *         Configuration for MC1322x hobby board based on 
 *         Configuration for sample STK 501 Contiki kernel
 *
 * \author
 *         Originial by:
 *         Simon Barner <barner@in.tum.de
 *         This version by:
 *         Mariano Alvira <mar@devl.org>
 */

#ifndef __CONTIKI_CONF_H__
#define __CONTIKI_CONF_H__

#include <stdint.h>

/* mc1322x files */
#include "contiki-mc1322x-conf.h"
/* this is from cpu/mc1322x/board */
#include "redbee-econotag.h"

/* Clock ticks per second */
#define CLOCK_CONF_SECOND 100
/* set to 1 to toggle the green led ever second */
/* FIXME setting this will break the sensor button (and other gpio) */
/* since leds_arch hits the entire gpio_data */
#define BLINK_SECONDS 0

#define CCIF
#define CLIF

/* Baud rate */
#define MOD 9999
/*  230400 bps, INC=767, MOD=9999, 24Mhz 16x samp */
/*  115200 bps, INC=767, MOD=9999, 24Mhz 8x samp */
#define INC 767  
/*  921600 bps, MOD=9999, 24Mhz 16x samp */
//#define INC 3071 
#define SAMP UCON_SAMP_8X
//#define SAMP UCON_SAMP_16X

#define uart_init uart1_init
#define dbg_putchar(x) uart1_putc(x)

#define USE_FORMATTED_STDIO         1
#define MACA_DEBUG                  0
#define CONTIKI_MACA_RAW_MODE       0
#define USE_32KHZ_XTAL              0

#define BLOCKING_TX 1
#define NULLRDC_CONF_802154_AUTOACK_HW 1

/* end of mc1322x specific config. */

/* start of conitki config. */
#define RIMEADDR_CONF_SIZE              8

/* EUI64 generation */
/* Organizationally Unique Identifier */
#define OUI 0xacde48     /* if IAB is defined then OUI = 0x0050C2 */
#define IAB 0xA8C        /* IAB 0xA8C for use on Redwire products only */
//#undef IAB               /* do not define an IAB if you are using a full OUI */
//#define EXT_ID 0xdef123  /* lower 12-bits used if IAB is defined */ 
#undef  EXT_ID           /* if an extention id is not defined then one will be generated randomly */

#define FLASH_BLANK_ADDR /* if defined then the generated rime address will flashed */

#if WITH_UIP6
/* Network setup for IPv6 */
#define NETSTACK_CONF_NETWORK sicslowpan_driver
#define NETSTACK_CONF_MAC     nullmac_driver 
/*#define NETSTACK_CONF_RDC     contikimac_driver*/ /* contikimac for redbee hasn't been well tested */
#define NETSTACK_CONF_RDC     nullrdc_driver
#define NETSTACK_CONF_RADIO   contiki_maca_driver
#define NETSTACK_CONF_FRAMER  framer_802154

#define MAC_CONF_CHANNEL_CHECK_RATE      8
#define RIME_CONF_NO_POLITE_ANNOUCEMENTS 0
#define CXMAC_CONF_ANNOUNCEMENTS         0
#define XMAC_CONF_ANNOUNCEMENTS          0

#else /* WITH_UIP6 */
/* Network setup for non-IPv6 (rime). */

#define NETSTACK_CONF_NETWORK rime_driver
#define NETSTACK_CONF_MAC     csma_driver
#define NETSTACK_CONF_RDC     sicslowmac_driver
#define NETSTACK_CONF_RADIO   contiki_maca_driver
#define NETSTACK_CONF_FRAMER  framer_802154

#define MAC_CONF_CHANNEL_CHECK_RATE      8

#define COLLECT_CONF_ANNOUNCEMENTS       1
#define RIME_CONF_NO_POLITE_ANNOUCEMENTS 0
#define CXMAC_CONF_ANNOUNCEMENTS         0
#define XMAC_CONF_ANNOUNCEMENTS          0
#define CONTIKIMAC_CONF_ANNOUNCEMENTS    0

#define CONTIKIMAC_CONF_COMPOWER         0
#define XMAC_CONF_COMPOWER               0
#define CXMAC_CONF_COMPOWER              0

#define COLLECT_NEIGHBOR_CONF_MAX_NEIGHBORS      32

#endif /* WITH_UIP6 */

#define QUEUEBUF_CONF_NUM          16

#define PACKETBUF_CONF_ATTRS_INLINE 1

#ifndef RF_CHANNEL
#define RF_CHANNEL              26
#endif /* RF_CHANNEL */

#define CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT 0

#define IEEE802154_CONF_PANID       0xABCD

#define PROFILE_CONF_ON 0
#define ENERGEST_CONF_ON 0

#define AODV_COMPLIANCE
#define AODV_NUM_RT_ENTRIES 32

#define WITH_ASCII 1

#define PROCESS_CONF_NUMEVENTS 8
#define PROCESS_CONF_STATS 1

#ifdef WITH_UIP6

#define RIMEADDR_CONF_SIZE              8

#define UIP_CONF_LL_802154              1
#define UIP_CONF_LLH_LEN                0

#define UIP_CONF_ROUTER                 1  
#define UIP_CONF_IPV6_RPL               1

#define UIP_CONF_DS6_NBR_NBU     30
#define UIP_CONF_DS6_ROUTE_NBU   30

#define UIP_CONF_ND6_SEND_RA		0
#define UIP_CONF_ND6_REACHABLE_TIME     600000
#define UIP_CONF_ND6_RETRANS_TIMER      10000

#define UIP_CONF_IPV6                   1
#define UIP_CONF_IPV6_QUEUE_PKT         0
#define UIP_CONF_IPV6_CHECKS            1
#define UIP_CONF_IPV6_REASSEMBLY        0
#define UIP_CONF_NETIF_MAX_ADDRESSES    3
#define UIP_CONF_ND6_MAX_PREFIXES       3
#define UIP_CONF_ND6_MAX_NEIGHBORS      4
#define UIP_CONF_ND6_MAX_DEFROUTERS     2
#define UIP_CONF_IP_FORWARD             0
#define UIP_CONF_BUFFER_SIZE		1300
#define SICSLOWPAN_CONF_FRAG            1
#define SICSLOWPAN_CONF_MAXAGE          8

#define SICSLOWPAN_CONF_COMPRESSION_IPV6        0
#define SICSLOWPAN_CONF_COMPRESSION_HC1         1
#define SICSLOWPAN_CONF_COMPRESSION_HC01        2
#define SICSLOWPAN_CONF_COMPRESSION             SICSLOWPAN_COMPRESSION_HC06
#ifndef SICSLOWPAN_CONF_FRAG
#define SICSLOWPAN_CONF_FRAG                    1
#define SICSLOWPAN_CONF_MAXAGE                  8
#endif /* SICSLOWPAN_CONF_FRAG */
#define SICSLOWPAN_CONF_CONVENTIONAL_MAC	1
#define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS       2
#else /* WITH_UIP6 */
#define UIP_CONF_IP_FORWARD      1
#define UIP_CONF_BUFFER_SIZE     1300
#endif /* WITH_UIP6 */

#define UIP_CONF_ICMP_DEST_UNREACH 1

#define UIP_CONF_DHCP_LIGHT
#define UIP_CONF_LLH_LEN         0
#define UIP_CONF_RECEIVE_WINDOW  48
#define UIP_CONF_TCP_MSS         48
#define UIP_CONF_MAX_CONNECTIONS 4
#define UIP_CONF_MAX_LISTENPORTS 8
#define UIP_CONF_UDP_CONNS       12
#define UIP_CONF_FWCACHE_SIZE    30
#define UIP_CONF_BROADCAST       1
#define UIP_ARCH_IPCHKSUM        1
#define UIP_CONF_UDP             1
#define UIP_CONF_UDP_CHECKSUMS   1
#define UIP_CONF_PINGADDRCONF    0
#define UIP_CONF_LOGGING         0

#define UIP_CONF_TCP_SPLIT       0

/* include the project config */
/* PROJECT_CONF_H might be defined in the project Makefile */
#ifdef PROJECT_CONF_H
#include PROJECT_CONF_H
#endif /* PROJECT_CONF_H */

#endif /* __CONTIKI_CONF_H__ */
