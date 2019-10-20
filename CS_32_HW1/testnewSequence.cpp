#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    s.insert(0, 10);
    s.insert(0, 20);
    cerr << s.size();
    assert(s.size() == 2);
    ItemType x = 999;
    assert(s.get(0, x) && x == 20);
    assert(s.get(1, x) && x == 10);
}
void test2()
{
    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // b can hold at most DEFAULT_MAX_ITEMS items
    }
void test3()
{
    Sequence a(5);
    Sequence b(2);
    a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(5);
    
    b.insert(6);
    b.insert(7);
    cout<< a.size()<<endl;
    cout<< b.size()<<endl;
    a.swap(b);
    cout<< a.size()<<endl;
    cout<< b.size()<<endl;
}

int main()
{
    test();
    test3();
    cout << "Passed all tests" << endl;
    }
