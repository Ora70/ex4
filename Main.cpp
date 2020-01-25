
#include "Main.h"

int boot::Main :: main(int port) {

    MyParallelServer server;
    FileCacheManager *cm = new FileCacheManager();
    // in SolverForMatrix.solve we wrote the algorithm we are using so that way we wont need to clone the
    //client handler because it will create for each matrix new algorithm.
    Solver<string, MatrixDomain> *sm = new SolverForMatrix();
    ClientHandler *ch = new MyClientHandler(sm, cm);
    server.open(port, ch);
    this_thread::sleep_for(chrono::seconds(200));
    server.stop();
    delete ch;
    delete sm;
    delete cm;
    return 0;
}

