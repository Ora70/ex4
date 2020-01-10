
#include "Solver.h"

string StringReverser:: solve(string problem) {
    int len = problem.length(), i;
    for (i=0; i < len/2; i++) {
        swap(problem[i], problem[len - i - 1]);
    }
    return problem;
}
