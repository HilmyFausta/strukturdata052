#include <bits/stdc++.h>
using namespace std;

struct mahasiswa{
    string nim, nama, prodi;
    float ipk;
};

int main(){

    mahasiswa mhs1, mhs2;
    mhs1.nim = "5025251052";
    mhs1.prodi = "Teknik Informatika";
    cout << "Masukan nama mahasiswa dengan nrp " << mhs1.nim << endl;
    cin >> mhs1.nama;
    cout << "Masukan ipk mahasiswa " << mhs1.nama << endl;
    cin >> mhs1.ipk;

    mhs2.nim = "206767381";
    mhs2.prodi = "Teknik Mesin";
    mhs2.ipk = 3.99;
    cout << "Masukan nama mahasiswa dengan nrp " << mhs2.nim << endl;
    cin >> mhs2.nama;

    printf("\n\n");

    cout << "NIM mhs1 : " << mhs1.nim << endl;
    cout << "Nama mhs 1 : " << mhs1.nama << endl;
    cout << "Prodi mhs 1 : " << mhs1.prodi << endl;
    cout << "IPK mhs 1 : " << mhs1.ipk << endl;

    printf("\n");

    cout << "NIM mhs2 : " << mhs2.nim << endl;
    cout << "Nama mhs 2 : " << mhs2.nama << endl;
    cout << "Prodi mhs 2 : " << mhs2.prodi << endl;
    cout << "IPK mhs 2 : " << mhs2.ipk << endl;


    return 0;
}