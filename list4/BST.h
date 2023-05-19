#ifndef BST_H
#define BST_H

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BST {
private:
    Node* root;
    Node* empty(Node* n);
    Node* insert(int x, Node* n);
    Node* minNode(Node* n);
    Node* remove(int x, Node* n);
    void print(Node* n, int indent, bool left_tree, std::vector<int> road);
    int height(Node* n);
public:
    BST();
    ~BST();
    void insert(int k);
    void remove(int k);
    int height();
    void print();
};

#endif