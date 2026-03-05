#include <bits/stdc++.h>
using namespace std;

bool prima(int n){
    if (n <= 1){
        return false;
    }
    int i;
    for(int i = 2; i < n; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

void cariprima(int l, int r){
    bool ketemu = false;
    int i;
    for(i = l; i <= r; i++){
        if(prima(i)){
            cout << i << " ";
            ketemu = true;
        }
    }
    if(!ketemu){
        cout << "Gada yang prima" << endl;
    }
}

int main(){

    int l, r;
    cout << "Masukkan batas angka ex: 1 15" << endl;
    cin >> l >> r;
    cariprima(l, r);
    return 0;
}