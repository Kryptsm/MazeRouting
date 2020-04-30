//
// Created by Sam Walsh on 4/29/20.
//
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include "Vertex.h"

using namespace std;

#ifndef MAZEROUTING_LEEALGORITHM_H
#define MAZEROUTING_LEEALGORITHM_H

class LeeAlgorithm {
private:
    //globally holds the amount of rows and columns in the selected maze
    int numColumns = 0;
    int numRows = 0;

    //holds the information for the start and end vertexes
    int startX = 0;
    int startY = 0;
    Vertex endVertex;

    //pointers to two indentical mazes. When passed into the algorithms, one will be used to perform the wave analysis
    //and the other will be then changed via backtracking of the wave analysis to construct the optimal path
    string **Maze;
    string **FinalMaze;

public:
    LeeAlgorithm(int numberOfColumns, int numberOfRows, string **newMaze, string **mazeToSearch, int startPosX,
                 int startPosY, int endPosX, int endPosY);

    int performSearch();

    bool addWave(vector<Vertex> *vertexList, int indexX, int indexY, int level);

    Vertex backtrackLevel(int currentLevel, Vertex currentVertex);

    void printProgress();


};

#endif //MAZEROUTING_LEEALGORITHM_H
