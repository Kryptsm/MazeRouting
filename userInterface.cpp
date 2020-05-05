//
// Created by Sam Walsh on 5/1/20.
//

#include "userInterface.h"
#include "mainDriver.h"
#include "iostream"

using namespace std;

void userInterface::initiate() {
    mainDriver program;
    bool gitHub = true;

    if (gitHub) {
        program.go(5, 1);
        program.go(5, 2);
        return;
    }

    int mazeOption = getMazeOption();
    int algoOption = getAlgoOption();


    //just so that the UI doesnt run on github


    if (algoOption != 3)
        program.go(mazeOption, algoOption);
    else {
        program.go(mazeOption, 1);
        program.go(mazeOption, 2);
    }
}

int userInterface::getMazeOption() {
    cout << "Welcome to the Magical Maze Solver! (Which basically works in any matrix with a defined start and end)"
         << endl << endl;
    cout << "Please choose one of the following selections: " << endl << endl;
    cout
            << "1) Small Wall Maze. Makes a small 5x5 matrix with a wall from the top middle to the exact middle, start and end on either side."
            << endl;
    cout
            << "2) Custom Wall Maze. User-defined width and height of previous maze, with walls start and end automatically made."
            << endl;
    cout
            << "3) Edge Path Maze. The entire matrix is filled with walls, except a path around the outside from start to end."
            << endl;
    cout << "4) Normal Maze. Creates a very small single-path maze that only has one path." << endl;
    cout << "5) Multi-Path Normal Maze. Creates a normal sized maze with dead-ends and multiple paths." << endl;
    cout << "6) Multi-Path Large Maze. Creates a larger maze with dead-ends and  multiple paths." << endl;
    cout
            << "7) Large Wall Maze. Creates a very large (50x50) matrix with a big wall in the middle, splitting begin and end."
            << endl;
    cout
            << "8) Large Wave Wall Maze. Creates the same maze as in 6, but with a series of walls that increase in size then decrease between begin and end."
            << endl;
    cout << endl << "Please make an option 1-8. Enter: ";
    int buffer;
    cin >> buffer;

    while (cin.fail()) {
        cout << "That was not a number. Please try again. Enter: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> buffer;
    }

    while (buffer < 0 || buffer > 8) {
        cout << "Not within the specified range. Enter: ";
        cin >> buffer;
        while (cin.fail()) {
            cout << "That was not a number. Please try again. Enter: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> buffer;
        }

    }

    buffer--;
    return buffer;
}

int userInterface::getAlgoOption() {
    cout << endl << "Now, please choose a pathfinding versiont to run." << endl;
    cout << "1) Sophisticated Implementation: Lee Algorithm. Runs very well on all graphs." << endl;
    cout << "2) Trivial Implementation: Recursive Backtracking. Runs very poorly on any graph with lots of space."
         << endl;
    cout << "3) Both" << endl;
    cout << "Enter: ";

    int buffer2;
    cin >> buffer2;

    while (cin.fail()) {
        cout << "That was not a number. Please try again. Enter: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> buffer2;
    }

    while (buffer2 != 1 && buffer2 != 2 && buffer2 != 3) {
        cout << "Invalid option. Enter: ";
        cin >> buffer2;
        while (cin.fail()) {
            cout << "That was not a number. Please try again. Enter: ";
            cin.clear();
            cin.ignore(256, '\n');
            cin >> buffer2;
        }

    }

    return buffer2;
}
