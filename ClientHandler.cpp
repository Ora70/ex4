
#include "ClientHandler.h"

void MyTestClientHandle :: handelClient(int client_socket) {

    char data[1000] = {'\0'};
    int readData = read(client_socket, data, 1000); //read data from client
    if (readData == -1) {
        std::cout << "problem in reading" << std::endl;
    } else {
        while (strcmp(data, "end") != 0 && strcmp(data, "end\r\n") != 0 && strcmp(data, "end\n") != 0) {
            string problem = data;
            hash<string> hasher;
            unsigned long hashedProb = hasher(problem);
            string solution;
            if (cache->solutionExists(hashedProb)) {
                solution = cache->getSolution(hashedProb);
            } else {
                solution = solver->solve(problem);
                cache->SaveNewProblem(hashedProb, solution);
            }
            solution += "\n";
            int flag = 1;
            const char* reply = solution.c_str(); //convert string to char*
            if (setsockopt(client_socket, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) < 0) { //flush
                std::cout << "Failing flush" << std::endl;
            }
            int update = send(client_socket, reply, strlen(reply), 0);
            if (update == -1) {
                std::cout << "error in sending" << std::endl;
                break;
            }
            memset(data, '\0', 1000);
            int readData = read(client_socket, data, 1000); //read data from client
            if (readData == -1) {
                std::cout << "problem in reading" << std::endl;
                break;
            }
        }
    }
}

