#include <iostream>
#include <fstream>
#include <vector>
#include "BST.h"

void printGap(int indent, std::vector<int> road);
void presentation(const int n, int *toInsert, int *toDelete);
void experiment(const int n, int *toInsert, int *toDelete);
int comps = 0;
int readAndReplacements = 0;

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    root = empty(root);
}

Node* BST::empty(Node* n) {
    readAndReplacements++;
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
    readAndReplacements++;
    if (n == nullptr) { 
        n = new Node;
        n->data = x;
        n->left = nullptr;
        n->right = nullptr;
    }
    else if (x < n->data) {
        comps++;
        n->left = insert(x, n->left);
    }
    else if(x > n->data) {
        comps+=2;
        n->right = insert(x, n->right);
    }
    return n;
} 

void BST::remove(int k) {
    root = remove(k, root);
}

Node* BST::remove(int x, Node* n) {
    Node* tmp;
    readAndReplacements++;

    if (n == nullptr)
        return nullptr;
    else if (x < n->data) {
        comps++;
        n->left = remove(x, n->left);
    }
    else if (x > n->data) {
        comps += 2;
        n->right = remove(x, n->right);
    }
    else if (n->left && n->right) {
        comps += 4;
        tmp = minNode(n->right);
        n->data = tmp->data;
        n->right = remove(n->data, n->right);
    }
    else {
        comps += 4;
        readAndReplacements += 2;
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
        readAndReplacements++;
        return nullptr;
    }
    else if (n->left == nullptr) {
        readAndReplacements+=2;
        return n;
    }
    else {
        readAndReplacements+=2;
        return minNode(n->left);
    }
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
    BST bst;
    for (int i = 0; i < n; i++) {
        std::cout << "insert " << toInsert[i] << '\n';
        bst.insert(toInsert[i]);
        bst.print();
    }
    for (int i = 0; i < n; i++) {
        std::cout << "delete " << toDelete[i] << '\n';
        bst.remove(toDelete[i]);
        bst.print();
    }
}

void experiment(const int n, int *toInsert, int *toDelete) {
    int maxheight = 0;
    int maxcomps = 0;
    int maxrr = 0;
    long long sumheight = 0;
    long long sumcomps = 0;
    long long sumrr = 0;
    BST bst;
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list4/bstStats.txt", std::ios::app);

    for (int i = 0; i < n; i++) {
        readAndReplacements = 0;
        comps = 0;
        bst.insert(toInsert[i]);
        int h = bst.height();

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

    std::ofstream file2("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list4/bstDeleteStats.txt", std::ios::app);
    for (int i = 0; i < n; i++) {
        readAndReplacements = 0;
        comps = 0;
        bst.remove(toDelete[i]);
        int h = bst.height();

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