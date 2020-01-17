
#include "Cache.h"

bool FileCacheManager::solutionExists(unsigned long prob) {
    if (savedProblems.find(prob) != savedProblems.end()) {
        return true;
    } else {
        return false;
    }
}
string FileCacheManager::getSolution(unsigned long prob) {
    ifstream read_file;
    read_file.open(to_string(prob)+".txt", ios::in);
    if (!read_file) {
        throw "failed opening file";
    }
    string solution, line;
    while ( getline (read_file,line) )
    {
        solution.append(line);
    }
    read_file.close();
    return solution;
}
void FileCacheManager::SaveNewProblem(unsigned long prob, string sol) {
    savedProblems[prob] = sol;
    ofstream file_obj;

    file_obj.open(to_string(prob)+".txt", ios::out);
    if (!file_obj) {
        throw "failed opening file";
    }
    file_obj <<sol;
    file_obj.close();
}

