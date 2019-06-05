//
//  Position.hpp
//  Battleship
//
//  Created by Arnau Coiduras on 01/06/2019.
//  Copyright © 2019 Arnau Coiduras. All rights reserved.
//

#ifndef Position_hpp
#define Position_hpp

class Position {
private:
    int x;
    int y;
public:
    Position(int x, int y);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};

#endif /* Position_hpp */
