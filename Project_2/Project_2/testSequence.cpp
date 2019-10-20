#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    // For an empty sequence:
    assert(s.size() == 0);             // test size
    assert(s.empty());                 // test empty
    assert(s.remove("paratha") == 0);  // nothing to remove
}
void test2()
{
    Sequence s;
    s.insert(0, "b");
    s.insert("a");
    s.insert(0, "c");
   s.insert(1, "d");
    Sequence s2(s);
    s2.erase(1);
    string value;
    for (int i=0; i< s.size(); i++) {
        s.get(i, value);
        cout<< value<<endl;
    }
    cout<< endl;
    for (int i=0; i< s2.size(); i++) {
        s2.get(i, value);
        cout<< value<<endl;
    }
    cout<< endl;
    
    //interleave(const s2, const s, Sequence r)
    
}

int main()
{
    test();
    test2();
    cout << "Passed all tests" << endl;
}
