
#ifndef EXE4_CLIENTHANDLER_H
#define EXE4_CLIENTHANDLER_H

#include "Solver.h"
#include "Cache.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <netinet/tcp.h>
#include <functional>

using namespace std;

/*
 * ClientHandler Interface.
 */
class ClientHandler {
public:
    virtual void handelClient(int client_socket) = 0;
};

class MyTestClientHandle : public ClientHandler {
    Solver<string, string> *solver;
    CacheManager<string, unsigned long > *cache;
public:
    MyTestClientHandle(Solver <string, string> *solve, CacheManager<string, unsigned long> *cacheM) {
        solver = solve;
        cache = cacheM;
    }
    virtual void handelClient(int client_socket);
};

#endif //EXE4_CLIENTHANDLER_H
