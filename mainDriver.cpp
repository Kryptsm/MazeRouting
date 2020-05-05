//
// Created by Sam Walsh on 4/29/20.
//

#include "mainDriver.h"
#include <string>
#include <cstring>
#include <chrono>

mainDriver::mainDriver() {
    //initialzies all the dynamic objects to nullptr.
    Maze = nullptr;
    MazeForSearch = nullptr;
    LeeAlgo = nullptr;
    Recur = nullptr;

    //sets up the output file for data collection
    outputFile.open("output.txt");
    if (!outputFile.is_open())
        outputFile << "Error opening output file." << endl;
}

void mainDriver::go(int mazeVersion, int chooseOption) {

    chooseVersion(mazeVersion);

    //Does the main running of each algorithm depending on which was specified. Gathers time data, prints info to the
    //output file, and prints the length of the best path it found.
    if (chooseOption == 1) {
        LeeAlgo = new LeeAlgorithm(numColumns, numRows, Maze, MazeForSearch, startX, startY, endX, endY);

        outputFile << "-------------" << endl;
        outputFile << "LEE ALGORITHM" << endl;
        outputFile << "-------------" << endl << endl;
        outputFile << "BEFORE: ";
        printMaze();

        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> elapsed_seconds{};

        start = std::chrono::system_clock::now();
        int distanceToEnd = 0;

        distanceToEnd = LeeAlgo->performSearch();

        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;

        outputFile << "AFTER (PATH):";
        printMaze();
        outputFile << "AFTER (WAVE DATA):";
        printDataMaze();
        outputFile << "Time: " << elapsed_seconds.count() << endl << endl;
        outputFile << "Minimum distance from start to end: " << distanceToEnd << endl;

        cout << "Time (LEE): " << elapsed_seconds.count() << endl;
        cout << "Minimum distance from start to end (LEE): " << distanceToEnd << endl << endl;
    } else if (chooseOption == 2) {
        Recur = new RecursiveBacktracking(numColumns, numRows, Maze, MazeForSearch, startX, startY, endX, endY);

        outputFile << "----------------------" << endl;
        outputFile << "RECURSIVE BACKTRACKING" << endl;
        outputFile << "----------------------" << endl << endl;
        outputFile << "BEFORE:";
        printMaze();

        std::chrono::time_point<std::chrono::system_clock> start, end;
        std::chrono::duration<double> elapsed_seconds{};
        start = std::chrono::system_clock::now();
        int distanceToEnd = 0;

        distanceToEnd = Recur->performSearch();

        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;

        outputFile << "AFTER (PATH):";
        printMaze();
        outputFile << "AFTER (ALL VISITED LOCATIONS MARKED):";
        printDataMaze();
        outputFile << "Time: " << elapsed_seconds.count() << endl << endl;
        outputFile << "Minimum distance from start to end: " << distanceToEnd << endl;

        cout << "Time (RECURSIVE): " << elapsed_seconds.count() << endl;
        cout << "Minimum distance from start to end (RECURSIVE): " << distanceToEnd << endl << endl;
    }


    //Deletes the dynamically allocated objects from the program
    for (int x = 0; x < numRows; x++) {
        delete[] Maze[x];
        delete[] MazeForSearch[x];
    }
    delete[] Maze;
    delete[] MazeForSearch;

    if (chooseOption == 1)
        delete LeeAlgo;
    else
        delete Recur;
}

