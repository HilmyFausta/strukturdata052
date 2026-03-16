#include <bits/stdc++.h>
using namespace std;

int main(){

    int nilai[5];
    int total = 0;
    float avg;

    int i;
    for(i = 0; i < 5; i++){
        cout << "masukan nilai mahasiswa ke-" << i + 1 << " : ";
        cin >> nilai[i];
        total += nilai[i];
    }

    printf("\n");

    for(i = 0; i < 5; i++){
        cout << "nilai mahasiswa ke-" << i + 1 << " : " << nilai[i] << endl;
    }

    printf("\n");

    avg = total / 5.0;
    cout << "Rata-rata seluruh nilai mahasiswa adalah " << avg << endl;

    int max = nilai[0];
    for(i = 0; i < 5; i++){
        if(nilai[i] > max){
            max = nilai[i];
        }
    }

    cout << "Nilai tertinggi adalah : " << max << endl;
  
    return 0;
}