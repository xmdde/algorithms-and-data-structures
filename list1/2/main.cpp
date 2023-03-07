#include <iostream>
#include <random>
#include <chrono>
using namespace std;

class Node {
public:
    double data;
    Node* next;

    Node(double data) {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList {
private:
    int size;
    Node* head;
public:
    LinkedList() {
        this->size = 0;
        this->head = nullptr;
    };

    void addNode(double val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* tmp = head;
            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = newNode;
        }
        size++;
    }

    void deleteNode(int pos) { //
    }

    double getData(int pos) {
        assert(pos < size);
        Node* node = head;
        while (pos > 0) {
            node = node->next;
            pos--;
        }
        return node->data;
    }

    void printList() {
        if (head == nullptr) {
            cout << "Empty list\n";
        }
        else {
            Node* tmp = head;
            while(tmp != nullptr) {
                cout << tmp->data << '\n';
                tmp = tmp->next;
            }
        }
    }
};

LinkedList* merge() { //?

}

int main() {
    LinkedList l = *new LinkedList();
    srand(time(nullptr));
    mt19937 mt{random_device{}()};
    uniform_real_distribution<double> dist(0, 1000);
    for (int i = 0; i < 100; i++) {
        l.addNode(dist(mt));
    }
    l.printList();
    return 0;
}
