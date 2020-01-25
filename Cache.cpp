
#include "Cache.h"

/*
 * check if solution exist.
 */
bool FileCacheManager::solutionExists(string prob) {

    ifstream read_file;
    read_file.open(prob+".txt", ios::in);
    if (!read_file) {
        return false;
    }
    read_file.close();
    return true;
}
/*
 * return the solution to the problem.
 */
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

/*
 * add solution to cache.
 */
void FileCacheManager::SaveNewProblem(string prob, string sol) {

    ofstream file_obj;
    file_obj.open(prob +".txt", ios::out);
    if (!file_obj) {
        throw "failed opening file";
    }
    file_obj <<sol;
    file_obj.close();
}

