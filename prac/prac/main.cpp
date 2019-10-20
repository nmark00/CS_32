//
//  main.cpp
//  prac
//
//  Created by Nicholas Mark on 4/15/19.
//  Copyright © 2019 Nicholas Mark. All rights reserved.
//

#include <iostream>
using namespace std;

class A{
public:
    A(){cout<<"DC"<<endl; };
    A(const A& other)
    {
        cout<< "CC"<<endl;
    }
    A& operator=(const A& other)
    {
        cout<<"AO"<<endl; return *this;
    }
    ~A(){cout<<"Destructor!"<<endl;}
};

int main(){
    A arr[3];
    arr[0] = arr[1];
    A x = arr[0];
    x= arr[1];
    A y(arr[2]);
    cout<<"done"<<endl;
}
