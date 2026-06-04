#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
        string name;
        Node* parent;
        vector<Node*> children;

        Node(string folderName, Node* p = NULL){
            name = folderName;
            parent = p;
        }
};

class FolderTree{
    private:
        Node* root;

    public:
        FolderTree(){
            root = new Node("root");
        }

        Node* getRoot(){
            return root;
        }

        void addFolder(Node* parent, string name){
            Node* newFolder = new Node(name, parent);

            parent->children.push_back(newFolder);

            cout << "Folder '" << name << "' berhasil ditambahkan ke '" << parent->name << "'\n";
        }

        void printTree(Node* node, int level = 0){
            if(!node) return;

            for(int i = 0; i < level; i++){
                cout << "|  ";
            }

            if(level > 0) cout << "|--";
            
            cout << node->name << "\n";

            for(Node* child : node->children){
                printTree(child, level + 1);
            }
        }

        void preOrder(Node* node){
            if(!node) return;

            cout << node->name << "\n";

            for(Node* child : node->children){
                preOrder(child);
            }
        }

        void postOrder(Node* node){
            if(!node) return;

            for(Node* child : node->children){
                postOrder(child);
            }

            cout << node->name << "\n";
        }

        Node* search(Node* node, string name){
            if(!node) return NULL;

            if(node->name == name) return node;

            for(Node* child : node->children){
                Node* res = search(child, name);

                if(res) return res;
            }

            return NULL;
        }

        int countFolder(Node* node){
            if(!node) return 0;

            int tol = 1;

            for(Node* child : node->children){
                tol += countFolder(child);
            }

            return tol;
        }

        void showPath(Node* node){
            if(!node) return;

            vector<string> path;

            Node* curr = node;

            while(curr){
                path.push_back(curr->name);
                curr = curr->parent;
            }

            cout << "Path: ";

            for(int i = path.size() - 1; i >= 0; i--){
                cout << path[i];

                if(i != 0) cout << "/";
            }

            cout << "\n";
        }

        void deleteSubtree(Node* node){
            if(!node) return;

            for(Node* child : node->children){
                deleteSubtree(child);
            }

            delete node;
        }

        void deleteFolder(string name){
            Node* t = search(root, name);

            if(!t){
                cout << "Folder tidak ditemukan!\n";
                return;
            }

            if(t == root){
                cout << "root tidak dapat dihapus!\n";
                return;
            }

            Node* p = t->parent;

            for(auto it = p->children.begin(); it != p->children.end(); it++){
                if(*it == t){
                    p->children.erase(it);
                    break;
                }
            }

            deleteSubtree(t);

            cout << "Folder berhasil dihapus!\n";
        }
};

void menu(){
    cout << "\n========== FILE EXPLORER ==========\n";
    cout << "1. Tambah Folder\n";
    cout << "2. Tampilkan Struktur Folder\n";
    cout << "3. Cari Folder\n";
    cout << "4. Hitung Total Folder\n";
    cout << "5. Hapus Folder\n";
    cout << "6. Preorder Traversal\n";
    cout << "7. Postorder Traversal\n";
    cout << "0. Keluar\n";
    cout << "===================================\n";
    cout << "Pilihan : ";
}

int main(){
    FolderTree tree;
    Node* root = tree.getRoot();

    while(true){
        menu();
        int pilih;
        cin >> pilih;

        if(pilih == 1){
            string folder, name;

            cout << "Nama folder parent: ";
            cin >> folder;

            Node* parent = tree.search(root, folder);

            if(!parent){
                cout << "Folder parent tidak ditemukan!\n";
                continue;
            }

            cout << "Nama folder baru: ";
            cin >> name;

            tree.addFolder(parent, name);
        }
        else if(pilih == 2){
            cout << "\n===== STRUKTUR FOLDER =====\n";
            tree.printTree(root);
        }
        else if(pilih == 3){
            string folder;

            cout << "Nama folder yang dicari: ";
            cin >> folder;

            Node* f = tree.search(root, folder);

            if(f){
                cout << "Folder ditemukan!\n";
                tree.showPath(f);
            }
            else cout << "Folder tidak ditemukan!\n";
        }
        else if(pilih == 4){
            cout << "Total folder: " << tree.countFolder(root) << "\n";
        }
        else if(pilih == 5){
            string folder;

            cout << "Nama folder yang ingin dihapus: ";
            cin >> folder;

            tree.deleteFolder(folder);
        }
        else if(pilih == 6){
            cout << "\n===== PREORDER =====\n";
            tree.preOrder(root);
        }
        else if(pilih == 7){
            cout << "\n===== POSTORDER =====\n";
            tree.postOrder(root);
        }
        else if(pilih == 0){
            cout << "Program selesai\n";
            break;
        }
        else cout << "Pilihan tidak valid!\n";
    }

    return 0;
}