
#include "Server.h"

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

    //this_thread::sleep_for(chrono::seconds(15));
    //thread accept(&MySerialServer :: acceptingClients, this);
    //thread accept(&MySerialServer :: acceptingClients, this);
    // [=] mean that send clientHandler by value so when we'll do detach the clientHandler won't be deleted.
    thread accept([=] {this->acceptingClients(clientHandler);});
    accept.detach();

}

void MySerialServer :: acceptingClients(ClientHandler *clientHandler) {

    while (!isDone) {
        // accepting a client
        socklen_t size;
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &size);
        if (client_socket == -1) {
            std::cerr << "Error accepting client or timeout" << std::endl;
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

