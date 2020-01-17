
#ifndef EXE4_CACHE_H
#define EXE4_CACHE_H

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

class FileCacheManager: public CacheManager<string, unsigned long> {
    unordered_map <unsigned long, string> savedProblems;

public:
    FileCacheManager(){}
    virtual bool solutionExists(unsigned long prob);
    virtual string getSolution(unsigned long prob);
    virtual void SaveNewProblem(unsigned long prob, string sol);
};

#endif //EXE4_CACHE_H
