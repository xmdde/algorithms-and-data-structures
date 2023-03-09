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
public:
    Node* head;

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

    void merge(LinkedList* list2) {
        if (head == nullptr) {
            head = list2->head;
        }
        else {
            Node* tmp = head;
            while (tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = list2->head;
        }
    }

    ~LinkedList() {
        Node* tmp = head;
        while (tmp != nullptr) {
            Node* next = tmp->next;
            delete tmp;
            tmp = next;
        }
        delete head;
    }
};

void timeMeasurement(LinkedList* list) {
    cout << "Elapsed time accessing the same element: \n";
    double tmp;
    for (int i = 0; i < 100; i++) {
        auto begin = chrono::high_resolution_clock::now();
        tmp = list->getData(7);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << i + 1 << ": " << elapsed.count() << " ns \n";
    }
}

void randomTimeMeasurement(LinkedList* list) {
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
    LinkedList* l = new LinkedList();
    srand(time(nullptr));
    mt19937 mt{random_device{}()};
    uniform_real_distribution<double> dist(0, 1000);

    for (int i = 0; i < 10000; i++) {
        l->addNode(dist(mt));
    }
    timeMeasurement(l);
    cout << '\n';
    randomTimeMeasurement(l);
    return 0;
}
