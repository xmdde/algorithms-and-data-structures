#include <iostream>
#include <vector>
#include <fstream>
#include "SplayTree.h"
void presentation(const int n, int *toInsert, int *toDelete);
void experiment(const int n, int *toInsert, int *toDelete);

SplayTree::SplayTree() {
    root = nullptr;
}

void SplayTree::insert(int key) {
    Node* node = new Node;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->data = key;
    Node* y = nullptr;
    Node* x = this->root;
    
    readAndReplacements += 5;
    readAndReplacements++;

    while (x != nullptr) {
        y = x;
        readAndReplacements++;
        comps++;
        if (node->data < x->data) {
            x = x->left;
            readAndReplacements++;
        } else {
            comps++;
            readAndReplacements++;;
            x = x->right;
        }
        readAndReplacements++;
    }

    node->parent = y;
    readAndReplacements += 2;
    if (y == nullptr) {
        readAndReplacements++;
        root = node;
    } else if (node->data < y->data) {
        comps++;
        readAndReplacements++;;
        y->left = node;
    } else {
        comps += 2;;
        readAndReplacements++;
        y->right = node;
    }
    splay(node);
}

void SplayTree::deleteNode(int data) {
    deleteNode(this->root, data);
}

void SplayTree::deleteNode(Node* node, int key) {
    readAndReplacements++;
    Node* x = nullptr;
    Node* t;
    Node* s;
    readAndReplacements++;
    while (node != nullptr) {
        comps++;
        if (node->data == key) {
            readAndReplacements++;
            x = node;
        }

        comps++;
        if (node->data <= key) {
            readAndReplacements++;
            node = node->right;
        } else {
            comps++;
            readAndReplacements++;
            node = node->left;
        }
        readAndReplacements++;
    }

    readAndReplacements++;
    if (x == nullptr) {
        return;
    }
    split(x, s, t); 
    readAndReplacements++;
    if (s->left) { 
        readAndReplacements++;
        s->left->parent = nullptr;
    }
    root = join(s->left, t);
    delete(s);
    readAndReplacements++;
    s = nullptr;
}

int SplayTree::height(){
    return height(this->root);
}

int SplayTree::height(Node* root){
    if (root == nullptr) return 0;
    else if (root->left == nullptr && root->right == nullptr) return 1;
    else if (root->right == nullptr) return height(root->left) + 1;
    else if (root->left == nullptr)  return height(root->right) + 1;
    else return std::max(height(root->left), height(root->right)) + 1;
}

void SplayTree::leftRotate(Node* x) {
    readAndReplacements += 2;
    Node* y = x->right;
    x->right = y->left;

    readAndReplacements++;
    if (y->left != nullptr) {
        readAndReplacements++;
        y->left->parent = x;
    }
    readAndReplacements += 2;
    y->parent = x->parent;
    if (x->parent == nullptr) {
        readAndReplacements++;
        this->root = y;
    } else if (x == x->parent->left) {
        readAndReplacements += 2;
        x->parent->left = y;
    } else {
        readAndReplacements += 3;
        x->parent->right = y;
    }
    readAndReplacements += 2;
    y->left = x;
    x->parent = y;
}

void SplayTree::rightRotate(Node* x) {
    readAndReplacements += 2;
    Node* y = x->left;
    x->left = y->right;

    readAndReplacements++;
    if (y->right != nullptr) {
        readAndReplacements++;
        y->right->parent = x;
    }
    readAndReplacements += 2;
    y->parent = x->parent;
    if (x->parent == nullptr) {
        readAndReplacements++;
        this->root = y;
    } else if (x == x->parent->right) {
        readAndReplacements += 2;
        x->parent->right = y;
    } else {
        readAndReplacements += 3;
        x->parent->left = y;
    }
    readAndReplacements += 2;
    y->right = x;
    x->parent = y;
}

void SplayTree::splay(Node* x) {
    readAndReplacements++;
    while (x->parent) {
        readAndReplacements++;
        if (!x->parent->parent) {
            readAndReplacements++;
            if (x == x->parent->left) {
                // Zig rotation
                rightRotate(x->parent);
            } else {
                readAndReplacements++;
                // Zag rotation
                leftRotate(x->parent);
            }
        } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
            readAndReplacements += 2;
            // Zig-zig rotation
            rightRotate(x->parent->parent);
            rightRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
            readAndReplacements += 4;
            // Zag-zag rotation
            leftRotate(x->parent->parent);
            leftRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
            readAndReplacements += 6;
            // Zig-zag rotation
            leftRotate(x->parent);
            rightRotate(x->parent);
        } else {
            // Zag-zig rotation
            rightRotate(x->parent);
            leftRotate(x->parent);
        }
    }
}

Node* SplayTree::join(Node* s, Node* t) {
    readAndReplacements++;
    if (!s) {
        return t;
    }
    readAndReplacements++;
    if (!t) {
        return s;
    }
    readAndReplacements++;
    Node* x = maximum(s);
    splay(x);
    x->right = t;
    t->parent = x;
    readAndReplacements += 2;
    return x;
}

