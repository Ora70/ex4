
#ifndef EXE4_SEARCHER_H
#define EXE4_SEARCHER_H

#include <string>
#include "Searchable.h"
#include <queue>
#include <unordered_map>
#include <bits/stdc++.h>
#include "MyPriorityQueue.h"
#include <cmath>

/*
 * Searcher interface
 */
template <typename POS>
class Searcher {
public:
    virtual string search(Searchable<POS>*) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
    virtual ~Searcher() {}
};
template <typename POS>
class AbstractSearcher: public Searcher<POS> {
    virtual void insertNodeToStructure(State<POS>* state) = 0;
    virtual State<POS>* getNextNodeFromStructure() = 0;
    virtual bool structureIsEmpty() = 0;

protected:
    int numOfNodes;
    unordered_map<string, State<POS>*> nodesSeen;
    Searchable<POS>* searchableObj;

public:
    virtual string search(Searchable<POS>* searchable){
        searchableObj = searchable;
        State<POS>* s = searchable->getInitialState();
        if (s->equals(searchable->getGoalState())) { //if initial sate is goal we're done
            searchable->getGoalState()->setCost(s->getCost());
            delete s;
            numOfNodes = 1;
            return "";
        }
        insertNodeToStructure(s);
        while(!structureIsEmpty()) {
            s = getNextNodeFromStructure();
            list<State<POS>*> successors = searchable->getAllPossibleStates(s);
            while (!successors.empty()) {
                s = successors.front();
                successors.pop_front();
                if (s->equals(searchable->getGoalState())) { //reached goal state. can stop iteration
                    numOfNodes += 1;
                    nodesSeen.insert({s->getStringRep(), s});
                    string solution = searchable->traceSolution(s);
                    return solution;
                } else {
                    insertNodeToStructure(s);
                }
            }
        }
        return "No path found"; //if reached the end of while loop there's no path from start to the goal
    }
    virtual int getNumberOfNodesEvaluated() {return numOfNodes;}
    virtual ~AbstractSearcher() {}
};

template <typename POS>
class DFS: public AbstractSearcher<POS> {
    stack <State<POS>*> DFSstack;

    virtual void insertNodeToStructure(State<POS>* state) {
        string stateStr = state->getStringRep();
        if (this->nodesSeen.find(stateStr) == this->nodesSeen.end()) { //new node
            this->nodesSeen.insert({state->getStringRep(), state}); //add to node to seen map
            DFSstack.push(state);
        }
    }
    virtual State<POS>* getNextNodeFromStructure() {
        this->numOfNodes += 1;
        State<POS> *s = DFSstack.top();
        DFSstack.pop();
        return s;
    }
    virtual bool structureIsEmpty() {return DFSstack.empty();}

public:
    virtual ~DFS() {}
};

template <typename POS>
class BFS: public AbstractSearcher<POS> {
    queue<State<POS>*> BFSq;

    virtual void insertNodeToStructure(State<POS>* state) {
        string stateStr = state->getStringRep();
        if (this->nodesSeen.find(stateStr) == this->nodesSeen.end()) { //new node
            this->nodesSeen.insert({state->getStringRep(), state}); //add to node to seen map
            BFSq.push(state);
        }
    }
    virtual State<POS>* getNextNodeFromStructure() {
        this->numOfNodes += 1;
        State<POS> *s = BFSq.front();
        BFSq.pop();
        return s;
    }
    virtual bool structureIsEmpty() {return BFSq.empty();}
public:
    virtual ~BFS() {}
};

template <typename POS>
class BestFirstSearch: public AbstractSearcher<POS> {
    custom_priority_queue<State<POS>> open;
    unordered_map<string, State<POS>*> closed;

    virtual void insertNodeToStructure(State<POS>* state) {
        string strRep = state->getStringRep();

        if (closed.find(strRep) != closed.end()) { //node in closed list. already found best path
            return;
        } else if ((this->nodesSeen.find(strRep)) != this->nodesSeen.end()) { //node in open list. need to check if path shorter
            State<POS> *oldState = this->nodesSeen.at(strRep);
            if (state->getCost() < oldState->getCost()) { //new route is better
                open.remove(State<POS>(oldState)); //remove old node
                open.push(State<POS>(state));
                this->nodesSeen[strRep] = state;
            }
        } else { //new node. need to add to queue
            open.push(State<POS>(state));
            this->nodesSeen.insert({strRep, state}); //add to node to seen map
        }
    }
    virtual State<POS>* getNextNodeFromStructure() {
        this->numOfNodes += 1;
        State<POS> s = open.top();
        open.pop();
        State<POS> *state = new State<POS>(s.getPosition(), s.getPrevious(), s.getCost(), s.getStringRep());
        closed.insert({s.getStringRep(), state});
        return state;
    }
    virtual bool structureIsEmpty() {return open.empty();}
public:
    virtual ~BestFirstSearch() {}
};

template <typename POS>
class AStarSearch: public AbstractSearcher<POS> {
    custom_priority_queue<State<POS>> open;
    unordered_map<string, State<POS>*> closed;

    virtual void insertNodeToStructure(State<POS>* state) {
        //create h and update cost of state accordingly
        vector<double> cost;
        cost.push_back(state->getCost()); //first cost in vector is true cost from start
        cost.push_back(this->searchableObj->getheuristicVal(state)); //second cost is estimated cost to goal
        state->setCost(cost);
        //check if state was seen before
        string strRep = state->getStringRep();
        if ((closed.find(strRep)) != closed.end()) { //node in closed list. Check if new cost smaller
            State<POS> old = this->closed.at(strRep);
            if (state->getCost() < old.getCost()) { //new cost smaller. need to remove from closed and add to opened
                closed.erase(strRep);
                open.push(State<POS>(state));
            }
        } else if ((this->nodesSeen.find(strRep)) != this->nodesSeen.end()) { //node in queue
            State<POS> old = this->nodesSeen.at(strRep);
            if (state->getCost() < old.getCost()) { //new cost smaller. need to update queue
                open.remove(old); //remove old node
                open.push(State<POS>(state));
                this->nodesSeen[strRep] = state;
            }
        } else {
            //new node. need to add to queue
            open.push(State<POS>(state));
            this->nodesSeen.insert({strRep, state}); //add node to seen map
        }
    }
    virtual State<POS>* getNextNodeFromStructure() {
        this->numOfNodes += 1;
        State<POS> s = open.top();
        open.pop();
        State<POS> *state = new State<POS>(s.getPosition(), s.getPrevious(), s.getVectorCost(), s.getStringRep());
        closed.insert({s.getStringRep(), state});
        return state;
    }
    virtual bool structureIsEmpty() { return open.empty();}
public:
    virtual ~AStarSearch() {}
};

#endif //EXE4_SEARCHER_H
