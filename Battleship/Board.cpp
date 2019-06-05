//
//  Board.cpp
//  Battleship
//
//  Created by Arnau Coiduras on 25/05/2019.
//  Copyright © 2019 Arnau Coiduras. All rights reserved.
//

#include "Board.hpp"

#define EMPTY '-'
#define SHOT 'X'

Board::Board() {
    // We have all ships alive
    this->alive = SHIPS_NUMBER;
    
    // Reserve number of ships
    this->ships.reserve(SHIPS_NUMBER);
    
    // Reserve number of shot positions
    this->shotPositions.reserve(BOARD_SIZE * BOARD_SIZE);
    
    // Initialize matrix
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            this->matrix[i][j] = EMPTY;
        }
    }
}

Board::~Board() {
    this->ships.clear();
    this->shotPositions.clear();
}

bool Board::areCoordinatesValid(int x, int y, int size, Orientation *orientation) {
    bool valid = true;
    
    // Check boundaries
    if(*orientation == Orientation::HORIZONTAL) {
        if((y + size) > BOARD_SIZE) {
            if((x + size) < BOARD_SIZE) {
                *orientation = Orientation::VERTICAL;
            } else {
                valid = false;
            }
        }
    } else if(*orientation == Orientation::VERTICAL) {
        if((x + size) > BOARD_SIZE) {
            if((y + size) < BOARD_SIZE) {
                *orientation = Orientation::HORIZONTAL;
            } else {
                valid = false;
            }
        }
    }
    
    // Check if ship is override with other
    if(valid) {
        if(*orientation == Orientation::HORIZONTAL) {
            // Move in x axis
            for(int pos = y; pos < y + size; pos++) {
                if(matrix[x][pos] != EMPTY) {
                    valid = false;
                    break;
                }
            }
        } else if(*orientation == Orientation::VERTICAL) {
            // Move in y axis
            for(int pos = x; pos < x + size; pos++) {
                if(matrix[pos][y] != EMPTY) {
                    valid = false;
                    break;
                }
            }
        }
    }
    
    return valid;
}

void Board::createShip(int x, int y, int size, Orientation orientation, char value) {
    // Create ship using constructor
    Ship *ship = new Ship(size, x, y, orientation);
    
    // Put in ships
    this->ships.push_back(ship);
    
    // Assign ship to matrix
    if(orientation == Orientation::HORIZONTAL) {
        // Move in x axis
        for(int pos = y; pos < y + size; pos++) {
            this->matrix[x][pos] = value;
        }
    } else if(orientation == Orientation::VERTICAL) {
        // Move in y axis
        for(int pos = x; pos < x + size; pos++) {
            this->matrix[pos][y] = value;
        }
    }
}

void Board::createRandomShips() {
    // Ship size
    int size = 2;
    char value = '2';
    
    for(int i = 0; i < SHIPS_NUMBER; i++) {
        // random orientation
        Orientation orientation;
        int orient = rand() % 1;
        if(orient == 0) {
            orientation = Orientation::HORIZONTAL;
        } else {
            orientation = Orientation::VERTICAL;
        }
        
        int x, y;
        bool validCoordinates;
        do {
            // Initialize
            validCoordinates = true;
            
            // random x
            x = rand() % BOARD_SIZE;
            // random y
            y = rand() % BOARD_SIZE;
            
            validCoordinates = areCoordinatesValid(x, y, size, &orientation);
        } while(!validCoordinates);
        
        // Create ship
        createShip(x, y, size, orientation, value);
        
        // Increase size
        size++;
        value++;
    }
}

void Board::setShips() { //da por sentado que sólo habrá 3 barcos. Repensar.
    int orient;
    int size = 2;
    char value = '2';
    Orientation orientation;
    Position *position;
    bool validCoordinates;
    string initialMessage = "Please, set your ship giving an x (row) and y (column)";
    string errorMsg = "You entered an incorrect orientation. Please, try again: ";
    
    for(int i = 0; i < SHIPS_NUMBER; i++) {
        do {
            // Initialize
            validCoordinates = true;
            
            // Get X and Y
            position = Utils::readPosition(initialMessage);
            
            // Get orientation
            cout << "Insert orientation (0 for HORIZONTAL, 1 for VERTICAL): ";
            orient = Utils::readNumber(0, 1, errorMsg);
            
            if(orient == 0) {
                orientation = Orientation::HORIZONTAL;
            } else {
                orientation = Orientation::VERTICAL;
            }
            
            validCoordinates = areCoordinatesValid(position->getX(), position->getY(),
                                                   size, &orientation);
            
            cout << endl;
        } while(!validCoordinates);
        
        // Create ship
        createShip(position->getX(), position->getY(), size, orientation, value);
        
        // Increase size
        size++;
        value++;
    }
}

void Board::print() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            cout << " " << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool Board::findShotPosition(int x, int y) {
    bool found = false;
    for(Position *pos : shotPositions) {
        if(pos->getX() == x && pos->getY() == y) {
            found = true;
            break;
        }
    }
    return found;
}

void Board::printOnlyShot() {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(findShotPosition(i, j)) {
                cout << " " << matrix[i][j] << " ";
            } else {
                cout << " ? ";
            }
        }
        cout << endl;
    }
}

void Board::shoot(int x, int y) {
    // Save shot position
    this->shotPositions.push_back(new Position(x, y));
    
    // Check matrix
    if(matrix[x][y] == EMPTY) {
        cout << "You missed. Nothing's there." << endl << endl;
    }
    else if(matrix[x][y] == SHOT) {
        cout << "You've already shot and hit here." << endl << endl;
    }
    else if(matrix[x][y] > '0') {
        cout << "HIT!" << endl;
        
        // Get value to identify the ship
        int size = matrix[x][y] - '0';
        
        // Update matrix
        matrix[x][y] = SHOT;
        
        // Find ship
        for(Ship *ship : ships) {
            if(ship->getSize() == size) {
                int cont = 0;
                int initialX = ship->getX();
                int initialY = ship->getY();
                Orientation orientation = ship->getOrientation();
                if(orientation == Orientation::HORIZONTAL) {
                    // Move in x axis
                    for(int pos = initialY; pos < initialY + size; pos++) {
                        if(matrix[initialX][pos] == SHOT) {
                            cont++;
                        }
                    }
                } else if(orientation == Orientation::VERTICAL) {
                    // Move in y axis
                    for(int pos = initialX; pos < initialX + size; pos++) {
                        if(matrix[pos][initialY] == SHOT) {
                            cont++;
                        }
                    }
                }
                // Ship is sunken
                if(cont == size) {
                    cout << "SHIP DESTROYED!" << endl;
                    this->alive--;
                }
                break;
            }
        }
    }
}

bool Board::isGameFinished() {
    return this->alive == 0;
}
