#include <iostream>
#include <fstream>
#include <string>
#include <random>
void printArr(int *arr, const int size);
int partition5(int *arr, int left, int right);
int selectPartition(int *arr, int left, int right, int pivotIndex, int n);
int select(int *arr, int left, int right, int n);
int pivot(int *arr, int left, int right);
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
            std::cout << "position " << k << "\n";
            std::cout << "found " << keys[select(keys, 0, n-1, k)] << "\n";
            printArr(keys, n);
        }
        else {
            //std::cout <<;
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
        //experiment(keys, n);
    }
    return 0;
}

int select(int *arr, int left, int right, int n) { //int size??
    while (true) {
        if (left == right)
            return left;
        int pivotIndex = pivot(arr, left, right);
        pivotIndex = selectPartition(arr, left, right, pivotIndex, n);
        if (n == pivotIndex)
            return n;
        if (n < pivotIndex)
            right = pivotIndex - 1;
        else left = pivotIndex + 1;
    }
}

int selectPartition(int *arr, int left, int right, int pivotIndex, int n) {
    int pivot = arr[pivotIndex];
    mySwap(arr, pivotIndex, right);
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {
            mySwap(arr, storeIndex, i);
            storeIndex++;
        }
        c++;
    }
    int storeIndexEq = storeIndex;
    for (int i = storeIndex; i < right; i++) {
        if (arr[i] == pivot) {
            mySwap(arr, storeIndexEq, i);
            storeIndexEq++;
        }
        c++;
    }
    mySwap(arr, right, storeIndexEq);
    if (n < storeIndex)
        return storeIndex;
    else if (n <= storeIndexEq)
        return n;
    return storeIndexEq;
}

int partition5(int *arr, int left, int right) {
    int i = left + 1;
    int j;
    while (i <= right) {
        j = i;
        while (j > left && arr[j-1] && arr[j]) {
            mySwap(arr, j-1, j);
            j--;
            c++;
        }
        c++;
        i++;
    }
    return (left + right)/2;
}

int pivot(int *arr, int left, int right) {
    if (right - left < 5)
        return partition5(arr, left, right);
    for (int i = left; i < right; i += 5) {
        int subRight = i + 4;
        if (subRight > right) {
            subRight = right;
        }
        int median5 = partition5(arr, i, subRight);
        mySwap(arr, median5, left + (i-left)/5);
    }
    int mid = (right - left)/10 + left + 1;
    return select(arr, left, left + (right-left)/5, mid);
}

void printArr(int *arr, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n";
}

void mySwap(int *arr, const int i1, const int i2) {
    int tmp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = tmp;
    s++;
}

void experiment(int *arr, const int n) {
    std::ofstream file1("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/selectStat1.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        s = 0;
        c = 0;
        select(arr, 0, n-1, 3);
        file1 << n << ";" << s << ";" << c << "\n";
    }
    file1.close();

    std::ofstream file2("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/selectStat2.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        s = 0;
        c = 0;
        select(arr, 0, n-1, n/2);
        file2 << n << ";" << s << ";" << c << "\n";
    }
    file2.close();
    
    std::ofstream file3("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list3/selectStat3.txt", std::ios::app);
    for (int i = 0; i < 100; i++) {
        s = 0;
        c = 0;
        select(arr, 0, n-1, n-1);
        file3 << n << ";" << s << ";" << c << "\n";
    }
    file3.close();
}