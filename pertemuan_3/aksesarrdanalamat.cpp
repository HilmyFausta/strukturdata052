#include <bits/stdc++.h>
using namespace std;

int main(){

    int arr[] = {1, 67, 96, 87, 100, -1};
    
    int i;
    for(i = 0; i < 10; i++){
        cout << arr[i] << endl;
        cout << "alamat : " << &arr[i] << endl;
    }

    return 0;
}