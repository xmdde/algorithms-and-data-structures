#include <iostream>
#include <vector>
#include <fstream>
#include "RedBlackTree.h"
using namespace std;

void presentation(const int n, int *toInsert, int *toDelete);
void experiment(const int n, int *toInsert, int *toDelete);
int comps = 0;
int readAndReplacements = 0;

void RedBlackTree::initializeNULLNode(Node* node, Node* parent) {
    node->key = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 'B';
}

void RedBlackTree::insert(int key) {
    Node* node = new Node;
    node->parent = nullptr;
    node->key = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 'R';

    Node* y = nullptr;
    Node* x = this->root;
    readAndReplacements += 2;

    while (x != TNULL) {
        readAndReplacements++;
        comps++;
        y = x;
        if (node->key < x->key) {
            readAndReplacements++;
            x = x->left;
        } else {
            readAndReplacements++;
            x = x->right;
        }
    }
    node->parent = y;
    readAndReplacements += 2;
    if (y == nullptr) {
        readAndReplacements += 1;
        root = node;
    } else if (node->key < y->key) {
        readAndReplacements++;
        y->left = node;
        comps++;
    } else {
        readAndReplacements++;
        y->right = node;
        comps++;
    }

    if (node->parent == nullptr) {
        readAndReplacements++;
        node->color = 'B';
        return;
    }

    if (node->parent->parent == nullptr) {
        readAndReplacements++;
        return;
    }
    insertFix(node);
}

void RedBlackTree::insertFix(Node* k) {
    Node* u;
    while (k->parent->color == 'R') {
        readAndReplacements++;
        comps++;
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            readAndReplacements++;

            if (u->color == 'R') {
                u->color = 'B';
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                k = k->parent->parent;
                readAndReplacements++;
            } 
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    readAndReplacements++;
                    rightRotate(k);
                }
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                leftRotate(k->parent->parent);
            }
        } 
        else {
            readAndReplacements++;
            u = k->parent->parent->right;

            if (u->color == 'R') {
                u->color = 'B';
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                k = k->parent->parent;
                readAndReplacements++;
            } 
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    readAndReplacements++;
                    leftRotate(k);
                }
                k->parent->color = 'B';
                k->parent->parent->color = 'R';
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 'B';
  }

Node* RedBlackTree::getRoot() {
    return this->root;
}

void RedBlackTree::deleteNode(int key) {
    deleteNodeHelper(this->root, key);
}

void RedBlackTree::deleteFix(Node* x) {
    Node* s;
    while (x != root && x->color == 'B') {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == 'R') {
                s->color = 'B';
                x->parent->color = 'R';
                leftRotate(x->parent);
                s = x->parent->right;
                readAndReplacements++;
            }
            if (s->left->color == 'B' && s->right->color == 'B') {
                s->color = 'R';
                x = x->parent;
                readAndReplacements++;
            } 
            else {
                if (s->right->color == 'B') {
                    s->left->color = 'B';
                    s->color = 'R';
                    rightRotate(s);
                    s = x->parent->right;
                    readAndReplacements++;
                }
                s->color = x->parent->color;
                x->parent->color = 'B';
                s->right->color = 'B';
                leftRotate(x->parent);
                x = root;
                readAndReplacements++;
            }
        } else {
            s = x->parent->left;
            readAndReplacements++;
            if (s->color == 'R') {
                s->color = 'B';
                x->parent->color = 'R';
                rightRotate(x->parent);
                s = x->parent->left;
                readAndReplacements++;
            }

            if (s->right->color == 'B' && s->right->color == 'B') {
                s->color = 'R';
                x = x->parent;
                readAndReplacements++;
            } else {
                if (s->left->color == 'B') {
                    s->right->color = 'B';
                    s->color = 'R';
                    leftRotate(s);
                    s = x->parent->left;
                    readAndReplacements++;
                }
                s->color = x->parent->color;
                x->parent->color = 'B';
                s->left->color = 'B';
                rightRotate(x->parent);
                x = root;
                readAndReplacements++;
            }
        }
    }
    x->color = 'B';
}

void RedBlackTree::deleteNodeHelper(Node* node, int key) {
    Node* z = TNULL;
    Node* x;
    Node* y;
    while (node != TNULL) {
        if (node->key == key) {
            comps++;
            readAndReplacements++;
            z = node;
        }
        if (node->key <= key) {
            comps += 2;
            readAndReplacements++;
            node = node->right;
        } 
        else {
            comps += 3;
            readAndReplacements++;
            node = node->left;
        }
    }
    if (z == TNULL) {
        return;
    }

    y = z;
    readAndReplacements++;
    char y_original_color = y->color;

    if (z->left == TNULL) {
        x = z->right;
        readAndReplacements += 2;
        rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        readAndReplacements += 3;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        readAndReplacements++;
        if (y->parent == z) {
            readAndReplacements++;
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
            readAndReplacements += 2;
        }
        rbTransplant(z, y);
        readAndReplacements += 2;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == 'B') {
        deleteFix(x);
    }
}

Node* RedBlackTree::successor(Node* x) {
    readAndReplacements++;
    if (x->right != TNULL) {
        return minimum(x->right);
    }
    Node* y = x->parent;
    readAndReplacements++;
    while (y != TNULL && x == y->right) {
        x = y;
        y = y->parent;
        readAndReplacements += 2;
    }
    return y;
}

