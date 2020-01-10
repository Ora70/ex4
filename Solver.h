
#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

#include <string>

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
};

#endif //EX4_SOLVER_H
