//
//  diff.cpp
//  Proj-4
//
//  Created by Nicholas Mark on 6/1/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#include "diff.h"
//**check if adding all is shorter
void diffMaker(hashTable m_hashTable, string foldString, string fnewString, string& diff)
{
    string addMe;
    int newIndex = 0;
    int runSize = 0;//checks how long to copy
    int maxRun;
    int bestIndex;//best index in the vector
    while (newIndex < fnewString.size())
    {
        if (newIndex >= fnewString.size() - 7)//add the last 1-3 char
        {
            for (; newIndex < fnewString.size(); newIndex++)
                addMe += fnewString[newIndex];
            diff += "A";
            diff += to_string(addMe.size());
            diff += ":";
            diff += addMe;
            break;
        }
        
        string hashMe = fnewString.substr(newIndex, 8);//create miniString
        vector<int> indexes;//get number of indexes in foldString
        //        if (newIndex == fnewString.size() -3)
        //            addMe += hashMe;
        /*else*/ if (!m_hashTable.miniStringExist(hashMe, indexes))
        {
            //cout<<"adding: "<<hashMe[0]<<endl;
            addMe += hashMe[0];
            newIndex++;
            continue;
        }
        //copying command
        maxRun = 0;
        bestIndex = 0;
        for (int i =0; i<indexes.size(); i++)//vector of indexes of repeated substrings
        {
            runSize = 0;//checks how long to copy
            
            for (int j = 0; j <fnewString.size() - newIndex && j<foldString.size() - indexes[i] ; j++)
            {
                if (fnewString[j + newIndex] == foldString[ indexes[i] + j ])
                    runSize++;
                else
                    break;
                
            }
            if (runSize > maxRun)//update maxrun
            {
                maxRun = runSize;
                bestIndex = indexes[i];
            }
        }//finished checking all indexes in the in the found hashTable
        
        
        if (to_string(bestIndex).size() > maxRun)
        {
            for (int j=0; j<maxRun; j++)
                addMe += foldString[bestIndex + j];
            newIndex += maxRun;
            continue;
        }
        
        
        if (addMe.size() > 0)
        {
            diff += "A";
            diff += to_string(addMe.size());
            diff += ":";
            diff += addMe;
            addMe = "";
        }
        if (newIndex +8 >= fnewString.size())//make sure newIndex is small enough
            continue;//break;
        
        
        newIndex += maxRun;
        //add everything that needs to be copied
        diff += "C";
        diff += to_string(maxRun);
        diff += ',';
        diff += to_string(bestIndex);
    }//end of while loop
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    //    fold.seekg(0, fold.end);//put cursor at the end of the file
    //    int fold_length = (int)fold.tellg();//store location as length
    //    fold.seekg(0, fold.beg);
    //    char* fold_buffer = new char[fold_length];//create cstring with length of file
    //    fold.read(fold_buffer, fold_length);
    //    string foldString = fold_buffer;
    //
    //    fnew.seekg(0, fnew.end);
    //    int fnew_length = (int)fnew.tellg();
    //    fnew.seekg(0, fnew.beg);
    //    char* fnew_buffer = new char[fnew_length];
    //    fnew.read(fnew_buffer, fnew_length);
    //    string fnewString = fnew_buffer;
    //
    string foldString;
    string fnewString;
    string diff;
    
    // getline returns infile; the while tests its success/failure state
    char c;
    while (fold.get(c))
    {
        foldString += c;
    }
    // getline returns infile; the while tests its success/failure state
    while (fnew.get(c))
    {
        fnewString += c;
    }
    //    cout<<"fold:"<<foldString<<endl;
    //    cout<<"fnew:"<<fnewString<<endl;
    
    hashTable m_hashTable(foldString); //create hashtable
    m_hashTable.slice(); //turns a string into chunks and stores into hashtable
    
    diffMaker(m_hashTable, foldString, fnewString, diff);
    
    fdiff.write(diff.c_str(), diff.length());//convert diff string back into ostream
}

