
#include "Searchable.h"

MatrixDomain:: MatrixDomain(int* mat, int row, int col, pair<int, int> theStart, pair<int, int> end) {
    string str = to_string(theStart.first);
    string s2 = to_string(theStart.second);
    str.append(",").append(s2);
    start = new State<pair<int,int>>(theStart, nullptr, 0, str);
    str = to_string(end.first);
    s2 = to_string(end.second);
    str.append(",").append(s2);
    goal = new State<pair<int,int>>(end, nullptr, std::numeric_limits<double>::infinity(), str);
    matrix = mat;
    rowSize = row;
    colSize = col;
    //set cost of starting point to the value in that square
    start->setCost(mat[theStart.first*col + theStart.second]);
}

State<pair<int,int>>* MatrixDomain::getInitialState() {
    return new State<pair<int,int>>(start);
}
State<pair<int,int>>* MatrixDomain::getGoalState() {
    return new State<pair<int,int>>(goal);
}
list<State<pair<int,int>>*> MatrixDomain::getAllPossibleStates(State<pair<int,int>>* s) {
    list<State<pair<int,int>>*> adjStates;
    pair<int, int> sPos = s->getPosition();
    int row = sPos.first;
    int col = sPos.second;
    int sCost = s->getCost();
    int adjCost;
    if (row > 0) { //can add above square
        adjCost = matrix[colSize*(row-1)+col];
        if (adjCost >-1) {
            string str = to_string(row-1).append(",").append(to_string(col));
            adjStates.push_back(new State<pair<int,int>>(pair<int, int>(row - 1, col), s, sCost+ matrix[colSize*(row-1)+col], str));
        }
    }
    if (row < rowSize - 1) { //can add below square
        adjCost = matrix[colSize*(row+1)+col];
        if (adjCost >-1) {
            string str = to_string(row+1).append(",").append(to_string(col));
            adjStates.push_back( new State<pair<int,int>>(pair<int, int>(row + 1, col), s, sCost+ matrix[colSize*(row+1)+col], str));
        }
    }
    if (col > 0) { //can add left
        adjCost = matrix[colSize*row+col-1];
        if (adjCost >-1) {
            string str = to_string(row).append(",").append(to_string(col-1));
            adjStates.push_back(new State<pair<int,int>>(pair<int, int>(row, col-1), s, sCost+ matrix[colSize*row+col-1], str));
        }
    }
    if (col < colSize-1) { //can add right
        adjCost = matrix[colSize*row+col+1];
        if (adjCost >-1){
            string str = to_string(row).append(",").append(to_string(col+1));
            adjStates.push_back(new State<pair<int,int>>(pair<int, int>(row, col+1), s, sCost+ matrix[colSize*row+col+1], str));
        }
    }
    return adjStates;
}
int MatrixDomain::getheuristicVal(State<pair<int,int>> *s) {
    pair<int, int> goalPos = goal->getPosition();
    pair<int, int> sPos = s->getPosition();
    return abs(sPos.first-goalPos.first) + abs(sPos.second+goalPos.second);
}
string MatrixDomain::traceSolution(State<pair<int,int>> *state) {
    string solution;
    State<pair<int,int>> *previous = state->getPrevious();

    while (previous != nullptr) {
        pair<int, int> currPos = state->getPosition();
        pair<int, int> prevPos = previous->getPosition();
        int cost = state->getCost();
        if (prevPos.first > currPos.first) { //prev row below
            solution = "Up ("+ to_string(cost)+ "), "+solution;
        } else if (prevPos.first < currPos.first) { //prev row above
            solution = "Down("+ to_string(cost)+ "), "+solution;
        } else if (prevPos.second > currPos.second) { //prev column on the right
            solution = "Left("+ to_string(cost)+ "), "+solution;
        } else {
            solution = "Right("+ to_string(cost)+ "), "+solution;
        }
        state = previous;
        previous = state->getPrevious();
    }
    solution = solution.substr(0, solution.size()-2);
    return solution;
}
