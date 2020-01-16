
#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <utility>
#include <string>
#include <list>
#include <limits>
#include <vector>
using namespace std;

class State {
    vector<double> cost;
    pair<int, int> position;
    State *cameFrom;
    string stringPos;

public:
    State(pair<int, int> pos, State *from, double theCost);
    State(int i, int j, State *from, double theCost): State(pair<int,int>(i,j), from, theCost) {}
    State(pair<int, int> pos, State *from, vector<double> theCost);
    State(int i, int j, State *from, vector<double> theCost): State(pair<int,int>(i,j), from, theCost) {}
    State(State* s) {
        position = s->getPosition();
        cost = s->getVectorCost();
        cameFrom = s->getPrevious();
        stringPos = s->getStringPos();
    }
    State* getPrevious();
    void SetPrevious(State *from);
    double getCost() const;
    void setCost(double c);
    void setCost(vector<double> c);
    pair<int, int> getPosition() const;
    bool equals(State *s);
    string getStringPos() const;
    vector<double> getVectorCost() const;
};

bool operator<(const State & s1, const State & s2);
bool operator==(const State & s1, const State & s2);

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

class MatrixDomain: public Searchable<State*> {
    State* start;
    State* goal;
    int *matrix;
    int rowSize;
    int colSize;

public:
    MatrixDomain(int* mat, int row, int col, pair<int, int> theStart, pair<int, int> end);
    virtual State* getInitialState();
    virtual State* getGoalState();
    virtual list<State*> getAllPossibleStates(State* s);
};

#endif //EX4_SEARCHABLE_H
