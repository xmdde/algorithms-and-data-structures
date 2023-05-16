#include <iostream>
#include <vector>
void printGap(int indent, std::vector<int> road);
void presentation(const int n, int *toInsert, int *toDelete);

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

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    root = empty(root);
}

Node* BST::empty(Node* n) {
    if (n == nullptr)
        return nullptr;
    empty(n->left);
    empty(n->right);
    delete n;
    return nullptr;
}

void BST::insert(int k) {
    root = insert(k, root);
}

Node* BST::insert(int x, Node* n) {
    if (n == nullptr) { //
        n = new Node;
        n->data = x;
        n->left = nullptr;
        n->right = nullptr;
    }
    else if (x < n->data) {
        n->left = insert(x, n->left);
    }
    else if(x > n->data) {
        n->right = insert(x, n->right);
    }
    return n;
} 

void BST::remove(int k) {
    root = remove(k, root);
}

Node* BST::remove(int x, Node* n) {
    Node* tmp;
    if (n == nullptr)
        return nullptr;
    else if (x < n->data) {
        n->left = remove(x, n->left);
    }
    else if (x > n->data) {
        n->right = remove(x, n->right);
    }
    else if (n->left && n->right) {
        tmp = minNode(n->right);
        n->data = tmp->data;
        n->right = remove(n->data, n->right);
    }
    else {
        tmp = n;
        if(n->left == nullptr)
            n = n->right;
        else if(n->right == nullptr)
            n = n->left;
        delete tmp;
    }
    return n;
}

Node* BST::minNode(Node* n) {
    if (n == nullptr) {
        return nullptr;
    }
    else if (n->left == nullptr) {
        return n;
    }
    else return minNode(n->left);
}

void BST::print() {
    std::vector<int> road;
    print(root, 0, false, road);
    std::cout << '\n';
}

void BST::print(Node* n, int indent, bool left_tree, std::vector<int> road) {
    if(n != NULL){
        if (n->left != NULL){
            std::vector<int> left_road = road;
            left_road.push_back(-1);
            print(n->left, indent+1, true, left_road);
        }
        printGap(indent, road);
        if (left_tree)
            std::cout << "/";
        if (!left_tree && indent != 0)
            std::cout << "\\";
        std::cout << "-[" << n->data << "]" << std::endl;
        if (n->right != NULL){
            std::vector<int> right_road = road;
            right_road.push_back(1);
            print(n->right, indent+1, false, right_road);
        }
    }
}

void printGap(int indent, std::vector<int> road) {
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

int BST::height(){
    return height(root);
}

int BST::height(Node* n){
    if (n == nullptr)
        return 0;
    else if (n->left == nullptr && n->right == nullptr)
        return 1;
    else if (n->right == nullptr) 
        return height(n->left) + 1;
    else if (n->left == nullptr)
        return height(n->right) + 1;
    else return std::max(height(n->left), height(n->right)) + 1;
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
    }
    return 0;
}

void presentation(const int n, int *toInsert, int *toDelete) {
    BST bst;
    for (int i = 0; i < n; i++) {
        bst.insert(toInsert[i]);
        bst.print();
    }
}