void SplayTree::split(Node* &x, Node* &s, Node* &t) {
    splay(x);
    readAndReplacements++;
    if (x->right) {
        readAndReplacements += 2;
        t = x->right;
        t->parent = nullptr;
    } else {
        readAndReplacements += 2;
        t = nullptr;
    }
    s = x;
    s->right = nullptr;
    x = nullptr;
    readAndReplacements += 3;
} 

Node* SplayTree::maximum(Node* node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

void SplayTree::print() {
    std::vector<int> road;
    print(this->root, 0, false, road);
    std::cout << '\n';
}

void SplayTree::print(Node* root, int indent, bool left_tree, std::vector<int> road) {
    if (root != nullptr) {
        if (root->left != nullptr) {
            std::vector<int> left_road = road;
            left_road.push_back(-1);
            print(root->left, indent+1, true, left_road);
        }

        printGap(indent, road);
        if (left_tree)
            std::cout << "/-";
        if (!left_tree && indent != 0)
            std::cout << "\\-";
        
        std::cout << "[" << root->data << "]" << std::endl;
        
        if (root->right != nullptr) {
            std::vector<int> right_road = road;
            right_road.push_back(1);
            print(root->right, indent+1, false, right_road);
        }
    }
}

void SplayTree::printGap(int indent, std::vector<int> road) {
    std::vector<char> output;
    int previous = 0;
    for (int i = road.size()-1; i >= 0; i--){
        if (previous == road[i] || previous == 0)
            output.push_back(' ');
        else {
            if (road[i] == 1 || road[i] == -1)
                output.push_back('|');
        }
        previous = road[i];
    }
    for (int i = output.size()-1; i >= 0; i--)
        std::cout << output.at(i);
}

int main(int argc, char *argv[]) {
    if (argc != 1) {
        if (std::string(argv[1]) == "-p") { //presentation mode
            int n;
            std::cin >> n;
            int keysToInsert[n];
            int keysToDelete[n];
            for (int i = 0; i < n; i++) {
                std::cin >> keysToInsert[i];
            }
            for (int i = 0; i < n; i++) {
                std::cin >> keysToDelete[i];
            }
            presentation(n, keysToInsert, keysToDelete);
        }
        if (std::string(argv[1]) == "-e") { //generate stats
            int n;
            std::cin >> n;
            int keysToInsert[n];
            int keysToDelete[n];
            for (int i = 0; i < n; i++) {
                std::cin >> keysToInsert[i];
            }
            for (int i = 0; i < n; i++) {
                std::cin >> keysToDelete[i];
            }
            experiment(n, keysToInsert, keysToDelete);
        }
    }
    return 0;
}

void presentation(const int n, int *toInsert, int *toDelete) {
    SplayTree splayTree;
    for (int i = 0; i < n; i++) {
        std::cout << "insert " << toInsert[i] << '\n';
        splayTree.insert(toInsert[i]);
        splayTree.print();
    }
    for (int i = 0; i < n; i++) {
        std::cout << "delete " << toDelete[i] << '\n';
        splayTree.deleteNode(toDelete[i]);
        splayTree.print();
    }
}

void experiment(const int n, int *toInsert, int *toDelete) {
    int maxheight = 0;
    int maxcomps = 0;
    int maxrr = 0;
    int sumheight = 0;
    int sumcomps = 0;
    int sumrr = 0;
    SplayTree splayTree;
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list4/splayTreeStats.txt", std::ios::app);

    for (int i = 0; i < n; i++) {
        readAndReplacements = 0;
        comps = 0;
        splayTree.insert(toInsert[i]);
        int h = splayTree.height();

        sumheight += h;
        sumcomps += comps;
        sumrr += readAndReplacements;

        if (comps > maxcomps) maxcomps = comps;
        if (h > maxheight) maxheight = h;
        if (readAndReplacements > maxrr) maxrr = readAndReplacements;
    }
    file << n << ';' << sumcomps/n << ';' << maxcomps << ';' << sumrr/n << ';' << maxrr << ';' << sumheight/n << ';' << maxheight << '\n';
    file.close();

    maxheight = 0;
    maxcomps = 0;
    maxrr = 0;
    sumheight = 0;
    sumcomps = 0;
    sumrr = 0;

    std::ofstream file2("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list4/splayTreeDeleteStats.txt", std::ios::app);
    for (int i = 0; i < n; i++) {
        readAndReplacements = 0;
        comps = 0;
        splayTree.deleteNode(toDelete[i]);
        int h = splayTree.height();

        sumheight += h;
        sumcomps += comps;
        sumrr += readAndReplacements;

        if (comps > maxcomps) maxcomps = comps;
        if (h > maxheight) maxheight = h;
        if (readAndReplacements > maxrr) maxrr = readAndReplacements;
    }
    file2 << n << ';' << sumcomps/n << ';' << maxcomps << ';' << sumrr/n << ';' << maxrr << ';' << sumheight/n << ';' << maxheight << '\n';
    file2.close();
}