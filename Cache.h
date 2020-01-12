
#ifndef EX4_CACHE_H
#define EX4_CACHE_H

#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <utility>
#include <bits/stdc++.h>
using namespace std;

/*
 * CacheManager interface
 */
template <typename Solution, typename Problem>
class CacheManager {
public:
    virtual bool solutionExists(Problem prob) = 0;
    virtual Solution getSolution(Problem prob) = 0;
    virtual void SaveNewProblem(Problem prob, Solution sol) = 0;
};

class FileCacheManager: public CacheManager<string, string> {
    unordered_set <string> savedProblems;

public:
    FileCacheManager(){}
    virtual bool solutionExists(string prob);
    virtual string getSolution(string prob);
    virtual void SaveNewProblem(string prob, string sol);
};

#endif //EX4_CACHE_H
