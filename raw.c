#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/ethernet.h>

const int max_ethframe_size = 1600;
const int raw_hex_dump_num_bytes_per_block = 8;

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

    printf("\n\n\n");

}

int main()
{
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));   // 0 for proto??
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

        raw_hex_dump(num_read, buff);
    }


    return 0;
}