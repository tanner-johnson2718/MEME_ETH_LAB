// Some C socket code that messes with raw sockets. For now this program is a
// poor mans wire shark and just dumps all frames seen on all interfaces.

// |---------------------------------------------------------------------------
// | Key Sys Calls
// | ---------------------------------------------------------------------------
// | 
// | int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
// | num_read = recv(sock, buff, max_ethframe_size, 0);
// |
// |---------------------------------------------------------------------------


// |---------------------------------------------------------------------------
// | Key Commands
// |---------------------------------------------------------------------------
// | 
// | `ip a` | Shows all net interfaces, IP, and MAC 
// | `arp`  | Shows all resolved MACs via ARP
// |
// |---------------------------------------------------------------------------


// |---------------------------------------------------------------------------
// | 802.3 Layer 2 Frame (Non VlAN i.e. 802.1Q)
// |---------------------------------------------------------------------------
// |
// | MAC DST | MAC SRC | TAG | PAYLOAD | CRC | 
// |    6    |    6    |  2  | 46-1500 |  4  |
// |---------------------------------------------------------------------------


// |---------------------------------------------------------------------------
// | Questions 
// |---------------------------------------------------------------------------
// | 
// | Is a call to recv() garmented to return 1 and only 1 packet?
// | Max Lengths w/ and w/out vlan shit??
// | What happens when I dont call recv does that ring buffer fill??
// |
// |---------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/ethernet.h>

const int max_ethframe_size = 1522;
const int raw_hex_dump_num_bytes_per_block = 8;

const int mac_len = 6;
const int eth_tag_len = 2;
const int crc_len = 4;
const int mac_dest_off = 0;
const int mac_src_off = 6;
const int eth_tag_offset = 12;
const int payload_offset = 14;

void raw_hex_dump(int len, unsigned char* buff)
{
    int i;
    for(i = 0; i < len; ++i)
    {

        if(i % raw_hex_dump_num_bytes_per_block != 0)
        {
            printf(" %02x", buff[i]);
            continue;
        }

        if(i != 0)
        {
            printf("\n");
        }

        printf("0x%02x  |  %02x", i, buff[i]);
    }

    printf("\n");

}

void frame_pretty_print(int len, unsigned char* buff)
{
    int i, off = mac_dest_off;
    
    printf("------------------------------------------------------------\n");

    printf("MAC DST = ");
    for(i = 0; i < mac_len; ++i)
    {
        printf("%02x ", buff[off + i]);
    }
    printf("\n");

    off = mac_src_off;
    printf("MAC SRC = ");
    for(i = 0; i < mac_len; ++i)
    {
        printf("%02x ", buff[off + i]);
    }
    printf("\n");

    off = eth_tag_offset;
    printf("ETH TAG = %02x %02x", buff[off], buff[off+1]);
    printf("\n");

    off = len - crc_len;
    printf("CRC     = %02x %02x %02x %02x\n", buff[off], buff[off+1], buff[off+2], buff[off+3]);

    off = payload_offset;
    printf("PAYLOAD = \n\n");
    raw_hex_dump(len - off - crc_len, buff + off);

    printf("------------------------------------------------------------\n\n");

}

// Input is a full eth frame
unsigned char* parse_MAC_dest(int len, unsigned char* buff)
{
    return buff + mac_dest_off;
}

// Input is a full eth frame
unsigned char* parse_MAC_src(int len, unsigned char* buff)
{
    return buff + mac_src_off;
}

int main()
{
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(sock < 0)
    {
        perror("Failed to create socket");
        exit(1);
    }

    ssize_t num_read = 0;
    unsigned char* buff = malloc(max_ethframe_size);

    while(1)
    {
        num_read = recv(sock, buff, max_ethframe_size, 0);

        // recv should only return this in failure as we are using a blocking
        // call to recv
        if(num_read < 0)
        {
            perror("recv failed");
            exit(1);
        }

        if(num_read == max_ethframe_size)
        {
            printf("WARNING, recv packet of max length\n");
        }

        frame_pretty_print(num_read, buff);
    }

    free(buff);
    return 0;
}