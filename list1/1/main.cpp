#include <iostream>
using namespace std;
#define MAX_SIZE 1000

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

    void help() { //move to tests
        cout << "front: " << front << " rear: " << rear << '\n';
    }
};

class Stack {
private:
    int* arr;
    int top;
    int size;
public:
    Stack() {
        this->top = 0;
        this->size = MAX_SIZE;
        this->arr = new int[size];
    }

    void addElement(int val) {
        if (top == size) {
            cout << "Stack overflow! ;D\n";
        }
        else {
            arr[top] = val;
            top++;
        }
    }

    int pop() {
        if (top == 0) {
            cerr << "pop: Empty stack\n";
            exit(EXIT_FAILURE);
        }
        else {
            top--;
            return arr[top];
        }
    }

    ~Stack() {
        delete [] arr;
    }
};

int main() {
    srand(time(nullptr));
    Queue* q = new Queue;
    Stack* s = new Stack;
    cout << "Adding 100 elements to the queue.\n";
    int element;
    for (int i = 0; i < 100; i++) {
        element = rand()%1000;
        cout << element << "\n";
        q->enqueue(element);
    }
    cout << "Dequeuing: \n";
    for (int i = 0; i < 100; i++) {
        cout << q->dequeue() << '\n';
    }

    cout << "\nAdding 100 elements to the stack.\n";
    for (int i = 0; i < 100; i++) {
        element = rand()%1000;
        cout << element << "\n";
        s->addElement(element);
    }
    cout << "Taking elements from the stack: \n";
    for (int i = 0; i < 100; i++) {
        cout << s->pop() << '\n';
    }
    return 0;
}