//Creates the mazes based on the number of columns and number of rows that was specified when they chose an option
void mainDriver::createMazes() {
    //creates a 2d array of strings that will represent the maze according to the numRows and numColumns
    Maze = new string *[numRows];
    MazeForSearch = new string *[numRows];

    //initializes the whole maze with empty space, represented by "O"
    for (int x = 0; x < numRows; x++) {
        Maze[x] = new string[numColumns];
        MazeForSearch[x] = new string[numColumns];
        for (int y = 0; y < numColumns; y++) {
            Maze[x][y] = "O";
            MazeForSearch[x][y] = "O";
        }
    }
}
//prints the maze with walls and a top and bottom, and replaces the "O" character with what it represents, a space
//prints out 0 as the start and # as interior maze walls
void mainDriver::printMaze() {
    outputFile << endl << "Maze: " << endl;
    for (int x = 0; x < numColumns; x++) {
        outputFile << "---";
    }
    outputFile << "----" << endl;

    for (int x = 0; x < numRows; x++) {
        outputFile << "| ";
        for (int y = 0; y < numColumns; y++)
            if (strcmp(Maze[x][y].c_str(), "O") == 0)
                outputFile << "   ";
            else {
                if (Maze[x][y].size() == 1)
                    outputFile << " " << Maze[x][y] << " ";
                else if (Maze[x][y].size() == 2)
                    outputFile << " " << Maze[x][y];
                else
                    outputFile << Maze[x][y];
            }
        outputFile << " |" << endl;
    }

    for (int x = 0; x < numColumns; x++) {
        outputFile << "---";
    }
    outputFile << "----" << endl;
}
//prints the same way as the regular maze printing
void mainDriver::printDataMaze() {
    outputFile << endl << "Maze: " << endl;
    for (int x = 0; x < numColumns; x++) {
        outputFile << "---";
    }
    outputFile << "----" << endl;

    for (int x = 0; x < numRows; x++) {
        outputFile << "| ";
        for (int y = 0; y < numColumns; y++)
            if (strcmp(MazeForSearch[x][y].c_str(), "O") == 0)
                outputFile << "   ";
            else {
                if (MazeForSearch[x][y].size() == 1)
                    outputFile << " " << MazeForSearch[x][y] << " ";
                else if (MazeForSearch[x][y].size() == 2)
                    outputFile << " " << MazeForSearch[x][y];
                else
                    outputFile << MazeForSearch[x][y];
            }

        outputFile << " |" << endl;
    }

    for (int x = 0; x < numColumns; x++) {
        outputFile << "---";
    }
    outputFile << "----" << endl;
}

