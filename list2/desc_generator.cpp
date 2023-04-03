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
    int i = 2 * n - 1;
    int cnt = 0;

    srand(time(nullptr));
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(0, 1);
    cout << n << ' ';
    
    while (i >= 0 && cnt < n) {
        double pbb = (dist(mt));
        if (pbb < 0.6) {
            cout << i << ' ';
            cnt++;
        }
        i--;
    }
    if (cnt < n) {
        for (int j = 0; j < n - cnt; j++)
            cout << i - 1 << ' ';
    }
    return 0;
}