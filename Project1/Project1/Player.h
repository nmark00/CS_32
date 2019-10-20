//
//  Player.hpp
//  Project1
//
//  Created by Nicholas Mark on 4/3/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#include <iostream>
#include <string>
#include <cassert>


#include <stdio.h>
class Arena;
class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

#endif /* Player_hpp */
