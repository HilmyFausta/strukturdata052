#include <bits/stdc++.h>
using namespace std;

string antrian[10];
int front = -1;
int back = -1;

bool cekfull() {
    return back == 9;
}

bool cekkosong() {
    return front == -1 || front > back;
}

void enqueue(string nama) {
    if (cekfull()) {
        cout << "Antrian Penuh!\n";
    } else {
        if (cekkosong()){
            front = 0;
        }
        back++;
        antrian[back] = nama;
        cout << nama << " masuk antrean.\n";
    }
}

void dequeue() {
    if (cekkosong()) {
        cout << "Antrian Kosong!\n";
    } else {
        cout << "Melayani mahasiswa: " << antrian[front] << endl;
        front++;
    }
}

void tampilkan() {
    if (cekkosong()) {
        cout << "Antrian Kosong.\n";
    } else {
        cout << "Kondisi Antrian: ";
        for (int i = front; i <= back; i++) {
            cout << "[" << antrian[i] << "] ";
        }
        cout << endl;
    }
}

int main() {
    
    enqueue("A");
    enqueue("B");
    enqueue("C");
    tampilkan();

    dequeue();
    
    enqueue("D");
    tampilkan();

    return 0;
}