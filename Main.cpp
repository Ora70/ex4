
#include "Main.h"

int boot::Main :: main(int port) {

    MyParallelServer server;
    FileCacheManager cache;
    // in SolverForMatrix.solve we wrote the algorithm we are using so that way we wont need to clone the
    //client handler because it will create for each matrix new algorithm.
    SolverForMatrix matrixSolver;
    MyClientHandler clientHandler(&matrixSolver, &cache);
    server.open(port, &clientHandler);
    return 0;
}

