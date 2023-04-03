#include <iostream>
#include <time.h>
using namespace std;
void insertionSort(int* keys, int n);
void printArr(int* keys, int n);
bool compare(int key1, int key2);
int c = 0; //number of comparisions
int s = 0; //number of swaps

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    int keys[n];
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    if (n < 40) {
        printArr(keys, n);
    }
    insertionSort(keys, n);
    cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
    return 0;
}

void insertionSort(int* keys, int n) {
    int key;
    for (int i = 1; i < n; i++) {
        key = keys[i];
        int j = i - 1;
        while (j >= 0 && compare(keys[j],key)) {
            keys[j + 1] = keys[j];
            j--;
            s++;
        }
        keys[j + 1] = key;
        if (j + 1 != i) {
            s++;
        }
        if (n < 40) {
            printArr(keys, n);
        }
    }
}

bool compare(int key1, int key2) {
    c++;
    if (key1 > key2)
        return true;
    return false;
}

void printArr(int* keys, int n) {
    for (int i = 0; i < n; i++)
        cout << keys[i] << ' ';

    cout << '\n';
}