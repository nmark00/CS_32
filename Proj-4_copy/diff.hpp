//
//  diff.hpp
//  Proj-4
//
//  Created by Nicholas Mark on 6/1/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#ifndef diff_hpp
#define diff_hpp
#include "hashTable.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdio.h>



bool getInt(istream& inf, int& n);
void diffMaker(hashTable m_hashTable, string foldString, string fnewString, string& diff);
void createDiff(istream& fold, istream& fnew, ostream& fdiff);
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);


#endif /* diff_hpp */
