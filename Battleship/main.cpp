//
//  main.cpp
//  Battleship
//
//  Created by Arnau Coiduras on 25/05/2019.
//  Copyright © 2019 Arnau Coiduras. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include "Board.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    cout << "WELCOME TO BATTLESHIP" << endl << endl;
    
    // Random seed
    srand((unsigned int) time(NULL));
    
    Board playerBoard = Board();
    playerBoard.setShips();
    cout << "Creating Player Board..." << endl << endl;
    playerBoard.print();
    cout << endl;
    
    Board computerBoard = Board();
    computerBoard.createRandomShips();
    cout << "Creating Computer Board..." << endl << endl;
    computerBoard.printOnlyShot();
    cout << endl;
    
    // Manages the turn
    bool playerTurn = true;
    // Manages the end of the game
    bool endGame = false;
    // Coordinates to shoot
    Position* position;
    int randomX, randomY;
    // Initial message
    string attackPlayerMessage = "Now give a coordinate to attack: ";
    string attackComputerMessage = "Thinking a coordinate to attack...";
    
    while(!endGame) {
        // Ask for coordinates to shoot
        if(playerTurn) {
            // Get coordinates
            position = Utils::readPosition(attackPlayerMessage);
        } else {
            // Random coordinates
            cout << attackComputerMessage << endl;
            randomX = rand() % BOARD_SIZE;
            randomY = rand() % BOARD_SIZE;
            cout << "X: " << randomX << endl;
            cout << "Y: " << randomY << endl;
            position = new Position(randomX, randomY);
        }
        
        // Shoot
        if(playerTurn) {
            computerBoard.shoot(position->getX(), position->getY());
        } else {
            playerBoard.shoot(position->getX(), position->getY());
        }
        
        // Print two boards
        playerBoard.print();
        cout << endl << endl;
        computerBoard.printOnlyShot();
        cout << endl << endl;
        
        // Check game finished
        endGame = playerTurn
        ? computerBoard.isGameFinished() // operador ternario
        : playerBoard.isGameFinished();
        
        // Change turn
        playerTurn = !playerTurn;
    }
    
    // WINNER
    if(playerTurn) {
        cout << "WINNER: COMPUTER" << endl;
    } else {
        cout << "WINNER: PLAYER" << endl;
    }
    
    return 0;
}
