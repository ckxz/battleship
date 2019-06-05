//
//  Board.hpp
//  Battleship
//
//  Created by Arnau Coiduras on 25/05/2019.
//  Copyright © 2019 Arnau Coiduras. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <vector>
#include "Ship.hpp"
#include "Utils.hpp"

#define BOARD_SIZE 9
#define SHIPS_NUMBER 3

using namespace std;

class Board {
private:
    int alive;
    char matrix[BOARD_SIZE][BOARD_SIZE];
    vector<Ship*> ships;
    vector<Position*> shotPositions;
    bool areCoordinatesValid(int x, int y, int size, Orientation *orientation);
    void createShip(int x, int y, int size, Orientation orientation, char value);
    bool findShotPosition(int x, int y);
public:
    Board();
    ~Board();
    void createRandomShips();
    void setShips();
    void print();
    void printOnlyShot();
    void shoot(int x, int y);
    bool isGameFinished();
};

#endif /* Board_hpp */
