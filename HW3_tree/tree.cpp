#include <iostream>
#include <string>
using namespace std;
  // Return the number of ways that all n2 elements of a2 appear
  // in the n1 element array a1 in the same order (though not
  // necessarily consecutively).  The empty sequence appears in a
  // sequence of length n1 in 1 way, even if n1 is 0.
  // For example, if a1 is the 7 element array
  //    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
  // then for this value of a2            the function must return
  //    "stan" "kenny" "cartman"                      1
  //    "stan" "cartman" "butters"                    2
  //    "kenny" "stan" "cartman"                      0
  //    "kyle" "cartman" "butters"                    3

int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2<=0)
		return 1;
	if (n1<=1)
	{
		if (n2 == 1 && a1[0] == a2[0])
			return 1;
		else
			return 0;
	}
	
	if (a1[0] == a2[0])
	{
		return countIncludes(a1+1, n1-1, a2, n2)+countIncludes(a1+1, n1-1, a2+1, n2-1);
	}
	return countIncludes(a1+1, n1-1, a2, n2);
}

  // Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

  // Rearrange the elements of the array so that all the elements
  // whose value is < separator come before all the other elements,
  // and all the elements whose value is > separator come after all
  // the other elements.  Upon return, firstNotLess is set to the
  // index of the first element in the rearranged array that is
  // >= separator, or n if there is no such element, and firstGreater is
  // set to the index of the first element that is > separator, or n
  // if there is no such element.
  // In other words, upon return from the function, the array is a
  // permutation of its original value such that
  //   * for 0 <= i < firstNotLess, a[i] < separator
  //   * for firstNotLess <= i < firstGreater, a[i] == separator
  //   * for firstGreater <= i < n, a[i] > separator
  // All the elements < separator end up in no particular order.
  // All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
                                    int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;

      // It will always be the case that just before evaluating the loop
      // condition:
      //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
      //  Every element earlier than position firstNotLess is < separator
      //  Every element from position firstNotLess to firstUnknown-1 is
      //    == separator
      //  Every element from firstUnknown to firstGreater-1 is not known yet
      //  Every element at position firstGreater or later is > separator

    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

  // Rearrange the elements of the array so that
  // a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
  // If n <= 1, do nothing.
void order(string a[], int n)
{
	if (n<=1)
		return;
	int firstNotLess=0;
	int firstGreater=0;
	separate(a, n, a[0], firstNotLess, firstGreater);
	order(a, firstNotLess);
	order(a+firstGreater, n- firstGreater);
}

int main()
{
	string a1[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
    string a21[] = {"stan", "kenny", "cartman"};
    string a22[] = {"stan", "cartman", "butters"};
    string a23[] = {"kenny", "stan", "cartman"};
    string a24[] = {"kyle", "cartman", "butters"};
    cout<<countIncludes(a1, 7, a21, 3)<<endl;
    cout<<countIncludes(a1, 7, a22, 3)<<endl;
    cout<<countIncludes(a1, 7, a23, 3)<<endl;
    cout<<countIncludes(a1, 7, a24, 3)<<endl;

    string test[] = {"112", "543", "223", "364", "634", "241", "857", "334", "933"};
    order(test, 9);

    for (int i = 0; i < 9; ++i)
    {
    	cout<<test[i]<<" ";
    }
    cout<<endl;
	return 0;
}
