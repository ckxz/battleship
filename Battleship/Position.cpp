//
//  Position.cpp
//  Battleship
//
//  Created by Arnau Coiduras on 01/06/2019.
//  Copyright © 2019 Arnau Coiduras. All rights reserved.
//

#include "Position.hpp"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getX() {
    return x;
}

int Position::getY() {
    return y;
}

void Position::setX(int x) {
    this->x = x;
}

void Position::setY(int y) {
    this->y = y;
}
