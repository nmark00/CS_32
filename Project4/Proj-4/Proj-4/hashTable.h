//
//  hashTable.hpp
//  Proj-4
//
//  Created by Nicholas Mark on 6/1/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#ifndef hashTable_h
#define hashTable_h
#include <vector>
#include <functional>
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
using namespace std;

struct three //struct stores sets of 3 char and the index that this mini string is located
{
    string miniString;
    vector<int> index;
};

class hashTable
{
public:
    hashTable(string fold);
    int getNumBuckets();
    unsigned int hashFunction(const string& hashMe);
    bool miniStringExist(string checkHash, vector<int>& indexes);
    void slice();
private:
    vector<list<three> > hashLists;
    int m_numBuckets;
    string m_fold;
};

#endif /* hashTable_hpp */
