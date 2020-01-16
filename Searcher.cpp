
#include "Searcher.h"

string AbstractSearcher::search(Searchable<State *> *searchable) {
    searchableObj = searchable;
    State* s = searchable->getInitialState();
    if (s->equals(searchable->getGoalState())) { //if initial sate is goal we're done
        searchable->getGoalState()->setCost(s->getCost());
        delete s;
        numOfNodes = 1;
        return "";
    }
    insertNodeToStructure(s);
    while(!structureIsEmpty()) {
        s = getNextNodeFromStructure();
        list<State*> successors = searchable->getAllPossibleStates(s);
        list <State*> :: iterator it;
        for (it = successors.begin(); it != successors.end(); ++it) {
            if ((*it)->equals(searchable->getGoalState())) { //reached goal state. can stop iteration
                numOfNodes += 1;
                nodesSeen.insert({(*it)->getStringPos(), *it});
                string solution = traceSolution(*it);
                deleteNodes(nodesSeen);
                return solution;
            } else {
                insertNodeToStructure(*it);
            }
        }
    }
    return "No path found"; //if reached the end of while loop there's no path from start to the goal
}
int AbstractSearcher::getNumberOfNodesEvaluated() {
    return numOfNodes;
}
string AbstractSearcher::traceSolution(State* goal) {
    string solution;
    State *previous = goal->getPrevious();

    while (previous != nullptr) {
        pair<int, int> currPos = goal->getPosition();
        pair<int, int> prevPos = previous->getPosition();
        int cost = goal->getCost();
        if (prevPos.first > currPos.first) { //prev row below
            solution = "Up ("+ to_string(cost)+ "), "+solution;
        } else if (prevPos.first < currPos.first) { //prev row above
            solution = "Down("+ to_string(cost)+ "), "+solution;
        } else if (prevPos.second > currPos.second) { //prev column on the right
            solution = "Left("+ to_string(cost)+ "), "+solution;
        } else {
            solution = "Right("+ to_string(cost)+ "), "+solution;
        }
        goal = previous;
        previous = goal->getPrevious();
    }
    solution = solution.substr(0, solution.size()-2);
    return solution;
}
void AbstractSearcher:: deleteNodes(unordered_map<string, State*> nodesSeen) {
    unordered_map<std::string, State*>::iterator it;
    for (it = nodesSeen.begin(); it != nodesSeen.end(); it++) {
        delete (it->second);
    }
}

void DFS::insertNodeToStructure(State *state) {
    string stateStr = state->getStringPos();
    if (nodesSeen.find(stateStr) == nodesSeen.end()) { //new node
        nodesSeen.insert({state->getStringPos(), state}); //add to node to seen map
        DFSstack.push(state);
    }

}
State* DFS::getNextNodeFromStructure() {
    numOfNodes += 1;
    State *s = DFSstack.top();
    DFSstack.pop();
    return s;
}
bool DFS::structureIsEmpty() {
    return DFSstack.empty();
}

void BFS::insertNodeToStructure(State *state) {
    string stateStr = state->getStringPos();
    if (nodesSeen.find(stateStr) == nodesSeen.end()) { //new node
        nodesSeen.insert({state->getStringPos(), state}); //add to node to seen map
        BFSq.push(state);
    }
}
State* BFS::getNextNodeFromStructure() {
    numOfNodes += 1;
    State *s = BFSq.front();
    BFSq.pop();
    return s;
}
bool BFS::structureIsEmpty() {
    return BFSq.empty();
}

void BestFirstSearch::insertNodeToStructure(State *state) {
    unordered_map<std::string,State*>::iterator itr;
    string strPos = state->getStringPos();
    if (closed.find(strPos) != closed.end()) { //node in closed list. already found best path
        return;
    } else if ((itr = nodesSeen.find(strPos)) != nodesSeen.end()) { //node in open list. need to check if path shorter
        if (state->getCost() < itr->second->getCost()) { //new route is better
            open.remove(itr->second); //remove old node
            open.push(State(state));
        }
    } else { //new node. need to add to queue
        open.push(State(state));
        nodesSeen.insert({strPos, state}); //add to node to seen map
    }
}
State* BestFirstSearch::getNextNodeFromStructure() {
    numOfNodes += 1;
    State s = open.top();
    open.pop();
    State *state = new State(s.getPosition(), s.getPrevious(), s.getCost());
    closed.insert({s.getStringPos(), state});
    return state;
}
bool BestFirstSearch::structureIsEmpty() {
    return open.empty();
}

void AStarSearch::insertNodeToStructure(State *state) {
    //create h and update cost of state accordingly
    updateHOfNode(state);
    //check if state was seen before
    unordered_map<std::string,State*>::iterator itr;
    string strPos = state->getStringPos();
    if ((itr = closed.find(strPos)) != closed.end()) { //node in closed list. Check if new cost smaller
        State old = *itr->second;
        if (state->getCost() < old.getCost()) { //new cost smaller. need to remove from closed and add to opened
            closed.erase(itr);
            open.push(State(state));
        }
    } else if ((itr = nodesSeen.find(strPos)) != nodesSeen.end()) { //node in queue
        State old = *itr->second;
        if (state->getCost() < old.getCost()) { //new cost smaller. need to update queue
            open.remove(itr->second); //remove old node
            open.push(State(state));
        }
    } else {
        //new node. need to add to queue
        open.push(State(state));
        nodesSeen.insert({strPos, state}); //add node to seen map
    }
}
State* AStarSearch::getNextNodeFromStructure() {
    numOfNodes += 1;
    State s = open.top();
    open.pop();
    State *state = new State(s.getPosition(), s.getPrevious(), s.getVectorCost());
    closed.insert({s.getStringPos(), state});
    return state;
}
bool AStarSearch::structureIsEmpty() {
    return open.empty();
}
void AStarSearch::updateHOfNode(State *state) {
    pair<int, int> goalPos = searchableObj->getGoalState()->getPosition();
    pair<int, int> sPos = state->getPosition();
    double disToGoal = abs(sPos.first-goalPos.first) + abs(sPos.second+goalPos.second);
    double h = disToGoal;
    vector<double> cost;
    cost.push_back(state->getCost()); //first cost in vector is true cost from start
    cost.push_back(h); //second cost is estimated cost to goal
    state->setCost(cost);
}