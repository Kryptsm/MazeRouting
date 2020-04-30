//
// Created by Sam Walsh on 4/29/20.
//


#include "LeeAlgorithm.h"
#include "Vertex.h"
#include <vector>
#include <string>
#include <cstring>

//retrieves all necessary information and sets it where necessary
LeeAlgorithm::LeeAlgorithm(int numberOfColumns, int numberOfRows, string **newMaze, string **mazeToSearch,
                           int startPosX, int startPosY, int endPosX, int endPosY) {
    numColumns = numberOfColumns;
    numRows = numberOfRows;
    FinalMaze = newMaze;
    Maze = mazeToSearch;
    startX = startPosX, startY = startPosY;
    endVertex.setPositionX(endPosX);
    endVertex.setPositionY(endPosY);
}

//performs the main searching algorithm
int LeeAlgorithm::performSearch() {
    //initializes the vectors, both the listOf version that holds the current list of vertexes we are "waving", and
    //a temporary one that gathers the list of vertexes that will be in the next wave
    vector<Vertex> listOfVertexes;
    vector<Vertex> tempVector;

    //makes the start vertex and adds it, so that the first wave starts there
    Vertex startVertex(startX, startY, 0);
    listOfVertexes.push_back(startVertex);

    //sets the current additive (AKA the current distance from the start node) at 1, since the wave of the first node
    //will be one move away
    int currentAdditive = 1;

    //sets up the looping structure.
    bool status = false;
    while (!status) {
        for (auto &vertex : listOfVertexes) {
            status = addWave(&tempVector, vertex.getPositionX(), vertex.getPositionY(), currentAdditive);
            if (status)
                break;
        }

        //moves the temp vector vertexes into the main vector, and clears the temp for future use
        listOfVertexes = tempVector;
        tempVector.clear();

        //increases the level
        currentAdditive++;
    }
    Vertex currentVertex = endVertex;

    //backtracks all the way back from the end node to the start node, going in descending order of
    //vertex distance values
    for (int x = (currentAdditive - 1); x > 1; x--) {
        currentVertex = backtrackLevel(x, currentVertex);
    }

    return currentAdditive - 1;

}

//Adds a wave (aka marks the vertexes) around the desired node with the desired level, and adds all the "waved" vertexes
//to the temp list for use in the next wave
bool LeeAlgorithm::addWave(vector<Vertex> *vertexList, int indexX, int indexY, int level) {
    int currentX = indexX;
    int currentY = indexY;

    //checks if the vertex to the left is open to be marked. If it is, if its the end it returns. Else it adds it to
    //the "to be waved" list and changes it to the number.
    if (currentY != 0) {
        if ((strcmp(Maze[currentX][currentY - 1].c_str(), "O") == 0) ||
            (strcmp(Maze[currentX][currentY - 1].c_str(), "E") == 0)) {
            if (strcmp(Maze[currentX][currentY - 1].c_str(), "E") == 0)
                return true;
            Maze[currentX][currentY - 1] = to_string(level);
            Vertex temp(currentX, currentY - 1, level);
            vertexList->push_back(temp);
        }
    }
    //checks the vertex above
    if (currentX != 0) {
        if ((strcmp(Maze[currentX - 1][currentY].c_str(), "O") == 0) ||
            (strcmp(Maze[currentX - 1][currentY].c_str(), "E") == 0)) {
            if (strcmp(Maze[currentX - 1][currentY].c_str(), "E") == 0)
                return true;
            Maze[currentX - 1][currentY] = to_string(level);
            Vertex temp(currentX - 1, currentY, level);
            vertexList->push_back(temp);
        }
    }
    //checks the vertex under the current
    if (currentX != (numRows - 1)) {
        if ((strcmp(Maze[currentX + 1][currentY].c_str(), "O") == 0) ||
            (strcmp(Maze[currentX + 1][currentY].c_str(), "E") == 0)) {
            if (strcmp(Maze[currentX + 1][currentY].c_str(), "E") == 0)
                return true;
            Maze[currentX + 1][currentY] = to_string(level);
            Vertex temp(currentX + 1, currentY, level);
            vertexList->push_back(temp);
        }
    }
    //checks the vertex to the right
    if (currentY != (numColumns - 1)) {
        if ((strcmp(Maze[currentX][currentY + 1].c_str(), "O") == 0) ||
            (strcmp(Maze[currentX][currentY + 1].c_str(), "E") == 0)) {
            if (strcmp(Maze[currentX][currentY + 1].c_str(), "E") == 0)
                return true;
            Maze[currentX][currentY + 1] = to_string(level);
            Vertex temp(currentX, currentY + 1, level);
            vertexList->push_back(temp);
        }
    }
    return false;
}

//this function will pass in a vertex and a current level, and then mark the next lowest value vertex around
//it as part of the path and return it. So we will be able to start at the end and work our way back to zero.
Vertex LeeAlgorithm::backtrackLevel(int currentLevel, Vertex currentVertex) {
    int currentX = currentVertex.getPositionX();
    int currentY = currentVertex.getPositionY();
    string tempHolder = to_string(currentLevel - 1);

    //checks for the next level down after our current level
    if (currentY != 0) {
        if (Maze[currentX][currentY - 1] == tempHolder) {
            FinalMaze[currentX][currentY - 1] = "+";
            Vertex temp(currentX, currentY - 1, 0);
            return temp;
        }
    }
    //checks the vertex above
    if (currentX != 0) {
        if (Maze[currentX - 1][currentY] == tempHolder) {
            FinalMaze[currentX - 1][currentY] = "+";
            Vertex temp(currentX - 1, currentY, 0);
            return temp;
        }
    }
    //checks the vertex under the current
    if (currentX != (numRows - 1)) {
        if (Maze[currentX + 1][currentY] == tempHolder) {
            FinalMaze[currentX + 1][currentY] = "+";
            Vertex temp(currentX + 1, currentY, 0);
            return temp;
        }
    }
    //checks the vertex to the right
    if (currentY != (numColumns - 1)) {
        if (Maze[currentX][currentY + 1] == tempHolder) {
            FinalMaze[currentX][currentY + 1] = "+";
            Vertex temp(currentX, currentY + 1, 0);
            return temp;
        }
    }
    return currentVertex;
}
