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
        if (head == nullptr) {
            head = list->head;
        }
        else {
            Node* tmp = head;
            while (tmp->next != head) {
                tmp = tmp->next;
            }
            tmp->next = list->head;
            list->head->prev = tmp;
            tmp = list->head;
            while(tmp->next != list->head) {
                tmp = tmp->next;
            }
            tmp->next = head;
            head->prev = tmp;
        }
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
    cout << '\n';
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
    cout << '\n';
}

void mergeTest() {
    DoubleLinkedList* miniList1 = new DoubleLinkedList;
    DoubleLinkedList* miniList2 = new DoubleLinkedList;
    for (int i = 0; i < 5; i++) {
        miniList1->pushBack(rand() % 100);
        miniList2->pushBack(rand() % 100);
    }
    cout << "Testing merge function:\nList 1:\n";
    miniList1->printList();
    cout << "List 2:\n";
    miniList2->printList();
    miniList1->merge(miniList2);
    cout << "List 1 after merging:\n";
    miniList1->printList();
}

int main() {
    DoubleLinkedList* l = new DoubleLinkedList;
    srand(time(nullptr));
    for (int i = 0; i < 10000; i++) {
        l->pushBack(rand() % 1000);
    }
    cout << "Added 10000 elements to the list.\n";
    timeMeasurement(l);
    randomTimeMeasurement(l);
    mergeTest();
    return 0;
}
