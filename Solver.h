
#ifndef EXE4_SOLVER_H
#define EXE4_SOLVER_H

#include <string>
#include "Searchable.h"
using namespace std;

/*
 * Solver interface
 */

template <typename Solution, typename Problem>
class Solver {
public:
    virtual Solution solve(Problem problem) = 0;
    virtual ~Solver(){}
};

class StringReverser: public Solver<string, string> {
public:
    virtual string solve(string problem);
    virtual ~StringReverser() {}
};

class SolverForMatrix : public Solver<string, MatrixDomain> {
public:
    virtual string solve(MatrixDomain problem);
    virtual ~SolverForMatrix() {}
};
#endif //EXE4_SOLVER_H
