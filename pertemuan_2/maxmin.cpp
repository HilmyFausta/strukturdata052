#include <bits/stdc++.h>
using namespace std;

int carimin(int arr[], int n){
    int res = arr[0];
    int i;
    for(i = 0; i < n; i++){
        res = min(res, arr[i]);
    }
    return res;
}

int carimax(int arr[], int n){
    int res = arr[0];
    int i;
    for(i = 0; i < n; i++){
        res = max(res, arr[i]);
    }
    return res;
}

int main(){

    int arr[] = {10, 27, 100, 67, -28, 1};
    int n = sizeof(arr) / sizeof(int);
    cout << "Elemen minimum adalah : " << carimin(arr, n) << endl;
    cout << "Elemen maksimum adalah : " << carimax(arr, n);

    return 0;
}