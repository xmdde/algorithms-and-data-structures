#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
using namespace std;
void printArr(int* keys, int n);
void experiment(int n, ofstream& file);
int partition(int* arr, int low, int high);
void quickSort(int* arr, int low, int high, int size, bool show);
int c = 0; //number of comparisions
int s = 0; //number of swaps

int main(int argc, char *argv[]) {
    if (argc == 1) {
        int n;
        cin >> n;
        int keys[n];
        for (int i = 0; i < n; i++) {
            cin >> keys[i];
        }
        if (n < 40) {
            quickSort(keys, 0, n - 1, n, true);
        } else quickSort(keys, 0, n - 1, n, false);
        cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
    }
    else if (string(argv[1]) == "-s") { //statistic mode
        /*ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list2/quickSortStat.txt");
        file << 'n' << ';' << 's' << ';' << 'c' << '\n';
        int n = 10;
        while (n <= 200) {
            for (int i = 0; i < 100; i++) {
                experiment(n, file);
            }
            n += 10;
        }
        file.close(); */
        ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list2/quickSort2.txt");
        file << 'n' << ';' << 's' << ';' << 'c' << '\n';
        int n = 1000;
        while (n <= 20000) {
            for (int i = 0; i < 100; i++) {
                experiment(n, file);
            }
            n += 1000;
        }
        file.close();
    }
    return 0;
}

void experiment(int n, ofstream& file) {
    srand(time(nullptr));
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0, 2*n-1);
    int arr[n];
    c = 0;
    s = 0;
    for (int i = 0; i < n; i++) {
        int x = floor(dist(mt));
        arr[i] = x;
    }
    quickSort(arr, 0, n-1, n, false);
    file << n << ';' << s << ';' << c << '\n';
}

void quickSort(int* arr, int low, int high, int size, bool show) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        if (show) {
            printArr(arr, size);
        }
        quickSort(arr, low, pivot - 1, size, show) ;
        quickSort(arr, pivot + 1, high, size, show) ;
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