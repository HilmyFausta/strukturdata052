#include <bits/stdc++.h>
using namespace std;

struct mahasiswa{
    string nrp, nama, jurusan;
    int umur;
    string hobi[3];
};

int main(){

    mahasiswa mhs[2];

    int i, j;
    for(i = 0; i < 2; i++){
        cout << "Data mahasiswa ke-" << i+1 << endl;
        cout << "NRP    : ";
        cin >> mhs[i].nrp;

        cout << "Nama   : ";
        cin >> mhs[i].nama;

        cout << "Jurusan : ";
        cin >> mhs[i].jurusan;

        cout << "Umur   : ";
        cin >> mhs[i].umur;

        cout << "Masukan 3 hobi:" << endl;
        for(j = 0; j < 3; j++){
            cout << "Hobi ke-" << j+1 << " : ";
            cin >> mhs[i].hobi[j];
        }

        cout << endl;
    }

    printf("\n====DATA MAHASISWA====\n");
    for(i = 0; i < 2; i++){
        cout << "\nMahasiswa ke-"<< i+1 << endl;
        cout << "NRP    : " << mhs[i].nrp << endl;
        cout << "Nama   : " << mhs[i].nama << endl;
        cout << "Jurusan : " << mhs[i].jurusan << endl;
        cout << "Hobi   : ";
        for(j = 0; j < 3; j++){
            cout << mhs[i].hobi[j] << " ";
        }
        cout << endl;
    }



    return 0;
}