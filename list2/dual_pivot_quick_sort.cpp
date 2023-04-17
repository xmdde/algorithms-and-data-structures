#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
using namespace std;
void printArr(int* keys, int n);
void dualPivotQuickSort(int* arr, int low, int high, int size, bool show);
void experiment(int n, ofstream& file);
pair<int,int> dualPartition(int* arr, int low, int high);
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
            dualPivotQuickSort(keys, 0, n-1, n, true);
        } else dualPivotQuickSort(keys, 0, n-1, n, false);
        cout << "Number of comparisions: " << c << "\nNumber of keys swaps: " << s << '\n';
    } 
    else if (string(argv[1]) == "-s") {
        ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list2/dualpivotquickSortStat.txt");
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
    dualPivotQuickSort(arr, 0, n-1, n, false);
    file << n << ';' << s << ';' << c << '\n';
}

void dualPivotQuickSort(int* arr, int low, int high, int size, bool show) {
    if (low < high) {
        std::pair<int,int> p = dualPartition(arr, low, high);
        if (show) {
            printArr(arr, size);
        }
        dualPivotQuickSort(arr, low, p.first - 1, size, show);
        dualPivotQuickSort(arr, p.first + 1, p.second - 1, size, show);
        dualPivotQuickSort(arr, p.second + 1, high, size, show);
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
