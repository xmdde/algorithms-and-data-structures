#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <vector>

struct Node {
    int key;
    Node *parent;
    Node *left;
    Node *right;
    char color;
};

class RedBlackTree {
private:
    Node* root;
    Node* TNULL;
    void initializeNULLNode(Node* node, Node* parent);
    Node* searchTreeHelper(Node* node, int key);
    int height(Node* root);
    void deleteFix(Node* x);
    void rbTransplant(Node* u, Node* v);
    void deleteNodeHelper(Node* node, int key);
    void insertFix(Node* k);
    void print(Node* root, int gap, bool left_tree, std::vector<int> road);
    void printGap(int gap, std::vector<int> road);
    void freeTree(Node* root);
public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 'B';
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
    ~RedBlackTree();
    void print();
    int height();
    Node* searchTree(int k);
    Node* minimum(Node* node);
    Node* maximum(Node* node);
    Node* successor(Node* x);
    Node* predecessor(Node* x);
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void insert(int key);
    Node* getRoot();
    void deleteNode(int key);
};

#endif