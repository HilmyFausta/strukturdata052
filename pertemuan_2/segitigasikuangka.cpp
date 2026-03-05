#include <bits/stdc++.h>
using namespace std;

int main(){

    int angka = 1;
    int baris;

    cout << "mau berapa baris?" << endl;
    cin >> baris;

    int i, j;
    for(i = 0; i <= baris; i++){
        for(j = 0; j < i; j++){
            cout << angka << " ";
            angka++;
        }
        cout << "\n";
    }

    return 0;
}