#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
using namespace std;

void printArr(int* keys, int n);
void experiment(int n, ofstream& file);
void merge(int* arr, int l, int m, int r);
void mergeSort(int* arr, int l, int r, int size, bool show);

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
            mergeSort(keys, 0, n - 1, n, true);
        } else mergeSort(keys, 0, n - 1, n, false);
        cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
    }
    else if (string(argv[1]) == "-s") { //statistic mode
        ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list2/mergeSortStat.txt");
        file << "n;s;c\n";
        int n = 10;
        while (n <= 200) {
            for (int i = 0; i < 100; i++) {
                experiment(n, file);
            }
            n += 10;
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
    mergeSort(arr, 0, n-1, n, false);
    file << n << ';' << s << ';' << c << '\n';
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

void mergeSort(int* arr, int l, int r, int size, bool show) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, size, show);
        mergeSort(arr, m + 1, r, size, show);
        merge(arr, l, m, r);
        if (show)
            printArr(arr, size);
    }
}

void printArr(int* keys, int n) {
    for (int i = 0; i < n; i++)
        cout << keys[i] << ' ';

    cout << '\n';
}