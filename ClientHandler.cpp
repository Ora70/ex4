
#include "ClientHandler.h"

/*
 * accept string from client and reverse it and return that.
 * the connection stops when the client send "end".
 */
void MyTestClientHandle :: handelClient(int client_socket) {

    char data[1024] = {'\0'};
    int readData = read(client_socket, data, 1000); //read data from client
    if (readData == -1) {
        std::cout << "problem in reading" << std::endl;
    } else {
        while (strcmp(data, "end") != 0 && strcmp(data, "end\r\n") != 0 && strcmp(data, "end\n") != 0) {
            string problem = data;
            //convert the problem to string of numbers.
            hash<string> hasher;
            string hashedProb = to_string(hasher(problem));
            string solution;
            //if solution in cache return it. else solve the problem return it, and enter to cache.
            if (cache->solutionExists(hashedProb)) {
                solution = cache->getSolution(hashedProb);
            } else {
                solution = solver->solve(problem);
                cache->SaveNewProblem(hashedProb, solution);
            }
            solution += "\n";
            //int flag = 1;
            const char* reply = solution.c_str(); //convert string to char*
            /*if (setsockopt(client_socket, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) < 0) { //flush
                std::cout << "Failing flush" << std::endl;
            }*/
            //send to client the solution.
            int update = send(client_socket, reply, strlen(reply), 0);
            if (update == -1) {
                std::cout << "error in sending" << std::endl;
                break;
            }
            memset(data, '\0', 1000);
            readData = read(client_socket, data, 1000); //read data from client
            if (readData == -1) {
                std::cout << "problem in reading" << std::endl;
                break;
            }
        }
    }
}

/*
 * accept matrix from client and return the shortest path from start to goal.
 */
void MyClientHandler ::handelClient(int client_socket) {

    string matrix;

    while(true) {
        char data[1024] = {'\0'};
        int readData = read(client_socket, data, 1000); //read data from client
        if (readData == -1) {
            std::cout << "problem in reading" << std::endl;
        } else {
            int placeOfEnd = findEnd(data);
            if (placeOfEnd != -1) { //there is end
                data[placeOfEnd] = '\0'; // the string ends before "end".
                matrix += data;
                break;
            }
            matrix += data;
        }
    }
    //convert the matrix to string of numbers.
    hash<string> hasher;
    string hashedProb = to_string(hasher(matrix));
    string solution;
    //if solution in cache return it. else solve the problem return it, and enter to cache.
    if (cache->solutionExists(hashedProb)) {
        solution = cache->getSolution(hashedProb);
    } else {
        solution = solver->solve(createMatrixFromString(matrix));
        cache->SaveNewProblem(hashedProb, solution);
    }
    //int flag = 1;
    const char *reply = solution.c_str(); //convert string to char*
    /*if (setsockopt(client_socket, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) < 0) { //flush
        std::cout << "Failing flush" << std::endl;
    }*/
    //send solution to client.
    int update = send(client_socket, reply, strlen(reply), 0);
    if (update == -1) {
        std::cout << "error in sending" << std::endl;
    }
}

/*
 * find the end of the matrix and return it's place.
 */
int MyClientHandler :: findEnd(char data[]) {
    int length = strlen(data);
    for (int i = 0; i < length; i++) {
        if (data[i] == 'e') {
            return i;
        }
    }
    return -1; //no end
}

/*
 * create object MatrixDomain from the string that been given from client.
 */
MatrixDomain MyClientHandler ::createMatrixFromString(string data) {

    vector<int> *matValues = new vector<int>();
    vector<char*> row;
    int numCol = 0, flag = 0;

    char *token = strtok(strdup(data.c_str()), "\n");

    while(token != NULL) { //split to rows
        row.push_back(token);
        token = strtok(NULL, "\n");
    }

    //initialize goal and start and remove their rows from row vector.
    char* goal = strtok(row.back(), ", ");
    char* gRow = goal;
    goal = strtok(NULL, ", ");
    char* gCol = goal;
    row.pop_back();
    char* start = strtok(row.back(), ", ");
    char* sRow = start;
    start = strtok(NULL, ", ");
    char* sCol = start;
    row.pop_back();

    for (auto it = row.begin(); it != row.end(); it++) { //split to cost
        char *cost = strtok(*it, ", ");
        while(cost != NULL) {
            if (!flag) {
                numCol++;
            }
            matValues->push_back(atoi(cost));
            cost = strtok(NULL, ", ");
        }
        flag++;
    }
    return MatrixDomain(matValues->data(), row.size(), numCol, pair<int, int>(atoi(sRow), atoi(sCol)),
            pair<int, int>(atoi(gRow), atoi(gCol)));
}

