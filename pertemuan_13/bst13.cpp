#include <iostream>
using namespace std;

// Struktur node dasar
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Fungsi membuat node baru
Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fungsi Insert (Penyisipan)
Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);
    
    // Logika persimpangan: Ke kiri atau ke kanan?
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
        
    return root;
}

// Fungsi Inorder Traversal (Menampilkan data terurut)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Fungsi Search (Pencarian)
bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (root->data == key) return true; // Target ditemukan
    
    // Navigasi satu arah membuang cabang yang salah
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

int main() {
    Node* root = NULL;
    
    // Memasukkan contoh data
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);

    cout << "Data Terurut (Inorder): ";
    inorder(root);
    cout << endl;

    int target = 40;
    if (search(root, target)) {
        cout << "Data " << target << " ditemukan!" << endl;
    } else {
        cout << "Data tidak ditemukan." << endl;
    }

    return 0;
}