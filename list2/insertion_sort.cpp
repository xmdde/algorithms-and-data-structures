#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
using namespace std;
void insertionSort(int* keys, int n, bool show);
void experiment(int n, ofstream& file);
void printArr(int* keys, int n);
bool compare(int key1, int key2);

int c = 0; //number of comparisions
int s = 0; //number of swaps

int main(int argc, char *argv[]) {
    if (string(argv[1]) == "-s") { //statistic mode
        ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list2/insertionSortStat.txt");
        file << 'n' << ';' << 's' << ';' << 'c' << '\n';
        int n = 10;
        while (n <= 200) {
            for (int i = 0; i < 100; i++) {
                experiment(n, file);
            }
            n += 10;
        }
        file.close();
    }
    else {
        int n;
        cin >> n;
        int keys[n];
        for (int i = 0; i < n; i++) {
            cin >> keys[i];
        }
        if (n < 40) {
            insertionSort(keys, n, true);
        } else insertionSort(keys, n, false);
        cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
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
    insertionSort(arr, n, false);
    file << n << ';' << s << ';' << c << '\n';
}

void insertionSort(int* keys, int n, bool show) {
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
        if (show) {
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