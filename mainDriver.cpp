//
// Created by Sam Walsh on 4/29/20.
//

#include "mainDriver.h"
#include <string>

mainDriver::mainDriver(int mazeVersion) {
    Maze = nullptr;
    MazeForSearch = nullptr;

    outputFile.open("output.txt");
    if (!outputFile.is_open())
        cout << "Error opening output file." << endl;

    //A single wall to get around
    if (mazeVersion == 0) {
        numRows = 5, numColumns = 5;
        createMazes();

        //sets up the wall
        for (int x = 0; x < 3; x++) {
            Maze[x][2] = '#';
            MazeForSearch[x][2] = '#';
        }

        //sets up the start and end points
        Maze[0][1] = '0', Maze[1][4] = 'E';
        MazeForSearch[0][1] = '0', MazeForSearch[1][4] = 'E';
        startX = 0, startY = 1;
        endX = 1, endY = 4;
    }
        //sets up a small, normal maze
    else if (mazeVersion == 1) {
        numRows = 5, numColumns = 5;
        createMazes();

        //sets up each of the walls in each of the columns
        for (int x = 0; x < numRows; x++) {
            Maze[x][0] = '#';
            MazeForSearch[x][0] = '#';
        }
        for (int x = 2; x < numRows; x++) {
            Maze[x][1] = '#';
            MazeForSearch[x][1] = '#';
        }

        Maze[0][2] = '#', Maze[2][2] = '#';
        MazeForSearch[0][2] = '#', MazeForSearch[2][2] = '#';
        Maze[0][3] = '#', Maze[4][3] = '#';
        MazeForSearch[0][3] = '#', MazeForSearch[4][3] = '#';

        for (int x = 0; x < numRows; x++) {
            Maze[x][4] = '#';
        }

        //start and end
        Maze[0][1] = '0', Maze[4][2] = 'E';
        MazeForSearch[0][1] = '0', MazeForSearch[4][2] = 'E';
        startX = 0, startY = 1;
        endX = 4, endY = 2;
    }
        //makes a wide block of walls with one path
    else if (mazeVersion == 2) {
        numRows = 10, numColumns = 20;
        createMazes();

        //creates one big block of walls with a path around the outside
        for (int x = 0; x < numRows - 1; x++) {
            for (int y = 1; y < numColumns - 1; y++) {
                Maze[x][y] = '#';
                MazeForSearch[x][y] = '#';
            }
        }

        //start and end
        Maze[0][0] = '0', Maze[0][19] = 'E';
        MazeForSearch[0][0] = '0', MazeForSearch[0][19] = 'E';
        startX = 0, startY = 0;
        endX = 0, endY = 19;
    }
        //huge map with a small wall between the points
    else if (mazeVersion == 3) {
        numRows = 50, numColumns = 50;
        createMazes();

        for (int x = 5; x < 45; x++) {
            Maze[x][25] = '#';
            MazeForSearch[x][25] = '#';
        }

        Maze[25][24] = "0", Maze[25][26] = "E";
        MazeForSearch[25][24] = "0", MazeForSearch[25][26] = "E";
        startX = 25, startY = 24;
        endX = 25, endY = 26;
    }
    LeeAlgo = new LeeAlgorithm(numColumns, numRows, Maze, MazeForSearch, startX, startY, endX, endY);
}

void mainDriver::go() {
    printMaze();
    int distanceToEnd = LeeAlgo->performSearch();
    printDataMaze();

    cout << "Minimum distance from start to end: " << distanceToEnd << endl;


    for (int x = 0; x < numRows; x++) {
        delete[] Maze[x];
        delete[] MazeForSearch[x];
    }
    delete[] Maze;
    delete[] MazeForSearch;

    delete LeeAlgo;
}

void mainDriver::createMazes() {
    Maze = new string *[numRows];
    MazeForSearch = new string *[numRows];

    for (int x = 0; x < numRows; x++) {
        Maze[x] = new string[numColumns];
        MazeForSearch[x] = new string[numColumns];
        for (int y = 0; y < numColumns; y++) {
            Maze[x][y] = "O";
            MazeForSearch[x][y] = "O";
        }
    }
}

void mainDriver::printMaze() {
    cout << endl << "Maze: " << endl;
    for (int x = 0; x < numColumns; x++) {
        cout << "---";
    }
    cout << "----" << endl;

    for (int x = 0; x < numRows; x++) {
        cout << "| ";
        for (int y = 0; y < numColumns; y++)
            if (strcmp(Maze[x][y].c_str(), "O") == 0)
                cout << "   ";
            else {
                if (Maze[x][y].size() == 1)
                    cout << " " << Maze[x][y] << " ";
                else if (Maze[x][y].size() == 2)
                    cout << " " << Maze[x][y];
                else
                    cout << Maze[x][y];
            }
        cout << " |" << endl;
    }

    for (int x = 0; x < numColumns; x++) {
        cout << "---";
    }
    cout << "----" << endl;
}

void mainDriver::printDataMaze() {
    cout << endl << "Maze: " << endl;
    for (int x = 0; x < numColumns; x++) {
        cout << "---";
    }
    cout << "----" << endl;

    for (int x = 0; x < numRows; x++) {
        cout << "| ";
        for (int y = 0; y < numColumns; y++)
            if (strcmp(MazeForSearch[x][y].c_str(), "O") == 0)
                cout << "   ";
            else {
                if (MazeForSearch[x][y].size() == 1)
                    cout << " " << MazeForSearch[x][y] << " ";
                else if (MazeForSearch[x][y].size() == 2)
                    cout << " " << MazeForSearch[x][y];
                else
                    cout << MazeForSearch[x][y];
            }

        cout << " |" << endl;
    }

    for (int x = 0; x < numColumns; x++) {
        cout << "---";
    }
    cout << "----" << endl;
}


