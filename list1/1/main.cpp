#include <iostream>
using namespace std;
#define MAX_SIZE 5

class Queue {
private:
    int *arr;
    int front;
    int rear;
    int size;

public:
    Queue() {
        this->size = MAX_SIZE;
        this->arr = new int[size];
        this->front = 0;
        this->rear = 0;
    }

    void enqueue(int element) {
        if (rear == size - 1) {
            cerr << "Queue is full!\n";
        }
        else {
            arr[rear] = element;
            rear = (rear + 1) % size;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            cerr << "dequeue: Queue is empty!\n";
            exit(EXIT_FAILURE); // exc?
        }
        else {
            int result = arr[front];
            front = (front + 1) % size;
            return result;
        }
    }

    bool isEmpty() {
        return front == rear;
    }

    ~Queue() {
        delete [] arr;
    }

    void help() {
        cout << "front: " << front << " rear: " << rear << '\n';
    }
};

class Stack {

};

int main() {
    Queue q;

    return 0;
}
