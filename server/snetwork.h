#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server{
private:
    int socketId;
    int clientId; // This should also be in a data structure to support multiple clients.
    int port;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr; // The struct that holds the client address info. This should be a list of connected clients later


    // Binds the socket to the Server address
    int bindSocket()
    {
        if(bind(socketId, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
        {
            printf("Error cannot bind socket");
            return 1;
        }
        return 0;
    }

public:

    void readMessage(char *message, int length)
    {
        read(clientId, message, 256);
    }

    void closeConnection()
    {
        close(socketId);
        close(clientId);
    }

    Server(int port)
    :port(port)
    {
        socketId = socket(AF_INET, SOCK_STREAM, 0);

        bzero((char *)&serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);
         
        return;
    }
    
    ~Server()
    {
        this->closeConnection();
    }


    // Starts listening on the provided port for incoming messages
    void startServer()
    {
        this->bindSocket();
        listen(socketId, 5);
        printf("Server started\n");

        socklen_t clilen;
        clilen = sizeof(clientAddr);

        clientId = accept(socketId, (struct sockaddr *) &clientAddr, &clilen); // This function is blocking and will only return when a client connects 
        printf("Client connected, id: %d\n", clientId);

        int nBytes;
        char buffer[256];
        bzero(buffer, 256);

        //nBytes = read(clientId, buffer, 256);
        //printf("message: %s", buffer);
    }

};
