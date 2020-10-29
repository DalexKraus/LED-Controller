#ifndef __SERVER_H
#define __SERVER_H

#include <thread>
#include <vector>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#include "LEDController.h"

//Forward declaration, as ClientHandle needs the Server class
class Server;

class ClientHandle
{
    private:
        int                         _sockfd;
        struct sockaddr_in          _client_addr;
        Server*                     _serverInstance;
        const char*                 _ipString;
        bool                        _isConnected;

    public:
        ~ClientHandle()
        {
            close(_sockfd);
            free((void*) _ipString);
        }

        ClientHandle(int sockfd, struct sockaddr_in client_addr, Server* serverInstance)
            : _sockfd(sockfd), _client_addr(client_addr), _serverInstance(serverInstance)
            {
                //Fetch IP String
                _ipString = (const char*) malloc(INET_ADDRSTRLEN);
                struct in_addr ipAddress = client_addr.sin_addr;
                inet_ntop(AF_INET, &client_addr.sin_addr, (char*) _ipString, INET_ADDRSTRLEN);

                _isConnected = true;
            };

        const char*     getIPString()   { return _ipString;     }
        int             sockfd()        { return _sockfd;       }
        bool            connected()     { return _isConnected;  }
        void            disconnect();
};

class Server
{
    private:
        bool                        _isRunning;
        int                         _sockfd;
        std::thread                 _listenThread;
        std::thread                 _updateThread;
        std::vector<ClientHandle*>  _clients;
        LEDController*              _controllerInstance;

        void _t_acceptClients();
        void _t_handleClient(ClientHandle* clientHandle);
        void deleteClient(ClientHandle** clientHandle); 

    public:
        bool start(int bindPort, LEDController* controller);
        void stop();
        bool running()      { return _isRunning;        }
        int  clientCount()  { return _clients.size();   }
        
        void sendToClient(ClientHandle* handle, const void* data);
};

#endif