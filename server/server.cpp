#include <stdio.h>

#include "snetwork.h"

int main()
{
    Server server(25565);
    server.startServer();

    char message[256];

    while(strcmp(message, "quit\n") != 0){
        bzero(message, 256);
        server.readMessage(message, 256);
        printf("message: %s", message);
    }

    server.closeConnection();

    return 0;
}
