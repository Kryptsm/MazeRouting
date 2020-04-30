//
// Created by Sam Walsh on 4/29/20.
//
#include <iostream>
#include <fstream>
#include "LeeAlgorithm.h"
#include <cstring>

using namespace std;

#ifndef MAZEROUTING_MAINDRIVER_H
#define MAZEROUTING_MAINDRIVER_H

//This class sets up the maze and calls commands on the maze
class mainDriver {
private:
    ofstream outputFile;
    int numColumns = 0;
    int numRows = 0;

    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;

    string **Maze;
    string **MazeForSearch;
    LeeAlgorithm *LeeAlgo;


public:
    explicit mainDriver();

    void go(int mazeVersion);

    void printMaze();

    void printDataMaze();

    void createMazes();

    void chooseVersion(int mazeVersion);

};

#endif //MAZEROUTING_MAINDRIVER_H
