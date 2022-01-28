#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Client{
private:
    int socketId;
    int port;

    struct hostent *server;
    struct sockaddr_in serverAddr; 

public:

    void sendMessage(const char* message, int length)
    {
        write(socketId, message, length);
    }
    
    // void recres should go here and place server responses in a queue of messages that can be read in order


    void start() // NOTE: these connect methods should probably return an error code so the open sockets can be cleaned up
    {
        if(connect(socketId, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        {
            printf("Failed to connect to server\n");
            return; // Should return code
        }
        printf("Connection successfull\n");

        return;
    }


    void closeConnection()
    {
        close(socketId);
    }


    Client(const char *hostname, int port)
    :port(port)
    {
        socketId = socket(AF_INET, SOCK_STREAM, 0);
        server = gethostbyname(hostname);

        if(server == NULL)
        {
            printf("Cannot connect to %s:%d\n", hostname, port);
            exit(0);
        }

        bzero((char *)&serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serverAddr.sin_addr, server->h_length);
        serverAddr.sin_port = htons(port);

        return;
    }


    ~Client()
    {
        this->closeConnection();
    }
    
};
