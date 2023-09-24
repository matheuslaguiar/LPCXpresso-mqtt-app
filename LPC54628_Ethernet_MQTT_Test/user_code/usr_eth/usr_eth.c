/*
 * usr_eth.c
 *
 *  Created on: 7 de set de 2023
 *      Author: matheus
 */

#include "../usr_eth/usr_eth.h"
#include "lwip/init.h"
#include "lwip/tcp.h"
#include "board.h"

struct tcp_pcb	*tcp_block;

int8_t usr_eth_init() {
	lwip_init();
	return 0;
}
