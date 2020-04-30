//
// Created by Sam Walsh on 4/29/20.
//

#ifndef MAZEROUTING_VERTEX_H
#define MAZEROUTING_VERTEX_H

class Vertex {
private:
    int positionX;
    int positionY;
    int distance;

public:
    Vertex(int positionX, int positionY, int distance) : positionX(positionX), positionY(positionY),
                                                         distance(distance) {}

    Vertex() {
        positionX = -1;
        positionY = -1;
        distance = -1;
    }

    int getPositionX() const {
        return positionX;
    }

    void setPositionX(int positionX) {
        Vertex::positionX = positionX;
    }

    int getPositionY() const {
        return positionY;
    }

    void setPositionY(int positionY) {
        Vertex::positionY = positionY;
    }

    int getDistance() const {
        return distance;
    }

    void setDistance(int distance) {
        Vertex::distance = distance;
    }

    bool operator==(const Vertex &rhs) const {
        return positionX == rhs.positionX &&
               positionY == rhs.positionY;
    }

    bool operator!=(const Vertex &rhs) const {
        return !(rhs == *this);
    }
};

#endif //MAZEROUTING_VERTEX_H
