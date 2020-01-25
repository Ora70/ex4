
#ifndef EXE4_SEARCHABLE_H
#define EXE4_SEARCHABLE_H

#include <utility>
#include <string>
#include <list>
#include <limits>
#include <vector>
using namespace std;

template <typename POS>
class State {
    vector<double> cost;
    POS position;
    State *cameFrom;
    string stringRep;

public:
    State(POS pos, State *from, double theCost, string strRep) {
        position = pos;
        cameFrom = from;
        cost.push_back(theCost);
        stringRep = strRep;
    }
    State(POS pos, State *from, vector<double> theCost, string strRep) {
        position = pos;
        cameFrom = from;
        cost = theCost;
        stringRep = strRep;
    }
    State(State* s) {
        position = s->getPosition();
        cost = s->getVectorCost();
        cameFrom = s->getPrevious();
        stringRep = s->getStringRep();
    }
    State* getPrevious() {
        return cameFrom;
    }
    double getCost() const {
        return cost[0];
    }
    void setCost(double c) {
        cost[0] = c;
    }
    void setCost(vector<double> c){
        cost = c;
    }
    POS getPosition() const {
        return position;
    }
    bool equals(State *s) {
        return (stringRep == s->getStringRep());
    }
    string getStringRep() const {
        return stringRep;
    }
    vector<double> getVectorCost() const {
        return cost;
    }
};
template <typename POS>
bool operator<(const State<POS> & s1, const State<POS> & s2) {
    vector<double> v1 = s1.getVectorCost();
    vector<double> v2 = s2.getVectorCost();
    int size = v1.size(), i, cost1 = 0, cost2 = 0;
    for (i = 0; i<size; i++) { //sum the costs in each vector and return which sum is smaller
        cost1 += v1[i];
        cost2 += v2[i];
    }
    return cost2 < cost1;
}
template <typename POS>
bool operator==(const State<POS> & s1, const State<POS> & s2){
    return (s1.getStringRep() == s2.getStringRep());
}
/*
 * searchable interface
 */
template <typename POS>
class Searchable {
public:
    virtual State<POS>* getInitialState() = 0;
    virtual State<POS>* getGoalState() = 0;
    virtual list<State<POS>*> getAllPossibleStates(State<POS> *s) = 0;
    virtual int getheuristicVal(State<pair<int,int>> *s) = 0;
    virtual string traceSolution(State<pair<int,int>>* goal) = 0;
    virtual ~Searchable() {}
};

class MatrixDomain: public Searchable<pair<int,int>> {
    State<pair<int,int>>* start;
    State<pair<int,int>>* goal;
    int *matrix;
    int rowSize;
    int colSize;

public:
    MatrixDomain(int* mat, int row, int col, pair<int, int> theStart, pair<int, int> end);
    virtual State<pair<int,int>>* getInitialState();
    virtual State<pair<int,int>>* getGoalState();
    virtual list<State<pair<int,int>>*> getAllPossibleStates(State<pair<int,int>>* s);
    virtual int getheuristicVal(State<pair<int,int>> *s);
    virtual string traceSolution(State<pair<int,int>>* goal);
    virtual ~MatrixDomain() {
        delete matrix;
    }
};

#endif //EXE4_SEARCHABLE_H
