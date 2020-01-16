
#include "Searchable.h"

State::State(pair<int, int> pos, State *from, double theCost) {
    position = pos;
    cameFrom = from;
    cost.push_back(theCost);
    stringPos = to_string(pos.first);
    string s2 = to_string(pos.second);
    stringPos.append(",").append(s2);
}
State::State(pair<int, int> pos, State *from, vector<double> theCost) {
    position = pos;
    cameFrom = from;
    cost = theCost;
    stringPos = to_string(pos.first);
    string s2 = to_string(pos.second);
    stringPos.append(",").append(s2);
}
State* State:: getPrevious() {
    return cameFrom;
}
double State:: getCost() const {
    return cost[0];
}
vector<double> State:: getVectorCost() const {
    return cost;
}
void State:: setCost(double c) {
    cost[0] = c;
}
void State::setCost(vector<double> c) {
    cost = c;
}
pair<int, int> State::getPosition() const {
    return position;
}
string State::getStringPos() const {
    return stringPos;
}
bool State::equals(State* s) {
    pair<int, int> otherPos = s->getPosition();
    return ((position.first == otherPos.first) && (position.second == otherPos.second));
}
bool operator<(const State& s1, const State & s2) {
    vector<double> v1 = s1.getVectorCost();
    vector<double> v2 = s2.getVectorCost();
    int size = v1.size(), i, cost1 = 0, cost2 = 0;
    for (i = 0; i<size; i++) { //sum the costs in each vector and return which sum is smaller
        cost1 += v1[i];
        cost2 += v2[i];
    }
    return cost2 < cost1;
}
bool operator==(const State & s1, const State & s2) {
    if (s1.getStringPos() == s2.getStringPos()) {
        return true;
    }
    return false;
}

MatrixDomain:: MatrixDomain(int* mat, int row, int col, pair<int, int> theStart, pair<int, int> end) {
    start = new State(theStart, nullptr, 0);
    goal = new State(end, nullptr, std::numeric_limits<double>::infinity());
    matrix = mat;
    rowSize = row;
    colSize = col;
    //set cost of starting point to the value in that square
    start->setCost(mat[theStart.first*col + theStart.second]);
}

State* MatrixDomain::getInitialState() {
    return new State(start);
}
State* MatrixDomain::getGoalState() {
    return new State(goal);
}
list<State*> MatrixDomain::getAllPossibleStates(State* s) {
    list<State*> adjStates;
    pair<int, int> sPos = s->getPosition();
    int row = sPos.first;
    int col = sPos.second;
    int sCost = s->getCost();
    int adjCost;
    if (row > 0) { //can add above square
        adjCost = matrix[colSize*(row-1)+col];
        if (adjCost >-1) {
            adjStates.push_back(new State(row - 1, col, s, sCost+ matrix[colSize*(row-1)+col]));
        }
    }
    if (row < rowSize - 1) { //can add below square
        adjCost = matrix[colSize*(row+1)+col];
        if (adjCost >-1) {
            adjStates.push_back( new State(row + 1, col, s, sCost+ matrix[colSize*(row+1)+col]));
        }
    }
    if (col > 0) { //can add left
        adjCost = matrix[colSize*row+col-1];
        if (adjCost >-1) {
            adjStates.push_back(new State(row, col-1, s, sCost+ matrix[colSize*row+col-1]));
        }
    }
    if (col < colSize-1) { //can add right
        adjCost = matrix[colSize*row+col+1];
        if (adjCost >-1){
            adjStates.push_back(new State(row, col+1, s, sCost+ matrix[colSize*row+col+1]));
        }
    }

    return adjStates;
}