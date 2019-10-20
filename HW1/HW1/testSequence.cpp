
#include "Sequence.h"
#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}

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
    test();
    
    cout << "Passed all tests" << endl;
    }
