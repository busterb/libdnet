/*
 * The defines used in this header came from the ISC dhcp source code. Here is their
 * License:
 *
 * Copyright (c) 2004-2007,2009 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1995-2003 by Internet Software Consortium
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *   Internet Systems Consortium, Inc.
 *   950 Charter Street
 *   Redwood City, CA 94063
 *   <info@isc.org>
 *   https://www.isc.org/
 *
 * This software has been written for Internet Systems Consortium
 * by Ted Lemon in cooperation with Vixie Enterprises.  To learn more
 * about Internet Systems Consortium, see ``https://www.isc.org''.
 * To learn more about Vixie Enterprises, see ``http://www.vix.com''.
 */

/*
   0                   1                   2                   3
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     op (1)    |   htype (1)   |   hlen (1)    |   hops (1)    |
   +---------------+---------------+---------------+---------------+
   |                            xid (4)                            |
   +-------------------------------+-------------------------------+
   |           secs (2)            |           flags (2)           |
   +-------------------------------+-------------------------------+
   |                          ciaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          yiaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          siaddr  (4)                          |
   +---------------------------------------------------------------+
   |                          giaddr  (4)                          |
   +---------------------------------------------------------------+
   |                                                               |
   |                          chaddr  (16)                         |
   |                                                               |
   |                                                               |
   +---------------------------------------------------------------+
   |                                                               |
   |                          sname   (64)                         |
   +---------------------------------------------------------------+
   |                                                               |
   |                          file    (128)                        |
   +---------------------------------------------------------------+
   |                                                               |
   |                          options (variable)                   |
   +---------------------------------------------------------------+

                       1 1 1 1 1 1
   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |B|             MBZ             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   B:  BROADCAST flag
   MBZ:  MUST BE ZERO (reserved for future use)

 */
#ifndef DNET_DHCP_H
#define DNET_DHCP_H

#include <stdint.h>

#define DHCP_UDP_OVERHEAD       (20 + /* IP header */           \
                                 8)	/* UDP header */
#define DHCP_SNAME_LEN          64
#define DHCP_FILE_LEN           128
#define DHCP_FIXED_NON_UDP      236
#define DHCP_FIXED_LEN          (DHCP_FIXED_NON_UDP + DHCP_UDP_OVERHEAD)
#define DHCP_MTU_MAX            1500
#define DHCP_OPTION_LEN         (DHCP_MTU_MAX - DHCP_FIXED_LEN)

struct dhcp_hdr {
	uint8_t op;					/* Message opcode/type */
	uint8_t htype;				/* Hardware addr type (see net/if_types.h) */
	uint8_t hlen;				/* Hardware addr length */
	uint8_t hops;				/* Number of relay agent hops from client */
	uint32_t xid;				/* Transaction ID */
	uint16_t secs;				/* Seconds since client started looking */
	uint16_t flags;				/* Flag bits */
	ip_addr_t ciaddr;			/* Client IP address (if already in use) */
	ip_addr_t yiaddr;			/* Client IP address */
	ip_addr_t siaddr;			/* IP address of next server to talk to */
	ip_addr_t giaddr;			/* DHCP relay agent IP address */
	unsigned char chaddr[16];	/* Client hardware address */
	char sname[DHCP_SNAME_LEN];	/* Server name */
	char file[DHCP_FILE_LEN];	/* Boot filename */
	unsigned char options[DHCP_OPTION_LEN];
	/*
	 * Optional parameters
	 * (actual length dependent on MTU).
	 */
} __attribute__((__packed__));

#define DHCP_MIN_HDR_LEN 252	/* This includes the magic cookie, dhcp message type and client identifier option */

enum dhcp_message_type {
	DHCPDISCOVER = 1,			/* Client broadcast to locate available servers. */
	DHCPOFFER,					/* Server to client in response to DHCPDISCOVER with
								 * offer of configuration parameters. */
	DHCPREQUEST,
	DHCPDECLINE,
	DHCPACK,
	DHCPNAK,
	DHCPRELEASE,
	DHCPINFORM,
	DHCPFORCERENEW,
	DHCPLEASEQUERY,
	DHCPLEASEUNASSIGNED,
	DHCPLEASEUNKNOWN,
	DHCPLEASEACTIVE
};
/* BOOTP (rfc951) message types */
#define BOOTREQUEST     1
#define BOOTREPLY       2

/* Possible values for hardware type (htype) field... */
#define HTYPE_ETHER     1		/* Ethernet 10Mbps              */
#define HTYPE_IEEE802   6		/* IEEE 802.2 Token Ring...     */
#define HTYPE_FDDI      8		/* FDDI...                      */

#define DHCP_CLIENT_SRC_PORT 68
#define DHCP_SERVER_SRC_PORT 67

/* Magic cookie validating dhcp options field (and bootp vendor
   extensions field). */
#define DHCP_OPTIONS_COOKIE     "\x63\x82\x53\x63"	/* 99, 130, 83 and 99 */

