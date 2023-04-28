#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
bool sorted(int *arr, int size);
bool binarySearch(int *arr, int left, int right, const int k);
void printArr(int *arr, const int size);
void experiment1(int *arr, const int n);
void experiment2(int *arr, const int n);
int c = 0;

int main(int argc, char *argv[]) {
    if (argc == 1) {
        int n;
        std::cin >> n;
        int k;
        std::cin >> k;
        int keys[n];
        for (int i = 0; i < n; i++) {
            std::cin >> keys[i];
        }
        assert(sorted(keys, n));
        if (n <= 50) {
            std::cout << "initial state: \n";
            printArr(keys, n);
            auto begin = std::chrono::high_resolution_clock::now();
            std::cout << binarySearch(keys, 0, n-1, k);
            auto end = std::chrono::high_resolution_clock::now();
            auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            std::cout << "number of comparisons " << c << "\ntime: " << t.count();
        }
        else {
            bool ans = binarySearch(keys, 0, n-1, k);
            std::cout << "number of comparisons " << c << "\ntime: ";
        }
    }
    else if (std::string(argv[1]) == "-s") {
        int n;
        std::cin >> n;
        int k;
        std::cin >> k;
        int keys[n];
        for (int i = 0; i < n; i++) {
            std::cin >> keys[i];
        }
        experiment1(keys, n);
    }
    else if (std::string(argv[1]) == "-e") {
        int n;
        std::cin >> n;
        int k;
        std::cin >> k;
        int keys[n];
        for (int i = 0; i < n; i++) {
            std::cin >> keys[i];
        }
        experiment2(keys, n);
    }
    return 0;
}

bool binarySearch(int *arr, int left, int right, const int k) {
    if (left > right) 
        return false;
    c++;
    int mid = (left + right)/2;
    if (arr[mid] == k) {
        return true;
    }
    if (k < arr[mid]) {
        return binarySearch(arr, left, mid - 1, k);
    }
    else return binarySearch(arr, mid + 1, right, k);
}

bool sorted(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1])
            return false;
    }
    return true;
}

void printArr(int *arr, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}

void experiment1(int *arr, const int n) {
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/binsearch1.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        int var = rand() % 3;
        c = 0;
        auto begin = std::chrono::high_resolution_clock::now();
        bool ans = binarySearch(arr, 0, n-1, arr[var]);
        auto end = std::chrono::high_resolution_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        file << n << ";" << c << ";" << t.count() << ";";

        c = 0;
        begin = std::chrono::high_resolution_clock::now();
        ans = binarySearch(arr, 0, n-1, arr[n/2 + var]);
        end = std::chrono::high_resolution_clock::now();
        t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        file << c << ";" << t.count() << ";";

        c = 0;
        begin = std::chrono::high_resolution_clock::now();
        ans = binarySearch(arr, 0, n-1, arr[n - 1 - var]);
        end = std::chrono::high_resolution_clock::now();
        t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        file << c << ";" << t.count() << "\n";
    }
    file.close();
}

void experiment2(int *arr, const int n) {
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, n-1);
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/binsearch2.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        c = 0;
        int pos = floor(dist(mt));
        auto begin = std::chrono::high_resolution_clock::now();
        binarySearch(arr, 0, n-1, arr[pos]);
        auto end = std::chrono::high_resolution_clock::now();
        auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        file << n << ";" << c << ";" << t.count() << "\n";
    }
    file.close();
}