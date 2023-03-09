#include <iostream>
#include <chrono>
#include <random>
using namespace std;

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
            while (tmp->next != head) {
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

    void merge(DoubleLinkedList* list) {
    }

    ~DoubleLinkedList() {
        Node* tmp = head;
        while (tmp != nullptr) {
            Node* next = tmp->next;
            delete tmp;
            tmp = next;
        }
        delete head;
    }
};

void timeMeasurement(DoubleLinkedList* list) {
    cout << "Elapsed time accessing element no. 7: \n";
    double tmp;
    for (int i = 0; i < 100; i++) {
        auto begin = chrono::high_resolution_clock::now();
        tmp = list->getData(7);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << i + 1 << ": " << elapsed.count() << " ns \n";
    }
    cout << "Elapsed time accessing element no. 5000: \n";
    for (int i = 0; i < 100; i++) {
        auto begin = chrono::high_resolution_clock::now();
        tmp = list->getData(5000);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << i + 1 << ": " << elapsed.count() << " ns \n";
    }
    cout << "Elapsed time accessing element no. 9000: \n";
    for (int i = 0; i < 100; i++) {
        auto begin = chrono::high_resolution_clock::now();
        tmp = list->getData(9000);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << i + 1 << ": " << elapsed.count() << " ns \n";
    }
}

void randomTimeMeasurement(DoubleLinkedList* list) {
    cout << "Elapsed time accessing random elements: \n";
    srand(time(nullptr));
    double tmp;
    int pos;
    for (int i = 0; i < 100; i++) {
        pos = rand() % 10000;
        auto begin = chrono::high_resolution_clock::now();
        tmp = list->getData(pos);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << i + 1 << ": " << elapsed.count() << " ns \n";
    }
}

int main() {
    DoubleLinkedList* l = new DoubleLinkedList;
    srand(time(nullptr));
    for (int i = 0; i < 10000; i++) {
        l->pushBack(rand() % 1000);
    }
    timeMeasurement(l);
    cout << '\n';
    randomTimeMeasurement(l);
    return 0;
}
