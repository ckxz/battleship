//
//  Ship.hpp
//  Battleship
//
//  Created by Arnau Coiduras on 25/05/2019.
//  Copyright © 2019 Arnau Coiduras. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

typedef enum {
    HORIZONTAL, VERTICAL
} Orientation;

class Ship {
private:
    int size;
    int x;
    int y;
    Orientation orientation;
public:
    Ship(int size, int x, int y, Orientation orientation);
    int getSize();
    int getX();
    int getY();
    Orientation getOrientation();
};

#endif /* Ship_hpp */
