
#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H
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
template <typename state>
class Searcher {
public:
    virtual string search(Searchable<state>*) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
};

class AbstractSearcher: public Searcher<State*> {
    string traceSolution(State* goal);
    void deleteNodes(unordered_map<string, State*> nodesSeen);
    virtual void insertNodeToStructure(State* state) = 0;
    virtual State* getNextNodeFromStructure() = 0;
    virtual bool structureIsEmpty() = 0;

protected:
    int numOfNodes;
    unordered_map<string, State*> nodesSeen;
    Searchable<State*>* searchableObj;

public:
    virtual string search(Searchable<State*>*);
    virtual int getNumberOfNodesEvaluated();
};

class DFS: public AbstractSearcher {
    stack <State*> DFSstack;

    virtual void insertNodeToStructure(State* state);
    virtual State* getNextNodeFromStructure();
    virtual bool structureIsEmpty();
};

class BFS: public AbstractSearcher {
    queue<State*> BFSq;

    virtual void insertNodeToStructure(State* state);
    virtual State* getNextNodeFromStructure();
    virtual bool structureIsEmpty();
};

class BestFirstSearch: public AbstractSearcher {
    custom_priority_queue<State> open;
    unordered_map<string, State*> closed;

    virtual void insertNodeToStructure(State* state);
    virtual State* getNextNodeFromStructure();
    virtual bool structureIsEmpty();
};

class AStarSearch: public AbstractSearcher {
    custom_priority_queue<State> open;
    unordered_map<string, State*> closed;

    virtual void insertNodeToStructure(State* state);
    virtual State* getNextNodeFromStructure();
    virtual bool structureIsEmpty();
    void updateHOfNode(State * state);
};

#endif //EX4_SEARCHER_H
