
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "diff.cpp"
using namespace std;



bool runtest(string oldName, string newName, string diffName, string newName2)
{
    if (diffName == oldName  ||  diffName == newName  ||
        newName2 == oldName  ||  newName2 == diffName  ||
            newName2 == newName)
    {
	cerr << "Files used for output must have names distinct from other files" << endl;
	return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream diffFile(diffName, ios::binary);
    if (!diffFile)
    {
        cerr << "Cannot create " << diffName << endl;
        return false;
    }
    createDiff(oldFile, newFile, diffFile);
    diffFile.close();

    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream diffFile2(diffName, ios::binary);
    if (!diffFile2)
    {
        cerr << "Cannot read the " << diffName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    assert(applyDiff(oldFile, diffFile2, newFile2));
    newFile2.close();

    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newfile), istreambuf_iterator<char>(), 
                 istreambuf_iterator<char>(newfile3), istreambuf_iterator<char>())
    {
	
        cerr << newName2 << " is not identical to " << newName
                 << "; test FAILED" << endl;
        return false;
    }
    return true;
}


void runtest(string oldtext, string newtext)
{
    istringstream oldFile(oldtext);
    istringstream newFile(newtext);
    ostringstream diffFile;
    createDiff(oldFile, newFile, diffFile);
    string result = diffFile.str();
    cout << "The diff file length is " << result.size()
         << " and its text is " << endl;
    cout << result << endl;

    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the stream
    istringstream diffFile2(result);
    ostringstream newFile2;
    assert(applyDiff(oldFile, diffFile2, newFile2));
    assert(newtext == newFile2.str());
}


int main()
{
    assert(runtest("myoldfile.txt", "mynewfile.txt", "mydifffile.txt", "mynewfile2.txt"));

    runtest("There's a bathroom on the right.",
		    "There's a bad moon on the rise.");
    runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
            "XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");

    cerr << "Test PASSED" << endl;
}