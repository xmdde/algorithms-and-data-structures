#include <iostream>
#include <chrono>
#include <random>
using namespace std;
//destruktory!!

class Node {
private:
public:
    int data;
    Node* next;
    Node* prev;

    Node(int data) {
        this->data = data;
    }
};

class DoubleLinkedList {
private:
    int size;
public:
    Node* head;

    DoubleLinkedList() {
        this->size = 0;
        this->head = nullptr;
    }

    void pushBack(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        }
        else {
            Node* tmp = head;
            while (tmp->next != head) { //?
                tmp = tmp->next;
            }
            newNode->prev = tmp;
            newNode->next = head;
            tmp->next = newNode;
            head->prev = newNode;
        }
        size++;
    }

    int getData(int pos) {
        assert(pos < size || pos >= 0);
        Node* node = head;
        if (pos <= (size-1)/2) {
            while (pos > 0) {
                node = node->next;
                pos--;
            }
            return node->data;
        }
        else {
            int cnt = size - pos;
            while (cnt > 0) {
                node = node->prev;
                cnt--;
            }
            return node->data;
        }
    }

    void printList() {
        if (head == nullptr) {
            cout << "Empty list!\n";
        }
        else {
            Node* tmp = head;
            while (tmp->next != head) {
                cout << tmp->data << '\n'; //<< " prev: " << tmp->prev->data << " next: " << tmp->next->data << '\n';
                tmp = tmp->next;
            }
            cout << tmp->data << '\n'; //" prev: " << tmp->prev->data << " next: " << tmp->next->data << '\n';
        }
    }
};

int main() {
    DoubleLinkedList* l = new DoubleLinkedList;
    srand(time(nullptr));
    for (int i = 0; i < 10000; i++) {
        l->pushBack(rand() % 1000);
    }
    //l->printList();
    for (int i = 0; i < 4; i++) {
        cout << l->getData(i) << ' ';
    }
    return 0;
}
