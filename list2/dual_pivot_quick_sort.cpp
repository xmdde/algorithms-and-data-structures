#include <iostream>
#include <time.h>
using namespace std;
void printArr(int* keys, int n);
void dualPivotQuickSort(int* arr, int low, int high, int size);
pair<int,int> dualPartition(int* arr, int low, int high);
int c = 0; //number of comparisions
int s = 0; //number of swaps

int main(int argc, char *argv[]) {
    int n;
    cin >> n;
    int keys[n];
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    dualPivotQuickSort(keys, 0, n-1, n);
    cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
}

void dualPivotQuickSort(int* arr, int low, int high, int size) {
    if (low < high) {
        std::pair<int,int> p = dualPartition(arr, low, high);
        if (size < 40) {
            printArr(arr, size);
        }
        dualPivotQuickSort(arr, low, p.first - 1, size);
        dualPivotQuickSort(arr, p.first + 1, p.second - 1, size);
        dualPivotQuickSort(arr, p.second + 1, high, size);
    }
}

pair<int,int> dualPartition(int* arr, int low, int high) {
    if (arr[low] > arr[high]) {
        swap(arr[low], arr[high]);
        s++;
    }
    c++;

    int j = low + 1;
    int g = high - 1;
    int k = low + 1;
    int p = arr[low];
    int q = arr[high];
    s++;

    while (k <= g) {

        if (arr[k] < p) {
            swap(arr[k], arr[j]);
            s++;
            j++;
        }
        else if (arr[k] >= q) {
            while (arr[g] > q && k < g) {
                g--;
                c++;
            }
            c++;
            swap(arr[k], arr[g]);
            s++;
            g--;
            if (arr[k] < p) {
                swap(arr[k], arr[j]);
                s++;
                j++;
            }
            c++;
        }
        c++;
        k++;
    }
    j--;
    g++;

    swap(arr[low], arr[j]);
    swap(arr[high], arr[g]);
    s++;

    return std::pair<int,int>(j,g);
}

void printArr(int* keys, int n) {
    for (int i = 0; i < n; i++)
        cout << keys[i] << ' ';
    cout << '\n';
}
