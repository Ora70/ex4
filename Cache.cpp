
#include "Cache.h"

bool FileCacheManager::solutionExists(string prob) {
    if (find(savedProblems.begin(), savedProblems.end(), prob) == savedProblems.end()) {
        return false;
    } else {
        return true;
    }
}
string FileCacheManager::getSolution(string prob) {
    ifstream read_file;
    read_file.open(prob+".txt", ios::in);
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
void FileCacheManager::SaveNewProblem(string prob, string sol) {
    savedProblems.insert(prob);
    ofstream file_obj;

    file_obj.open(prob+".txt", ios::out);
    if (!file_obj) {
        throw "failed opening file";
    }
    file_obj <<sol;
    file_obj.close();
}