/*	@file nyoci-plat-uip.h
**	@author Robert Quattlebaum <darco@deepdarc.com>
**
**	Copyright (C) 2017 Robert Quattlebaum
**
**	Permission is hereby granted, free of charge, to any person
**	obtaining a copy of this software and associated
**	documentation files (the "Software"), to deal in the
**	Software without restriction, including without limitation
**	the rights to use, copy, modify, merge, publish, distribute,
**	sublicense, and/or sell copies of the Software, and to
**	permit persons to whom the Software is furnished to do so,
**	subject to the following conditions:
**
**	The above copyright notice and this permission notice shall
**	be included in all copies or substantial portions of the
**	Software.
**
**	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
**	KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
**	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
**	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
**	OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
**	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
**	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
**	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef NYOCI_nyoci_plat_uip_internal_h
#define NYOCI_nyoci_plat_uip_internal_h

#include "net/ip/uip.h"

#if !defined(htonl)
#define htonl(x)		uip_htonl(x)
#define ntohl(x)		uip_ntohl(x)
#define htons(x)		uip_htons(x)
#define ntohs(x)		uip_ntohs(x)
#endif

#if !UIP_CONF_IPV6

#ifndef uip_is_addr_mcast
#define uip_is_addr_mcast(addrptr)		(*(const uint8_t*)(addrptr)==224)
#endif

#ifndef uip_is_addr_unspecified
#define uip_is_addr_unspecified(addrptr)		(*(addrptr)==0)
#endif

#ifndef uip_is_addr_loopback
#define uip_is_addr_loopback(addrptr)		(*(const uint8_t*)(addrptr)==127)
#endif
#endif

#define NYOCI_IS_ADDR_MULTICAST uip_is_addr_mcast
#define NYOCI_IS_ADDR_UNSPECIFIED uip_is_addr_unspecified
#define NYOCI_IS_ADDR_LOOPBACK uip_is_addr_loopback

#if UIP_CONF_IPV6
#define NYOCI_COAP_MULTICAST_ALLDEVICES_ADDR	COAP_MULTICAST_IP6_LL_ALLDEVICES
#else
#define NYOCI_COAP_MULTICAST_ALLDEVICES_ADDR	COAP_MULTICAST_IP4_ALLDEVICES
#endif

NYOCI_BEGIN_C_DECLS

struct nyoci_plat_s {
	struct uip_udp_conn*	udp_conn;
	nyoci_sockaddr_t	sockaddr_local;
	nyoci_sockaddr_t	sockaddr_remote;
	nyoci_session_type_t session_type;
};

NYOCI_END_C_DECLS

#if UIP_CONF_IPV6
#define NYOCI_ADDR_NTOP(dest, len, addr) sprintf(dest,"%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7], ((uint8_t *)addr)[8], ((uint8_t *)addr)[9], ((uint8_t *)addr)[10], ((uint8_t *)addr)[11], ((uint8_t *)addr)[12], ((uint8_t *)addr)[13], ((uint8_t *)addr)[14], ((uint8_t *)addr)[15])
#else
#define NYOCI_ADDR_NTOP(dest, len, addr) sprintf(dest,"%u.%u.%u.%u", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3])
#endif

#endif
