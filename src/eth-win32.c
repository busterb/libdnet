/*
 * eth-win32.c
 *
 * Copyright (c) 2000 Dug Song <dugsong@monkey.org>
 *
 * $Id: eth-win32.c 613 2005-09-26 02:46:57Z dugsong $
 */

#include "config.h"

/* XXX - VC++ 6.0 bogosity */
#define sockaddr_storage sockaddr
#undef sockaddr_storage

#include <errno.h>
#include <stdlib.h>

#include "dnet.h"

int
eth_get_pcap_devname(const char *intf_name, char *pcapdev, int pcapdevlen);

eth_t * eth_open(const char *device)
{
	return (NULL);
}

ssize_t
eth_send(eth_t *eth, const void *buf, size_t len)
{
	return (-1);
}

eth_t *
eth_close(eth_t *eth)
{
	return (NULL);
}

int
eth_get(eth_t *eth, eth_addr_t *ea)
{
	return (-1);
}

int
eth_set(eth_t *eth, const eth_addr_t *ea)
{
	return (-1);
}
