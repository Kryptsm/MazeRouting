//
// Created by Sam Walsh on 4/30/20.
//

#ifndef MAZEROUTING_RECURSIVEBACKTRACKING_H
#define MAZEROUTING_RECURSIVEBACKTRACKING_H

#include <list>
#include <stack>
#include <vector>
#include <string>
#include <cstring>
#include "Vertex.h"

using namespace std;

class RecursiveBacktracking {
private:
    //globally holds the amount of rows and columns in the selected maze
    int numColumns = 0;
    int numRows = 0;

    //holds the information for the start and end vertexes
    Vertex startVertex;
    Vertex endVertex;

    //both mazes, one for the actual path and one to mark all the nodes we visited
    string **Maze;
    string **changeMaze;


public:
    RecursiveBacktracking(int numberOfColumns, int numberOfRows, string **newMaze, string **dataMaze, int startPosX,
                          int startPosY, int endPosX, int endPosY);

    int performSearch();

    void addToStack(stack<Vertex> *currentPath, vector<stack<Vertex>> *allPaths, Vertex toAdd, int &target);

    void printProgress();
};

#endif //MAZEROUTING_RECURSIVEBACKTRACKING_H
