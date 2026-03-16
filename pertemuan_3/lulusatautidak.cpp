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

    printf("\n -- STATUS KELULUSAN -- \n");

    for(i = 0; i < 5; i++){
        if(nilai[i] >= 75){
             cout << "Mahasiswa ke-" << i + 1 << " : Lulus" << endl;
        }else{
            cout << "Mahasiswa ke-" << i + 1 << " : Tidak Lulus" << endl;
        }
       
    }

return 0;
}