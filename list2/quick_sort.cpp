#include <iostream>
#include <time.h>
using namespace std;
void printArr(int* keys, int n);
int partition(int* arr, int low, int high);
void quickSort(int* arr, int low, int high, int size);
int c = 0; //number of comparisions
int s = 0; //number of swaps

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    int keys[n];
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    quickSort(keys, 0, n - 1, n);
    cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
}

void quickSort(int* arr, int low, int high, int size) {
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        if (size < 40) {
            printArr(arr, size);
        }
        quickSort(arr, low, pivot - 1, size) ;
        quickSort(arr, pivot + 1, high, size) ;
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i;
    int j;
    i = low;
    j = low;

    for (int i = low; i < high; i++) {
        if(arr[i] < pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j += 1;
            s++;
        }
        c++;
    }

    int temp = arr[j];
    arr[j] = arr[high];
    arr[high] = temp;
    s++;

    return j;
}

void printArr(int* keys, int n) {
    for (int i = 0; i < n; i++)
        cout << keys[i] << ' ';

    cout << '\n';
}