//
// Created by Sam Walsh on 4/29/20.
//
#include <iostream>
#include <fstream>
#include <list>
#include "Vertex.h"

using namespace std;

#ifndef MAZEROUTING_LEEALGORITHM_H
#define MAZEROUTING_LEEALGORITHM_H

class LeeAlgorithm {
private:
    int numColumns = 0;
    int numRows = 0;

    int startX = 0;
    int startY = 0;
    Vertex endVertex;

    string **Maze;
    string **FinalMaze;

public:
    LeeAlgorithm(int numberOfColumns, int numberOfRows, string **newMaze, string **mazeToSearch, int startPosX,
                 int startPosY, int endPosX, int endPosY);

    int performSearch();

    bool addWave(vector<Vertex> *vertexList, int indexX, int indexY, int level);

    void printProgress();


};

#endif //MAZEROUTING_LEEALGORITHM_H
