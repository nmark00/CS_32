//
//  global.hpp
//  Project1
//
//  Created by Nicholas Mark on 4/4/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//


#include <cassert>

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#ifndef global_h
#define global_h
using namespace std;


#include <stdio.h>

const int MAXROWS = 20;              // max number of rows in the arena
const int MAXCOLS = 30;              // max number of columns in the arena
const int MAXZOMBIES = 150;          // max number of zombies allowed
const int INITIAL_ZOMBIE_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

#endif /* global_hpp */
