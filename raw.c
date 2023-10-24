#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>

int main()
{
    int sock = socket(AF_PACKET, SOCK_RAW, 0);   // 0 for proto??
    if(sock < 0)
    {
        perror("Failed to create socket");
        exit(1);
    }


    return 0;
}