//chooses a version of the maze to run, and sets the correct number of columns and rows, creates the mazes physically,
//and sets up the start and and obstacles of the maze itself.
void mainDriver::chooseVersion(int mazeVersion) {

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
    else if (mazeVersion == 3) {
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
            MazeForSearch[x][4] = "#";
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
    else if (mazeVersion == 6) {
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
        //makes a small "normal"  maze with multiple paths
    else if (mazeVersion == 4) {
        numRows = 11, numColumns = 11;
        createMazes();

        for (int x = 0; x < numColumns; x++)
            Maze[0][x] = "#", MazeForSearch[0][x] = "#";
        for (int x = 0; x < numColumns; x++)
            Maze[x][0] = "#", MazeForSearch[x][0] = "#";
        for (int x = 0; x < numColumns; x++)
            Maze[10][x] = "#", MazeForSearch[10][x] = "#";
        for (int x = 0; x < numColumns; x++)
            Maze[x][10] = "#", MazeForSearch[x][10] = "#";

        Maze[2][1] = "#", MazeForSearch[2][1] = "#";

        Maze[2][2] = "#", MazeForSearch[2][2] = "#";
        Maze[4][2] = "#", MazeForSearch[4][2] = "#";
        Maze[5][2] = "#", MazeForSearch[5][2] = "#";
        Maze[6][2] = "#", MazeForSearch[6][2] = "#";
        Maze[7][2] = "#", MazeForSearch[7][2] = "#";
        Maze[8][2] = "#", MazeForSearch[8][2] = "#";

        Maze[4][3] = "#", MazeForSearch[4][3] = "#";
        Maze[8][3] = "#", MazeForSearch[8][3] = "#";

        Maze[2][4] = "#", MazeForSearch[2][4] = "#";
        Maze[3][4] = "#", MazeForSearch[3][4] = "#";
        Maze[4][4] = "#", MazeForSearch[4][4] = "#";
        Maze[6][4] = "#", MazeForSearch[6][4] = "#";
        Maze[8][4] = "#", MazeForSearch[8][4] = "#";

        Maze[4][5] = "#", MazeForSearch[4][5] = "#";
        Maze[6][5] = "#", MazeForSearch[6][5] = "#";

        for (int x = 2; x < numColumns; x++)
            Maze[x][6] = "#", MazeForSearch[x][6] = "#";
        Maze[7][6] = "O", MazeForSearch[7][6] = "O";

        Maze[2][7] = "#", MazeForSearch[2][7] = "#";

        Maze[2][8] = "#", MazeForSearch[2][8] = "#";
        Maze[4][8] = "#", MazeForSearch[4][8] = "#";
        Maze[5][8] = "#", MazeForSearch[5][8] = "#";
        Maze[6][8] = "#", MazeForSearch[6][8] = "#";
        Maze[7][8] = "#", MazeForSearch[7][8] = "#";
        Maze[8][8] = "#", MazeForSearch[8][8] = "#";
        Maze[9][8] = "#", MazeForSearch[9][8] = "#";


        Maze[1][0] = "0", Maze[9][10] = "E";
        MazeForSearch[1][0] = "0", MazeForSearch[9][10] = "E";
        startX = 1, startY = 0;
        endX = 9, endY = 10;
    }
        //makes a series of walls in a big space between beginning and end
    else if (mazeVersion == 7) {
        numRows = 45, numColumns = 50;
        createMazes();

        for (int x = 22; x < 28; x++)
            Maze[x][15] = "#", MazeForSearch[x][15] = "#";

        for (int x = 20; x < 30; x++)
            Maze[x][19] = "#", MazeForSearch[x][19] = "#";

        for (int x = 15; x < 35; x++)
            Maze[x][23] = "#", MazeForSearch[x][23] = "#";

        for (int x = 13; x < 37; x++)
            Maze[x][27] = "#", MazeForSearch[x][27] = "#";

        for (int x = 15; x < 35; x++)
            Maze[x][31] = "#", MazeForSearch[x][31] = "#";

        for (int x = 20; x < 30; x++)
            Maze[x][35] = "#", MazeForSearch[x][35] = "#";

        for (int x = 22; x < 28; x++)
            Maze[x][39] = "#", MazeForSearch[x][39] = "#";


        Maze[25][10] = "0", Maze[25][40] = "E";
        MazeForSearch[25][10] = "0", MazeForSearch[25][40] = "E";
        startX = 25, startY = 10;
        endX = 25, endY = 40;
    }
        //custom maze
    else if (mazeVersion == 1) {
        cout << "What would you like the width and height to be? Enter: ";
        int buffer;
        cin >> buffer;

        while (cin.fail()) {
            cout << "That was not a number. Please try again. Enter: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> buffer;
        }

        while (buffer <= 2) {
            cout << "Need a bigger size. Enter: ";
            cin >> buffer;
            while (cin.fail()) {
                cout << "That was not a number. Please try again. Enter: ";
                cin.clear();
                cin.ignore(256, '\n');
                cin >> buffer;
            }

        }

        numRows = buffer, numColumns = buffer;
        createMazes();

        //sets up the wall
        for (int x = 0; x < buffer / 2; x++) {
            Maze[x][buffer / 2] = '#';
            MazeForSearch[x][buffer / 2] = '#';
        }

        //sets up the start and end points
        Maze[0][0] = '0', Maze[0][buffer - 1] = 'E';
        MazeForSearch[0][0] = '0', MazeForSearch[0][buffer - 1] = 'E';
        startX = 0, startY = 0;
        endX = 0, endY = buffer - 1;
    }
        //slightly larger "normal" maze
    else if (mazeVersion == 5) {
        numRows = 21, numColumns = 21;
        createMazes();

        for (int x = 0; x < numColumns; x++) {
            Maze[x][0] = "#", MazeForSearch[x][0] = "#";
            Maze[0][x] = "#", MazeForSearch[0][x] = "#";
            Maze[x][20] = "#", MazeForSearch[x][20] = "#";
            Maze[20][x] = "#", MazeForSearch[20][x] = "#";
        }

        Maze[1][8] = "#", MazeForSearch[1][8] = "#";
        Maze[1][14] = "#", MazeForSearch[1][14] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 3 && x != 11 && x != 15 && x != 17 && x != 19)
                Maze[2][x] = "#", MazeForSearch[2][x] = "#";
        }

        Maze[3][2] = "#", MazeForSearch[3][2] = "#";
        Maze[3][4] = "#", MazeForSearch[3][4] = "#";
        Maze[3][6] = "#", MazeForSearch[3][6] = "#";
        Maze[3][12] = "#", MazeForSearch[3][12] = "#";
        Maze[3][16] = "#", MazeForSearch[3][16] = "#";
        Maze[3][18] = "#", MazeForSearch[3][18] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 1 && x != 3 && x != 5 && x != 7 && x != 11 && x != 13 && x != 19) {
                Maze[4][x] = "#", MazeForSearch[4][x] = "#";
            }
        }

        Maze[5][6] = "#", MazeForSearch[5][6] = "#";
        Maze[5][10] = "#", MazeForSearch[5][10] = "#";
        Maze[5][14] = "#", MazeForSearch[5][14] = "#";
        Maze[5][16] = "#", MazeForSearch[5][16] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 1 && x != 13 && x != 15 && x != 17) {
                Maze[6][x] = "#", MazeForSearch[6][x] = "#";
            }
        }

        Maze[7][4] = "#", MazeForSearch[7][4] = "#";
        Maze[7][8] = "#", MazeForSearch[7][8] = "#";
        Maze[7][12] = "#", MazeForSearch[7][12] = "#";
        Maze[7][14] = "#", MazeForSearch[7][14] = "#";
        Maze[7][16] = "#", MazeForSearch[7][16] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 1 && x != 7 && x != 11 && x != 13 && x != 15 && x != 17) {
                Maze[8][x] = "#", MazeForSearch[8][x] = "#";
            }
        }

        Maze[9][6] = "#", MazeForSearch[9][6] = "#";
        Maze[9][16] = "#", MazeForSearch[9][16] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 5 && x != 11 && x != 19) {
                Maze[10][x] = "#", MazeForSearch[10][x] = "#";
            }
        }

        Maze[11][2] = "#", MazeForSearch[11][2] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 1 && x != 5 && x != 7 && x != 11 && x != 13 && x != 19) {
                Maze[12][x] = "#", MazeForSearch[12][x] = "#";
            }
        }

        Maze[13][6] = "#", MazeForSearch[13][6] = "#";
        Maze[13][8] = "#", MazeForSearch[13][8] = "#";
        Maze[13][10] = "#", MazeForSearch[13][10] = "#";
        Maze[13][12] = "#", MazeForSearch[13][12] = "#";
        Maze[13][14] = "#", MazeForSearch[13][14] = "#";
        Maze[13][16] = "#", MazeForSearch[13][16] = "#";
        Maze[13][18] = "#", MazeForSearch[13][18] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 5 && x != 9 && x != 13 && x != 15 && x != 17 && x != 19) {
                Maze[14][x] = "#", MazeForSearch[14][x] = "#";
            }
        }

        Maze[15][8] = "#", MazeForSearch[15][8] = "#";
        Maze[15][12] = "#", MazeForSearch[15][12] = "#";
        Maze[15][16] = "#", MazeForSearch[15][16] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 3 && x != 5 && x != 7 && x != 9 && x != 11 && x != 13 && x != 15) {
                Maze[16][x] = "#", MazeForSearch[16][x] = "#";
            }
        }

        Maze[17][4] = "#", MazeForSearch[17][4] = "#";
        Maze[17][6] = "#", MazeForSearch[17][6] = "#";
        Maze[17][8] = "#", MazeForSearch[17][8] = "#";
        Maze[17][10] = "#", MazeForSearch[17][10] = "#";
        Maze[17][14] = "#", MazeForSearch[17][14] = "#";
        Maze[17][18] = "#", MazeForSearch[17][18] = "#";

        for (int x = 0; x < numColumns; x++) {
            if (x != 7 && x != 9 && x != 17 && x != 19) {
                Maze[18][x] = "#", MazeForSearch[18][x] = "#";
            }
        }

        Maze[19][8] = "#", MazeForSearch[19][8] = "#";
        Maze[19][12] = "#", MazeForSearch[19][12] = "#";

        Maze[1][0] = "0", Maze[19][20] = "E";
        MazeForSearch[1][0] = "0", MazeForSearch[19][20] = "E";
        startX = 1, startY = 0;
        endX = 19, endY = 20;
    }

}


