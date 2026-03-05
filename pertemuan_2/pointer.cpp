#include <bits/stdc++.h>
using namespace std;

int main(){

    int var = 10;
    int *ptr = &var;

    cout << "Values of x: " << var << "\n";
    cout << "Address of x: " << &var << "\n";
    cout << "Values stored in pointer ptr: " << ptr << "\n";
    cout << "Values pointed to by ptr: " << *ptr << "\n";

    return 0;
}