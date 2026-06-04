#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

// Insert
Node* insert(Node* root, int data) {
    if (root == nullptr) return new Node(data);
    if (data < root->data)
        root->left  = insert(root->left,  data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Search
bool search(Node* root, int data) {
    if (root == nullptr) return false;
    if (data == root->data) return true;
    if (data < root->data)  return search(root->left,  data);
    return search(root->right, data);
}

// Inorder (hasil terurut)
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Cari node terkecil (untuk delete)
Node* minNode(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// Delete
Node* deleteNode(Node* root, int data) {
    if (root == nullptr) return root;
    if (data < root->data)
        root->left  = deleteNode(root->left,  data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        // Leaf atau 1 child
        if (root->left == nullptr) {
            Node* tmp = root->right;
            delete root;
            return tmp;
        }
        if (root->right == nullptr) {
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        // 2 child: ganti dengan inorder successor
        Node* succ   = minNode(root->right);
        root->data   = succ->data;
        root->right  = deleteNode(root->right, succ->data);
    }
    return root;
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    inorder(root);            
    cout << search(root, 40); 

    root = deleteNode(root, 30);
    inorder(root);            
}