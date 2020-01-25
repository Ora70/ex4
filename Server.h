
#ifndef EXE4_SERVER_H
#define EXE4_SERVER_H

#include <sys/socket.h>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <thread>
#include <sys/time.h>
#include "ClientHandler.h"
using namespace std;

namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *clientHandler) = 0;
        virtual void stop() = 0;
        virtual ~Server() {}
    };
}

class MySerialServer:public server_side::Server {
    bool isDone;
    int socketfd;
    sockaddr_in address;
    void acceptingClients(ClientHandler *clientHandler);
public:
    MySerialServer() {
        isDone = false;
    }
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
    virtual ~MySerialServer() {}
};

class MyParallelServer : public server_side::Server {
    std::vector<std::thread> threads;
    int socketfd;
    sockaddr_in address;
    bool isDone;
    void openParallelSocket(ClientHandler *clientHandler);
    void handel(ClientHandler *clientHandler, int client_socket);
public:
    MyParallelServer() {
        isDone = false;
    }
    virtual void open(int port, ClientHandler *clientHandler);
    virtual void stop();
    virtual ~MyParallelServer() {}
};

#endif //EXE4_SERVER_H
