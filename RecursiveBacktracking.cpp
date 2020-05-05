//
// Created by Sam Walsh on 4/30/20.
//

#include "RecursiveBacktracking.h"
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <string>
#include <cstring>
#include "Vertex.h"

using namespace std;

RecursiveBacktracking::RecursiveBacktracking(int numberOfColumns, int numberOfRows, string **newMaze, string **dataMaze,
                                             int startPosX,
                                             int startPosY, int endPosX, int endPosY) {
    //initializes all the information
    //rows and columns for size information and printing
    numColumns = numberOfColumns;
    numRows = numberOfRows;
    //loads both mazes, one for visited information and one for the actual path
    Maze = newMaze;
    changeMaze = dataMaze;
    //adds in the start and end points into vertex objects
    startVertex.setPositionX(startPosX);
    startVertex.setPositionY(startPosY);
    endVertex.setPositionY(endPosY);
    endVertex.setPositionX(endPosX);
}

//performs the main search operation, and calls other commands. Returns the length of the path.
int RecursiveBacktracking::performSearch() {
    //creates a stack that will track our current path, and a vector that will hold all the paths that we found
    //that leads to the end
    stack<Vertex> currentPath;
    vector<stack<Vertex>> allPaths;
    //starts the target length of the path at the largest possible integer, which will mean that the first path found
    //will become the target, and any longer paths will be ignored, even if they lead to the end
    int target = 2147483647;

    //adds the start vertex to the stack, which will then add all its adjacent tiles to the stack, and recursively
    //continue until it finds all possible paths
    addToStack(&currentPath, &allPaths, startVertex, target);

    //goes through the all paths list and finds the index of the shortest path
    int shortestPath = 2147483647;
    int winningIndex = -1;
    for (int x = 0; x < allPaths.size(); x++) {
        if (allPaths[x].size() < shortestPath) {
            winningIndex = x;
            shortestPath = allPaths[x].size();
        }
    }

    //goes through the entire winning path and marks the correct path on the maze
    while (!allPaths[winningIndex].empty()) {
        if (Maze[allPaths[winningIndex].top().getPositionX()][allPaths[winningIndex].top().getPositionY()] == "O")
            Maze[allPaths[winningIndex].top().getPositionX()][allPaths[winningIndex].top().getPositionY()] = "+";
        allPaths[winningIndex].pop();
    }

    //returns the length of said path
    return shortestPath - 1;
}

//recursively adds a vertex to the path, then adds all its neighbors
void RecursiveBacktracking::addToStack(stack<Vertex> *currentPath, vector<stack<Vertex>> *allPaths, Vertex toAdd,
                                       int &target) {
    //pushes the given vertex onto the stack
    currentPath->push(toAdd);
    //changes that index of the maze into a + on the maze of all nodes visited
    changeMaze[toAdd.getPositionX()][toAdd.getPositionY()] = "+";

    //if the top is the end, and if it is shorter than the current path found, adds it to the list of all.
    //pops it off the stack and continues the recursion
    if (currentPath->top() == endVertex) {
        if (currentPath->size() < target) {
            target = currentPath->size();
            allPaths->push_back(*currentPath);
        }
        currentPath->pop();
        return;
    }

    //if the current path is longer than the
    if (currentPath->size() > target) {
        currentPath->pop();
        return;
    }

    //now that we know it is part of the path and we will continue, marks it as an X on the map so we don't go over it again
    Maze[toAdd.getPositionX()][toAdd.getPositionY()] = "X";

    //checks for the next level down after our current level, only adds it if its blank or the end
    if (toAdd.getPositionY() != 0) {
        if (Maze[toAdd.getPositionX()][toAdd.getPositionY() - 1] == "O" ||
            Maze[toAdd.getPositionX()][toAdd.getPositionY() - 1] == "E") {
            Vertex temp(toAdd.getPositionX(), toAdd.getPositionY() - 1, 0);
            addToStack(currentPath, allPaths, temp, target);
        }
    }
    //checks the vertex above
    if (toAdd.getPositionX() != 0) {
        if (Maze[toAdd.getPositionX() - 1][toAdd.getPositionY()] == "O" ||
            Maze[toAdd.getPositionX() - 1][toAdd.getPositionY()] == "E") {
            Vertex temp(toAdd.getPositionX() - 1, toAdd.getPositionY(), 0);
            addToStack(currentPath, allPaths, temp, target);
        }
    }
    //checks the vertex under the current
    if (toAdd.getPositionX() != (numRows - 1)) {
        if (Maze[toAdd.getPositionX() + 1][toAdd.getPositionY()] == "O" ||
            Maze[toAdd.getPositionX() + 1][toAdd.getPositionY()] == "E") {
            Vertex temp(toAdd.getPositionX() + 1, toAdd.getPositionY(), 0);
            addToStack(currentPath, allPaths, temp, target);
        }
    }
    //checks the vertex to the right
    if (toAdd.getPositionY() != (numColumns - 1)) {
        if (Maze[toAdd.getPositionX()][toAdd.getPositionY() + 1] == "O" ||
            Maze[toAdd.getPositionX()][toAdd.getPositionY() + 1] == "E") {
            Vertex temp(toAdd.getPositionX(), toAdd.getPositionY() + 1, 0);
            addToStack(currentPath, allPaths, temp, target);
        }
    }

    //pops the top that we just added off the stack, recursion continues.
    currentPath->pop();
    if (toAdd != startVertex)
        Maze[toAdd.getPositionX()][toAdd.getPositionY()] = "O";
    else
        Maze[toAdd.getPositionX()][toAdd.getPositionY()] = "S";


}

//prints the progress of the maze so that we can check the algorithm
void RecursiveBacktracking::printProgress() {
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

