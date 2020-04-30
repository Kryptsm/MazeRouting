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
        printProgress();
    }

    cout << "Current Additive: " << currentAdditive << endl;
    cout << "The end has been found." << endl;
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

//prints the maze as is current, which shows all the wave information
void LeeAlgorithm::printProgress() {
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