Node* RedBlackTree::predecessor(Node* x) {
    readAndReplacements++;
    if (x->left != TNULL) {
      return maximum(x->left);
    }
    Node* y = x->parent;
    readAndReplacements++;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
      readAndReplacements += 2;
    }
    return y;
}

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    readAndReplacements += 2;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    readAndReplacements++;
    if (x->parent == nullptr) {
        this->root = y;
        readAndReplacements++;
    } else if (x == x->parent->left) {
        x->parent->left = y;
        readAndReplacements += 2;
    } else {
        x->parent->right = y;
        readAndReplacements += 2;
    }
    y->left = x;
    x->parent = y;
    readAndReplacements += 2;
}

void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    readAndReplacements += 2;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    readAndReplacements++;
    if (x->parent == nullptr) {
        this->root = y;
        readAndReplacements++;
    } else if (x == x->parent->right) {
        x->parent->right = y;
        readAndReplacements += 2;
    } else {
        x->parent->left = y;
        readAndReplacements += 2;
    }
    y->right = x;
    x->parent = y;
    readAndReplacements += 2;
  }

void RedBlackTree::rbTransplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
        readAndReplacements++;
    } else if (u == u->parent->left) {
        u->parent->left = v;
        readAndReplacements++;
    } else {
        u->parent->right = v;
        readAndReplacements++;
    }
    v->parent = u->parent;
    readAndReplacements++;
}

int RedBlackTree::height() {
    return height(root);
}

int RedBlackTree::height(Node* root) {
    if (root == NULL) return 0;
    else if (root->left == TNULL && root->right == TNULL) return 1;
    else if (root->right == TNULL) return height(root->left) + 1;
    else if (root->left == TNULL) return height(root->right) + 1;
    else return std::max(height(root->left), height(root->right)) + 1;
}

Node* RedBlackTree::searchTree(int k) {
    return searchTreeHelper(this->root, k);
}

Node* RedBlackTree::searchTreeHelper(Node* node, int key) {
    if (node == TNULL || key == node->key) {
        comps++;
        return node;
    }
    if (key < node->key) {
        comps++;
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

Node* RedBlackTree::minimum(Node* node) {
    while (node->left != TNULL) {
        node = node->left;
        readAndReplacements++;
    }
    return node;
}

Node* RedBlackTree::maximum(Node* node) {
    while (node->right != TNULL) {
        node = node->right;
        readAndReplacements++;
    }
    return node;
}

void RedBlackTree::print() {
    std::vector<int> road;
    print(root, 0, false, road);
    std::cout << '\n';
}

void RedBlackTree::print(Node* root, int gap, bool left_tree, std::vector<int> road) {
    if (root != NULL) {
        if (root->left != TNULL) {
            std::vector<int> left_road = road;
            left_road.push_back(-1);
            print(root->left, gap+1, true, left_road);
        }

        printGap(gap, road);
        if (left_tree)
            std::cout << "/";
        if (!left_tree && gap != 0)
            std::cout << "\\";
        if (root->color == 'R') {
            std::cout << "\033[1;31m" << "-[" << root->key << "]" << "\033[0m" <<std::endl;
        } 
        else std::cout << "-[" << root->key << "]" <<std::endl;

        if (root->right != TNULL) {
            std::vector<int> right_road = road;
            right_road.push_back(1);
            print(root->right, gap+1, false, right_road);
        }
    }
}

void RedBlackTree::printGap(int gap, std::vector<int> road) {
    std::vector<char> output;
    int previous = 0;
    for(int i = road.size()-1; i >= 0; i--){
        if (previous == road[i] || previous == 0)
            output.push_back(' ');
        else {
            if (road[i] == 1 || road[i] == -1)
                output.push_back('|');
        }
        previous = road[i];
    }
    for(int i = output.size()-1; i >= 0; i--)
        std::cout << output.at(i);
}

void RedBlackTree::freeTree(Node* node) { 
    if (node == TNULL) { 
        return;
    } 
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

RedBlackTree::~RedBlackTree() {
    freeTree(root);
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
    RedBlackTree rbtree;
    for (int i = 0; i < n; i++) {
        std::cout << "insert " << toInsert[i] << '\n';
        rbtree.insert(toInsert[i]);
        rbtree.print();
    }
    for (int i = 0; i < n; i++) {
        std::cout << "delete " << toDelete[i] << '\n';
        rbtree.deleteNode(toDelete[i]);
        rbtree.print();
    }
}

void experiment(const int n, int *toInsert, int *toDelete) {
    int maxheight = 0;
    int maxcomps = 0;
    int maxrr = 0;
    long long sumheight = 0;
    long long sumcomps = 0;
    long long sumrr = 0;
    RedBlackTree rbtree;
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list4/rbStats.txt", std::ios::app);

    for (int i = 0; i < n; i++) {
        readAndReplacements = 0;
        comps = 0;
        rbtree.insert(toInsert[i]);
        int h = rbtree.height();

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

    std::ofstream file2("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list4/rbDeleteStats.txt", std::ios::app);
    for (int i = 0; i < n; i++) {
        readAndReplacements = 0;
        comps = 0;
        rbtree.deleteNode(toDelete[i]);
        int h = rbtree.height();

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