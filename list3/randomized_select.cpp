#include <iostream>
#include <fstream>
#include <string>
#include <random>
void printArr(int *arr, const int size);
int randomizedPartition(int *arr, int left, int right);
int randomizedSelect(int *arr, int left, int right, int n, const int size);
void mySwap(int *arr, const int i1, const int i2);
void experiment(int *arr, const int n);
int s = 0;
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
        if (n <= 50) {
            std::cout << "initial state: \n";
            printArr(keys, n);
            std::cout << "found " << randomizedSelect(keys, 0, n-1, k+1, n) << "\n";
            printArr(keys, n);
        }
        else {
            std::cout << randomizedSelect(keys, 0, n-1, k+1, n);
        }
        std::cout << "number of swaps: " << s << "\nnumber of comparitions: " << c << "\n";
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
        experiment(keys, n);
    }
    return 0;
}

void experiment(int *arr, const int n) {
    std::ofstream file1("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/randStat1.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        s = 0;
        c = 0;
        randomizedSelect(arr, 0, n-1, 3, n);
        file1 << n << ";" << s << ";" << c << "\n";
    }
    file1.close();

    std::ofstream file2("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/randStat2.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        s = 0;
        c = 0;
        randomizedSelect(arr, 0, n-1, n/2, n);
        file2 << n << ";" << s << ";" << c << "\n";
    }
    file2.close();
    
    std::ofstream file3("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/randStat3.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        s = 0;
        c = 0;
        randomizedSelect(arr, 0, n-1, n-1, n);
        file3 << n << ";" << s << ";" << c << "\n";
    }
    file3.close();
}

void printArr(int *arr, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}

int randomizedPartition(int *arr, int left, int right) {
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(left, right);
    int pivotIndex = left;
    if (left < right) {
        pivotIndex = floor(dist(mt));
    }
    c++;
    mySwap(arr, pivotIndex, right);
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= arr[right]) {
            mySwap(arr, i, j);
            i++;
        }
        c++;
    }
    mySwap(arr, i, right);
    return i;
}

int randomizedSelect(int *arr, int left, int right, int n, const int size) {
    if (left == right) {
        return arr[left];
    }
    c++;
    int pivotIndex = randomizedPartition(arr, left, right);
    int k = pivotIndex - left + 1;
    if (n == k) {
        return arr[pivotIndex];
    }
    else if (n < k) {
        return randomizedSelect(arr, left, pivotIndex - 1, n, size);
    }
    else return randomizedSelect(arr, pivotIndex + 1, right, n - k, size);
    c++;
    //printArr(arr, size)
}

void mySwap(int *arr, const int i1, const int i2) {
    int tmp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = tmp;
    s++;
}