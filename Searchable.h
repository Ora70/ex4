
#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <utility>
#include <string>
#include <list>
#include <limits>
using namespace std;

class State {
    double cost;
    pair<int, int> position;
    State *cameFrom;

public:
    State(pair<int, int> pos, State *from, double theCost);
    State(int i, int j, State *from, double theCost);
    State* GetPrevious();
    void SetPrevious(State from);
    double getCost() const;
    void setCost(double c);
    pair<int, int> getPosition();
    bool equals(State s);
};

bool operator<(const State & s1, const State & s2);

/*
 * searchable interface
 */
template <typename state>
class Searchable {
public:
    virtual state getInitialState() = 0;
    virtual state getGoalState() = 0;
    virtual list<state> getAllPossibleStates(state s) = 0;
};

class MatrixDomain: public Searchable<State> {
    State start;
    State goal;
    double *matrix;
    int rowSize;
    int colSize;

public:
    MatrixDomain(double* mat, int row, int col, pair<int, int> theStart, pair<int, int> end);
    virtual State getInitialState();
    virtual State getGoalState();
    virtual list<State> getAllPossibleStates(State s);
};

#endif //EX4_SEARCHABLE_H
