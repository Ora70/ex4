
#include "Server.h"

/*
 * open serial server and in separate thread accept it's clients.
 */
void MySerialServer :: open(int port, ClientHandler *clientHandler) {

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        std::cerr << "Could not create a socket" << std::endl;
    }

    //initialize the sockaddr obj.
    address.sin_family = AF_INET; //in means IP4
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //bind socket to IP address
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }

    //making socket listen to the port
    if (listen(socketfd, 10) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // set time out
    struct timeval timeout;
    timeout.tv_sec = 120;
    timeout.tv_usec = 0;
    if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0 ) {
        std::cout << "Fail with timeout" << std::endl;
    }

    thread acceptThread([=] {this->acceptingClients(clientHandler);});
    acceptThread.join();

}

/*
 * accepting client handel it, close the connection and accept the next one until stop is executed.
 */
void MySerialServer :: acceptingClients(ClientHandler *clientHandler) {

    while (!isDone) {
        // accepting a client
        socklen_t size;
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &size);
        if (client_socket == -1) {
            stop();
        } else {
            std::cout << "client accepted" << std::endl;
            clientHandler->handelClient(client_socket);
            close (client_socket);
        }
    }
    close(socketfd); //closing the listening socket
}

void MySerialServer :: stop() {
    isDone = true;
}

/*
 * open parallel server and in separate thread accept it's clients, for each client open separate thread to handel them.
 */
void MyParallelServer ::open(int port, ClientHandler *clientHandler) {

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        std::cerr << "Could not create a socket" << std::endl;
    }

    //initialize the sockaddr obj.
    address.sin_family = AF_INET; //in means IP4
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //bind socket to IP address
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }

    //making socket listen to the port
    if (listen(socketfd, 10) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // set time out
    struct timeval timeout;
    timeout.tv_sec = 120;
    timeout.tv_usec = 0;
    if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0 ) {
        std::cout << "Fail with timeout" << std::endl;
    }

    thread parallelThread([=] { this->openParallelSocket(clientHandler); });
    parallelThread.join();
}

/*
 * accepting clients. for each client that been accepted open separete thread to handel it.
 */
void MyParallelServer ::openParallelSocket(ClientHandler *clientHandler) {

    while (!isDone) {
        socklen_t size;
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &size);
        if (client_socket < 0) {
            stop();
        } else {
            std::cout << "client accepted" << std::endl;
            threads.push_back(std::thread([=] { this->handel(clientHandler, client_socket); }));
        }
    }
}

/*
 * handel client and close the connection in the end.
 */
void MyParallelServer ::handel(ClientHandler *clientHandler, int client_socket) {

    clientHandler->handelClient(client_socket);
    close (client_socket);
}

/*
 * close the listening socket and close all the threads.
 */
void MyParallelServer :: stop() {
    isDone = true;
    close(socketfd);
    for (auto it = threads.begin(); it != threads.end(); it++) {
        it->join();
    }
}