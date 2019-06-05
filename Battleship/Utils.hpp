//
//  Utils.hpp
//  Battleship
//
//  Created by Arnau Coiduras on 01/06/2019.
//  Copyright © 2019 Arnau Coiduras. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <string>
#include "Position.hpp"

using namespace std;

class Utils {
private:
    Utils();
public:
    static int readNumber(int min, int max, string errorMsg);
    static Position* readPosition(string initialMessage);
};

#endif /* Utils_hpp */
