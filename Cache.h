
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
#include <sys/stat.h>
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
    virtual ~CacheManager() {}
};

class FileCacheManager: public CacheManager<string, string> {

public:
    FileCacheManager(){}
    virtual bool solutionExists(string prob);
    virtual string getSolution(string prob);
    virtual void SaveNewProblem(string prob, string sol);
    virtual ~FileCacheManager() {}
};

#endif //EXE4_CACHE_H
