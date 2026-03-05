#include <bits/stdc++.h>
using namespace std;

int main(){

    cout << "Siapa namamu?" << endl;
    string nama;
    getline(cin, nama);

    cout << "Berapa umurmu?" << endl;
    int umur;
    cin >> umur;
    
    cout << "Namamu adalah: " << nama << endl;
    cout << "Umurmu " << umur << " tahun" << endl;

    return 0;
}