bool commandA(string diff, string& fnewString, int& index)
{
    char cursor = diff[index];
    string intBuffer;
    while (cursor != ':')
    {
        //cerr<<"cursor " <<cursor<<endl;
        if (!isdigit(cursor))
            return false;
        intBuffer += diff[index];
        index++;
        cursor = diff[index];
        //cerr<<"cursor " <<cursor<<endl;
    }
    index++;//now pointing to the chars, not :
    int lengthOfSubstr = stoi(intBuffer);
    
    if (index + lengthOfSubstr > diff.size())
        return false;
    
    fnewString += diff.substr(index, lengthOfSubstr);
    //    cerr<<fnewString<<endl;
    index += lengthOfSubstr;//advance index
    //    cerr<<"index: "<<index<<endl;
    return true;
}

bool commandC(string diff, string& fnewString, string foldString, int& index)
{
    char cursor = diff[index];
    string intBuffer;
    
    while (cursor != ',')
    {
        if (!isdigit(cursor))
        {
            //            cerr<<"not a digit! 1";
            return false;
        }
        intBuffer += diff[index];
        cursor = diff[index];
        index++;
    }
    //index++;//now pointing to the chars, not :
    cursor = diff[index];
    int lengthOfSubstr = stoi(intBuffer);//convert string to int
    //    cerr << "C-lengthOfSubstr "<<lengthOfSubstr<<endl;
    //    if (index + lengthOfSubstr > diff.size())
    //        return false;
    
    intBuffer = "";//reset the intBuffer
    while (cursor != 'A' && cursor != 'C' && index < diff.size())
    {
        //        cerr<<"C-cursor: "<<cursor<<endl;
        if (!isdigit(cursor))
        {
            //            cerr<<"not a digit! 2";
            return false;
        }
        intBuffer += diff[index];
        index++;
        cursor = diff[index];
    }
    //index++;//now pointing to A or C
    //    cerr<< "C-index: "<< stoi(intBuffer)<<endl;
    //    cerr<< "stoi(intBuffer) + lengthOfSubstr = "<<stoi(intBuffer) + lengthOfSubstr<<endl;
    //    cerr<<"stoi(intBuffer) = "<<stoi(intBuffer)<<endl;
    //    cerr<<"lengthOfSubstr = "<<lengthOfSubstr<<endl;
    //    cerr<< "foldString.size() = "<<foldString.size()<<endl;
    //    cerr<<"diff: "<<diff<<endl;
    //    cerr<< "substr: "<< foldString.substr( stoi(intBuffer), lengthOfSubstr)<<endl;
    
    //****************** added 2 to foldString.size() ******************
    if (stoi(intBuffer) + lengthOfSubstr > foldString.size())//make sure you can copy it over
    {
        //        cerr<<"greater than foldString.size()"<<endl;
        return false;
    }
    
    fnewString += foldString.substr( stoi(intBuffer), lengthOfSubstr);
    //    cerr<<fnewString<<endl;
    //    cerr<<"from C- index: "<<index<<endl;
    return true;
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    string foldString;
    string fnewString;
    string diff;
    
    // getline returns infile; the while tests its success/failure state
    char c;
    while (fold.get(c))
    {
        foldString += c;
    }
    // getline returns infile; the while tests its success/failure state
    while (fdiff.get(c))
    {
        diff += c;
    }
    
    int index = 0;
    
    while (index < diff.size())
    {
        if (diff[index] == 'A')
        {
            index++;
            if (!commandA(diff, fnewString, index))
                return false;
            //            cerr<<"applyDiff- index: "<<index<<endl;
        }
        else if (diff[index] == 'C')
        {
            index++;
            if (!commandC(diff, fnewString, foldString, index))
                return false;
            //            cerr<<"fnewString:"<<endl<<fnewString<<endl;
        }
        else if (diff[index] == '\n' || diff[index] == '\r')
            continue;
        else
            return false;
    }
    
    fnew.write(fnewString.c_str(), fnewString.length());
    //cerr<<fnewString;
    
    return true;
}
