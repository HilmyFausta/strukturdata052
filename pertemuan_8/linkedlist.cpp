#include <bits/stdc++.h>
using namespace std;

// Struktur Node
struct Node {
    int data;
    Node* next;
};

int main() {
    // Membuat 3 node
    Node* node1 = new Node();
    Node* node2 = new Node();
    Node* node3 = new Node();

    // Isi data
    node1->data = 10;
    node2->data = 20;
    node3->data = 30;

    // Hubungkan node
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;

    // Traversal (menampilkan data)
    Node* current = node1;
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL";

    return 0;
}