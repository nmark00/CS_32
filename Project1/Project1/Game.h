//
//  Game.hpp
//  Project1
//
//  Created by Nicholas Mark on 4/3/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include <iostream>
#include <string>
#include <cassert>


#include <stdio.h>
class Arena;
class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif /* Game_hpp */
