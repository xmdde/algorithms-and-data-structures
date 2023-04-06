#include <iostream>
#include <time.h>
using namespace std;
void printArr(int* keys, int n);
void merge(int* arr, int l, int m, int r);
void mergeSort(int* arr, int l, int r, int size);

int c = 0; //number of comparisions
int s = 0; //number of swaps

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    int keys[n];
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    mergeSort(keys, 0, n - 1, n);
    cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
}

void merge(int* arr, int l, int m, int r) {

    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
        s++;
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
        s++;
    }

    int i = 0, j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            c++;
            arr[k] = L[i];
            s++;
            i++;
        }
        else {
            c++;
            arr[k] = R[j];
            s++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        s++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        s++;
        j++;
        k++;
    }
}

void mergeSort(int* arr, int l, int r, int size) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, size);
        mergeSort(arr, m + 1, r, size);
        merge(arr, l, m, r);
        if (size < 40)
            printArr(arr, size);
    }
}

void printArr(int* keys, int n) {
    for (int i = 0; i < n; i++)
        cout << keys[i] << ' ';

    cout << '\n';
}