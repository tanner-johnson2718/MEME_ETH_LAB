// gen.c raw ethernet packet generator. Will send packets to a hard coded MAC 
// out a hard coded interface. Will have hard coded params for setting size and
// freq of packet transmits as well as a max number of packets sent

// Key Sys Calls:
//   - send
//   - socket
//   - setsockopt

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

const int num_packets_to_send = 1;
const int delay_ms = 1000;

const int packet_size = 128;       // includes header, not crc though
const char payload_byte = 0xA5;    // byte repeated to fill packet
const unsigned char mac_src[6] = {0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c};
const unsigned char mac_dst[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
const unsigned char tag[2] = {0x69, 0x69};

const char* interface_name = "lo";
// const char* interface_name = "enp2s0";
// const char* interface_name = "wlp5s0";

int main()
{
    unsigned char* packet_buffer = NULL;
    int sock = 0, ret = 0, i = 0, num_sent = 0;


    // Allocate Buffer 
    packet_buffer = malloc(packet_size);
    if(packet_buffer == NULL)
    {
        perror("Malloc Failed to Create Packet Buffer");
        exit(1);
    }

    // Populate packet with payload byte
    for(i = 0; i < packet_size; ++i)
    {
        packet_buffer[i] = payload_byte;
    }

    // Fill in eth headers
    for(i = 0; i < 6; ++i)
    {
        packet_buffer[i] = mac_dst[i];
        packet_buffer[i+6] = mac_src[i];
    }
    packet_buffer[12] = tag[0];
    packet_buffer[13] = tag[0];

    // Open a socket
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sock < 1)
    {
        perror("Failed to create socket");
        exit(1);
    }

    // Bind it to the specified interface
    ret = setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, 
                     interface_name, strlen(interface_name));
    if(ret < 0)
    {
        perror("Failed to bind socket");
        exit(1);
    }

    // Transmit Data
    for(i = 0 ; i < num_packets_to_send; ++i)
    {
        num_sent = send(sock, packet_buffer, packet_size, 0);

        printf("Num Bytes Sent = %d\n", num_sent);
    }

    free(packet_buffer);
    close(sock);
}