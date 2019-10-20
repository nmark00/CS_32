//
//  main.cpp
//  HW3_linear
//
//  Created by Nicholas Mark on 5/6/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//bool somePredicate(string s)
//{
//    return s.empty();
//}
bool somePredicate(string s)
{
    int nDigits = 0;
    for (int k = 0; k != s.size(); k++)
    {
        if (isdigit(s[k]))
            nDigits++;
    }
    //cerr<<nDigits<<endl;
    return nDigits == 4;
}


// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if (n<0) {
        return false;
    }
    if (n==0) {
        return true;
    }
    if (somePredicate(a[n-1])) {
        return allTrue(a, n-1);
    }
    //cerr<<n<<endl;
    return false;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    if (n<=0)
        return 0;

    if (!somePredicate(a[n-1]))
        return 1 + countFalse(a, n-1);
    else
        return countFalse(a, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    if (n<=0)
        return -1;
    if (! somePredicate(a[0]))
        return 0;
    else
        return 1 + firstFalse(a +1, n -1);

}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
    if (n<=0)
        return -1;
    
    if (a[0]<= a[1+indexOfLeast(a+1, n-1)])
        return 0;
    
    return 1+ indexOfLeast(a+1, n-1);
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 < 0 || n1 < 0 || n2 > n1){
        return false;
    }
    
    if (n2 == 0)
        return true;
    if (a1[0] == a2[0]){
        return includes(a1+1, n1-1, a2+1, n2-1);
    }
    return includes(a1+1, n1-1, a2, n2);
}

int main() {
    // insert code here...
    string test_allTrue[] = {"1346", "2465", "5795", "3573", "5865"};
    assert(allTrue(test_allTrue, 5));
    
    string test_countFalse[] = {"1243", "2463", "234", "23"};
    assert(countFalse(test_countFalse, 4)==2);
    
    string test_firstFalse[] = {"2353", "2645", "234", "2354"};
    assert(firstFalse(test_firstFalse, 4) == 2);
    
    string test_indexOfLeast[] = {"1253", "2343", "7353", "9999", "4354", "3453"};
    assert(indexOfLeast(test_indexOfLeast, 6)== 0);
    
    string a1[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
    string a21[] = {"kyle", "kenny", "butters"};
    string a22[] = {"kyle", "cartman", "cartman"};
    string a23[] = {"kyle", "butters", "kenny"};
    string a24[] = {"stan", "kenny", "kenny"};
    assert(includes(a1, 7, a21, 3));
    assert(includes(a1, 7, a22, 3));
    assert(!includes(a1, 7, a23, 3));
    assert(!includes(a1, 7, a24, 3));
    
    return 0;
}
