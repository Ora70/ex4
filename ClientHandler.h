
#ifndef EXE4_CLIENTHANDLER_H
#define EXE4_CLIENTHANDLER_H

#include "Solver.h"
#include "Cache.h"
#include "Searchable.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <netinet/tcp.h>
#include <functional>
#include <string.h>

using namespace std;

/*
 * ClientHandler Interface.
 */
class ClientHandler {
public:
    virtual void handelClient(int client_socket) = 0;
    virtual ~ClientHandler() {}
};

class MyTestClientHandle : public ClientHandler {
    Solver<string, string> *solver;
    CacheManager<string, string> *cache;
public:
    MyTestClientHandle(Solver <string, string> *solve, CacheManager<string, string> *cacheM) {
        solver = solve;
        cache = cacheM;
    }
    virtual void handelClient(int client_socket);
    virtual ~MyTestClientHandle() {}
};

class MyClientHandler : public ClientHandler {
    Solver<string, MatrixDomain> *solver;
    CacheManager<string, string> *cache;
    int findEnd(char data[]);
    MatrixDomain createMatrixFromString(string);
public:
    MyClientHandler(Solver <string, MatrixDomain> *solve, CacheManager<string, string> *cacheM) {
        solver = solve;
        cache = cacheM;
    }
    MyClientHandler(const MyClientHandler& ch) {
        solver = ch.solver;
        cache = ch.cache;
    }
    virtual void handelClient(int client_socket);
    virtual ~MyClientHandler() {}
};

#endif //EXE4_CLIENTHANDLER_H
