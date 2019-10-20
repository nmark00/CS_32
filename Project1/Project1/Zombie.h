//
//  Zombie.hpp
//  Project1
//
//  Created by Nicholas Mark on 4/3/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#ifndef Zombie_hpp
#define Zombie_hpp
#include <iostream>
#include <string>
#include <cassert>


#include <stdio.h>
class Arena;
class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif /* Zombie_hpp */
