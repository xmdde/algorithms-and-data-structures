#include <iostream>
#include <vector>
#include <fstream>
#include "RedBlackTree.h"
using namespace std;

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
    node->color = 1;

    Node* y = nullptr;
    Node* x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->key < x->key) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->key < y->key) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }
    insertFix(node);
}

void RedBlackTree::insertFix(Node* k) {
    Node* u;
    while (k->parent->color == 'R') {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 'R') {
          u->color = 'B';
          k->parent->color = 'B';
          k->parent->parent->color = 'R';
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 'B';
          k->parent->parent->color = 'R';
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 'R') {
          u->color = 'B';
          k->parent->color = 'B';
          k->parent->parent->color = 'R';
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
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
        }

        if (s->left->color == 'B' && s->right->color == 'B') {
          s->color = 'R';
          x = x->parent;
        } else {
          if (s->right->color == 'B') {
            s->left->color = 'B';
            s->color = 'R';
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 'B';
          s->right->color = 'B';
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 'R') {
          s->color = 'B';
          x->parent->color = 'R';
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 'B' && s->right->color == 'B') {
          s->color = 'R';
          x = x->parent;
        } else {
          if (s->left->color == 'B') {
            s->right->color = 'B';
            s->color = 'R';
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 'B';
          s->left->color = 'B';
          rightRotate(x->parent);
          x = root;
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
        z = node;
      }

      if (node->key <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }
    if (z == TNULL) {
      return;
    }

    y = z;
    char y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
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
    if (x->right != TNULL) {
      return minimum(x->right);
    }
    Node* y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
}

Node* RedBlackTree::predecessor(Node* x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }
    Node* y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }
    return y;
}

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

void RedBlackTree::rbTransplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
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
      return node;
    }
    if (key < node->key) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

Node* RedBlackTree::minimum(Node* node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
}

Node* RedBlackTree::maximum(Node* node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
}

void RedBlackTree::print() {
    std::vector<int> road;
    print(root, 0, false, road);
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

int main() {
  RedBlackTree bst;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);
  bst.print();
  bst.deleteNode(40);
  bst.deleteNode(11);
  bst.print();
}