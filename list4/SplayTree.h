#include <iostream>
#include <vector>
int comps = 0;
int readAndReplacements = 0;

struct Node {
	int data;
	Node* parent;
	Node* left;
	Node* right;
};

class SplayTree {
private:
	Node* root;
	void deleteNode(Node* node, int key);
	void leftRotate(Node* x);
	void rightRotate(Node* x);
	void splay(Node* x);
	Node* join(Node* s, Node* t);
    int height(Node* root);
	void split(Node* &x, Node* &s, Node* &t);
    void print(Node* root, int indent, bool left_tree, std::vector<int> road);
    void printGap(int indent, std::vector<int> road);
public:
	SplayTree();
    //~SplayTree();
    Node* getRoot();
	Node* maximum(Node* node);
	void insert(int key);
	void deleteNode(int data);
    int height();
    void print();
};