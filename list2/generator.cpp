#include <iostream>
#include <random>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "wrong number of arguments!\n";
        return 1;
    }
    int n = atoi(argv[1]);
    srand(time(nullptr));
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0, 2*n-1);
    for (int i = 0; i < n; i++) {
        int x = floor(dist(mt));
        cout << x << ' ';
    }
    return 0;
}