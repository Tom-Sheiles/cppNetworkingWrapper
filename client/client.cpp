#include <stdio.h>

#include "cnetwork.h"

int main()
{
    Client client("127.0.0.1", 25565);
    client.start();
    
    char message[256];

    while(strcmp(message, "quit\n") != 0){
        bzero(message, 256);
        fgets(message, 256, stdin);
        client.sendMessage(message, 256);
    }

    client.closeConnection();

    return 0;
}
