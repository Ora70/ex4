
#include "Searchable.h"

State:: State (int i, int j, State *from, double theCost) {
    position.first = i;
    position.second = j;
    cameFrom = from;
    cost = theCost;
}
State::State(pair<int, int> pos, State *from, double theCost) {
    position = pos;
    cameFrom = from;
    cost = theCost;
}
State* State:: GetPrevious() {
    return cameFrom;
}
void State:: SetPrevious(State from) {
    cameFrom = &from;
}
double State:: getCost() const {
    return cost;
}
void State:: setCost(double c) {
    cost = c;
};
pair<int, int> State::getPosition() {
    return position;
}
bool State::equals(State s) {
    pair<int, int> otherPos = s.getPosition();
    return ((position.first == otherPos.first) && (position.second == otherPos.second));
}
bool operator<(const State& s1, const State & s2) {
    return s2.getCost() < s1.getCost();
}

MatrixDomain:: MatrixDomain(double* mat, int row, int col, pair<int, int> theStart, pair<int, int> end)
: start(theStart, nullptr, 0), goal(end, nullptr, std::numeric_limits<double>::infinity()) {
    matrix = mat;
    rowSize = row;
    colSize = col;
    //set cost of starting point to the value in that square
    start.setCost(mat[theStart.first*col + theStart.second]);
}

State MatrixDomain::getInitialState() {
    return start;
}
State MatrixDomain::getGoalState() {
    return goal;
}
list<State> MatrixDomain::getAllPossibleStates(State s) {
    list<State> adjStates;
    pair<int, int> sPos = s.getPosition();
    int row = sPos.first;
    int col = sPos.second;
    double sCost = s.getCost();
    if (row > 0) { //can add above square
        adjStates.push_back(State(row - 1, col, &s, sCost+ matrix[colSize*(row-1)+col]));
    }
    if (row < rowSize - 1) { //can add below square
        adjStates.push_back( State(row + 1, col, &s, sCost+ matrix[colSize*(row+1)+col]));
    }
    if (col > 0) { //can add left
        adjStates.push_back(State(row, col-1, &s, sCost+ matrix[colSize*row+col-1]));
    }
    if (col < colSize-1) { //can add right
        adjStates.push_back(State(row, col+1, &s, sCost+ matrix[colSize*row+col+1]));
    }

    return adjStates;
}