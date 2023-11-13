#ifndef __LIB_ETH_H
#define __LIB_ETH_H


#define _GNU_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <linux/if_packet.h>
#include <netinet/ether.h>
#include <sys/ioctl.h>
#include <time.h>

int parse_if_index(char* if_str, int sock);
int parse_mac(char* str, unsigned char* mac);
int pack_frame(unsigned char* packet_buffer, int len, unsigned char* mac_src, 
                                                      unsigned char* mac_dst,
                                                      unsigned char* tag,
                                                      unsigned char payload_byte);
int libEth_bind(int sock, int if_index);

#endif