#define REQUEST_SUBNETMASK 1
#define REQUEST_ROUTER     3
#define REQUEST_DNS        6

/* DHCP Option codes: */
#define DHO_PAD                                 0
#define DHO_SUBNET_MASK                         1
#define DHO_TIME_OFFSET                         2
#define DHO_ROUTERS                             3
#define DHO_TIME_SERVERS                        4
#define DHO_NAME_SERVERS                        5
#define DHO_DOMAIN_NAME_SERVERS                 6
#define DHO_LOG_SERVERS                         7
#define DHO_COOKIE_SERVERS                      8
#define DHO_LPR_SERVERS                         9
#define DHO_IMPRESS_SERVERS                     10
#define DHO_RESOURCE_LOCATION_SERVERS           11
#define DHO_HOST_NAME                           12
#define DHO_BOOT_SIZE                           13
#define DHO_MERIT_DUMP                          14
#define DHO_DOMAIN_NAME                         15
#define DHO_SWAP_SERVER                         16
#define DHO_ROOT_PATH                           17
#define DHO_EXTENSIONS_PATH                     18
#define DHO_IP_FORWARDING                       19
#define DHO_NON_LOCAL_SOURCE_ROUTING            20
#define DHO_POLICY_FILTER                       21
#define DHO_MAX_DGRAM_REASSEMBLY                22
#define DHO_DEFAULT_IP_TTL                      23
#define DHO_PATH_MTU_AGING_TIMEOUT              24
#define DHO_PATH_MTU_PLATEAU_TABLE              25
#define DHO_INTERFACE_MTU                       26
#define DHO_ALL_SUBNETS_LOCAL                   27
#define DHO_BROADCAST_ADDRESS                   28
#define DHO_PERFORM_MASK_DISCOVERY              29
#define DHO_MASK_SUPPLIER                       30
#define DHO_ROUTER_DISCOVERY                    31
#define DHO_ROUTER_SOLICITATION_ADDRESS         32
#define DHO_STATIC_ROUTES                       33
#define DHO_TRAILER_ENCAPSULATION               34
#define DHO_ARP_CACHE_TIMEOUT                   35
#define DHO_IEEE802_3_ENCAPSULATION             36
#define DHO_DEFAULT_TCP_TTL                     37
#define DHO_TCP_KEEPALIVE_INTERVAL              38
#define DHO_TCP_KEEPALIVE_GARBAGE               39
#define DHO_NIS_DOMAIN                          40
#define DHO_NIS_SERVERS                         41
#define DHO_NTP_SERVERS                         42
#define DHO_VENDOR_ENCAPSULATED_OPTIONS         43
#define DHO_NETBIOS_NAME_SERVERS                44
#define DHO_NETBIOS_DD_SERVER                   45
#define DHO_NETBIOS_NODE_TYPE                   46
#define DHO_NETBIOS_SCOPE                       47
#define DHO_FONT_SERVERS                        48
#define DHO_X_DISPLAY_MANAGER                   49
#define DHO_DHCP_REQUESTED_ADDRESS              50
#define DHO_DHCP_LEASE_TIME                     51
#define DHO_DHCP_OPTION_OVERLOAD                52
#define DHO_DHCP_MESSAGE_TYPE                   53
#define DHO_DHCP_SERVER_IDENTIFIER              54
#define DHO_DHCP_PARAMETER_REQUEST_LIST         55
#define DHO_DHCP_MESSAGE                        56
#define DHO_DHCP_MAX_MESSAGE_SIZE               57
#define DHO_DHCP_RENEWAL_TIME                   58
#define DHO_DHCP_REBINDING_TIME                 59
#define DHO_VENDOR_CLASS_IDENTIFIER             60
#define DHO_DHCP_CLIENT_IDENTIFIER              61
#define DHO_NWIP_DOMAIN_NAME                    62
#define DHO_NWIP_SUBOPTIONS                     63
#define DHO_USER_CLASS                          77
#define DHO_FQDN                                81
#define DHO_DHCP_AGENT_OPTIONS                  82
#define DHO_CLIENT_LAST_TRANSACTION_TIME        91
#define DHO_ASSOCIATED_IP                       92
#define DHO_CLIENT_SYSTEM						93	/* RFC4578 */
#define DHO_CLIENT_NDI							94	/* RFC4578 */
#define DHO_LDAP								95	/* RFC3679 */
#define DHO_UUID_GUID							97
#define DHO_USER_AUTH							98
#define DHO_SUBNET_SELECTION                    118	/* RFC3011! */
#define DHO_DOMAIN_SEARCH                       119	/* RFC3397 */
#define DHO_VIVCO_SUBOPTIONS                    124
#define DHO_VIVSO_SUBOPTIONS                    125
/* The DHO_AUTHENTICATE option is not a standard yet, so I've
   allocated an option out of the "local" option space for it on a
   temporary basis.  Once an option code number is assigned, I will
   immediately and shamelessly break this, so don't count on it
   continuing to work. */
#define DHO_AUTHENTICATE                        210
#define DHO_END                                 255

#endif
