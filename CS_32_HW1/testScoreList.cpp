
#include "Sequence.h"
#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;



void test2()
{
    ScoreList s;
    s.add(10);
    s.add(12);
    s.add(15);
    s.add(16);
    s.add(2);
    s.add(22);
    assert(s.minimum() == 2);
    assert(s.maximum() == 22);
}

int main()
{
    test2();
    
    cout << "Passed all tests" << endl;
}

