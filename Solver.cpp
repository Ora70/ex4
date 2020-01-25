
#include "Solver.h"
#include "Searcher.h"

/*
 * return the reverse of the string.
 */
string StringReverser:: solve(string problem) {
    int len = problem.length(), i;
    for (i=0; i < len/2; i++) {
        swap(problem[i], problem[len - i - 1]);
    }
    return problem;
}

/*
 * find the solution of the matrix (in this assignment find the shortest path in the matrix from start to goal) by
 * one of the algorithm and return it (in this assignment it's best first search).
 */
string SolverForMatrix ::solve(MatrixDomain problem) {
    BestFirstSearch<pair<int,int>> *bestFirstSearch = new BestFirstSearch<pair<int,int>>();
    string solution = bestFirstSearch->search(&problem);
    delete bestFirstSearch;
    return solution;
}

