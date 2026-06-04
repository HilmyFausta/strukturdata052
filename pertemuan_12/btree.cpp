#include <iostream>
#include <vector>
using namespace std;

const int ORDER = 3;

struct BNode {
  vector<int> keys;
  vector<BNode *> children;
  bool isLeaf;
  BNode(bool leaf) : isLeaf(leaf) {}
};

class BTree {
  BNode *root;

  void splitChild(BNode *p, int i) {
    BNode *child = p->children[i];
    BNode *newNode = new BNode(child->isLeaf);
    int mid = ORDER / 2;

    int midKey = child->keys[mid];

    newNode->keys.assign(child->keys.begin() + mid + 1, child->keys.end());
    child->keys.resize(mid);

    if (!child->isLeaf) {
      newNode->children.assign(child->children.begin() + mid + 1,
                               child->children.end());
      child->children.resize(mid + 1);
    }

    p->keys.insert(p->keys.begin() + i, midKey);
    p->children.insert(p->children.begin() + i + 1, newNode);
  }

  void insertNonFull(BNode *node, int key) {
    int i = node->keys.size() - 1;
    if (node->isLeaf) {
      node->keys.push_back(0);
      while (i >= 0 && key < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        i--;
      }
      node->keys[i + 1] = key;
    } else {
      while (i >= 0 && key < node->keys[i])
        i--;
      i++;
      if ((int)node->children[i]->keys.size() == ORDER - 1) {
        splitChild(node, i);
        if (key > node->keys[i])
          i++;
      }
      insertNonFull(node->children[i], key);
    }
  }

  void inorder(BNode *node) {
    if (!node)
      return;
    int n = node->keys.size();
    for (int i = 0; i < n; i++) {
      if (!node->isLeaf)
        inorder(node->children[i]);
      cout << node->keys[i] << " ";
    }
    if (!node->isLeaf)
      inorder(node->children[n]);
  }

  bool search(BNode *node, int key) {
    int i = 0;
    while (i < (int)node->keys.size() && key > node->keys[i])
      i++;
    if (i < (int)node->keys.size() && key == node->keys[i])
      return true;
    if (node->isLeaf)
      return false;
    return search(node->children[i], key);
  }

public:
  BTree() { root = new BNode(true); }

  void insert(int key) {
    if ((int)root->keys.size() == ORDER - 1) {
      BNode *newRoot = new BNode(false);
      newRoot->children.push_back(root);
      splitChild(newRoot, 0);
      root = newRoot;
    }
    insertNonFull(root, key);
  }

  bool search(int key) { return search(root, key); }

  void inorder() {
    inorder(root);
    cout << endl;
  }
};

int main() {
  BTree bt;
  bt.insert(10);
  bt.insert(20);
  bt.insert(30);
  bt.insert(40);
  bt.insert(50);

  bt.inorder();
  cout << bt.search(30) << endl;
  cout << bt.search(99) << endl;
}