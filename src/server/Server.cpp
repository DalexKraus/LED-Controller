#include "Server.h"
#include "PacketType.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define MAX_CLIENTS 8

bool Server::start(int bindPort, LEDController* controller)
{
    _controllerInstance = controller;
    _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sockfd < 0)
    {
        printf("[ERROR] Unable to create server socket!\n");
        return false;
    }

    //Apply socket options
    int opt = 1;
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        printf("[ERROR] Unable to apply options to socket!\n");
        return false;
    }

    struct sockaddr_in address;
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(bindPort);

    //Bind socket
    if (bind(_sockfd, (struct sockaddr*) &address, sizeof(address)) < 0)
    {
        printf("[ERROR] Unable to bind to port %d!\n", bindPort);
        return false;
    }

    _isRunning = true;
    printf("[INFO] Server started on port %d\n", bindPort);
    
    //Listen for clients
    _listenThread = std::thread(&Server::_t_acceptClients, this);

    return true;
}

void Server::stop()
{
    _isRunning = false;
    
    //Close all open connections
    for (auto& clientHandle : _clients)
    {
        clientHandle->disconnect();
        deleteClient(&clientHandle);
    }
    _clients.clear();
}

void Server::sendToClient(ClientHandle* handle, const void* data)
{
    send(handle->sockfd(), data, sizeof(data), 0);
}

void Server::deleteClient(ClientHandle** clientHandle)
{
    //Remove from clients list
    _clients.erase(std::remove(_clients.begin(), _clients.end(), *clientHandle), _clients.end());

    (*clientHandle)->~ClientHandle();
    free(*clientHandle);
    *clientHandle = nullptr;
}

void ClientHandle::disconnect()
{
    printf("[INFO] Client %s has disconnected.\n", getIPString());
    _isConnected = false;
}

void Server::_t_acceptClients()
{
    while (_isRunning)
    {
        if (listen(_sockfd, MAX_CLIENTS) < 0)
        {
            printf("[CRITICAL] An error occured while trying to listen for clients!\n");
            continue;
        }

        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);

        int client_sockfd = accept(_sockfd, (struct sockaddr*) &client_addr, &len);
        if (client_sockfd < 0)
        {
            printf("[CRITICAL] An error occurred while trying to accept a client connection!\n");
            continue;
        }

        ClientHandle* handle = new ClientHandle(client_sockfd, client_addr, this);
        _clients.push_back(handle);

        printf("[INFO] Client '%s' connected\n", handle->getIPString());

        //Send connection acknowledge packet
        char packet = __PCK_ACKNOWL;
        sendToClient(handle, &packet);

        //Start own thread to handle the connection with the client
        std::thread handleThread(&Server::_t_handleClient, this, handle);
        handleThread.detach();
    }
}

void Server::_t_handleClient(ClientHandle* clientHandle)
{
    char buffer[1024];

    while (_isRunning)
    {
        memset(buffer, 0, sizeof(buffer));

        //Read from client
        ssize_t readBytes = read(clientHandle->sockfd(), buffer, sizeof(buffer));
        if (readBytes < 0)
        {
            //The client has terminated the connection
            clientHandle->disconnect();

            //Delete the client, and stop the thread by breaking
            deleteClient(&clientHandle);
            break;
        }
        else
        {
            //Parse packets
            char packetType = buffer[0];
            switch (packetType)
            {
                case __PCK_REQUEST_COLOR:
                    COLOR currentColor = _controllerInstance->getColor();
                    printf("color: %d %x\n", currentColor, currentColor);
                    sendToClient(clientHandle, &currentColor);
            }
        }
    }
}
