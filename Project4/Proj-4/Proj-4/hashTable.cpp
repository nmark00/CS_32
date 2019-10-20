//
//  hashTable.cpp
//  Proj-4
//
//  Created by Nicholas Mark on 6/1/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#include "hashTable.h"

// struct three //struct stores sets of 3 char and the index that this mini string is located
// {
//     string miniString;
//     vector<int> index;
// };

// class hashTable
// {
// public:
//     hashTable(string fold);
//     int getNumBuckets();
//     unsigned int hashFunction(const string& hashMe);
//     bool miniStringExist(string checkHash, vector<int>& indexes);
//     void slice();
// private:
//     vector<list<three> > hashLists;
//     int m_numBuckets;
//     string m_fold;
// };

hashTable::hashTable(string fold): hashLists(fold.size() * 3)
{
    m_numBuckets = (int)fold.size() * 3;
    m_fold = fold;
}

int hashTable::getNumBuckets()
{
    return m_numBuckets;
}

unsigned int hashTable::hashFunction(const string& hashMe)
{
    hash<string> str_hash;
    unsigned int hashValue = (int)str_hash(hashMe);
    unsigned int bucketNum = hashValue % m_numBuckets;
    return bucketNum;
}

void hashTable::slice()
{
    bool found = false;
    for (int i=0; i< m_fold.size() - (m_fold.size()%8); i++)
    {
        found = false;
        if (i+7 > m_fold.size())
            break;
        
        string tempString;
        for (int k=0; k<8; k++) //create mini string
            tempString += m_fold[i+k];
        
        int hashIndex = hashFunction(tempString);
        list<three>::iterator findIt;
        for (findIt = hashLists[hashIndex].begin(); findIt != hashLists[hashIndex].end(); findIt++ )
        {
            if ((*findIt).miniString == tempString)//check if tempString exists
            {
                (*findIt).index.push_back(i);
                found = true;
            }
        }//tempString is not found
        if (found)
            continue;
        three tempStruct; //create temporary struct which stores miniString and index
        tempStruct.miniString = tempString;
        tempStruct.index.push_back(i);
        hashLists[hashIndex].push_back(tempStruct);
    }
}


bool hashTable::miniStringExist(string checkHash, vector<int>& indexes)
{
    int bucket = hashFunction(checkHash);
    list<three>::iterator findIt;
    for (findIt = hashLists[bucket].begin(); findIt != hashLists[bucket].end(); findIt++ )
    {
        if ((*findIt).miniString == checkHash)//check if checkHash exists
        {
            indexes = (*findIt).index;
            return true;
        }
    }
    return false;
}
