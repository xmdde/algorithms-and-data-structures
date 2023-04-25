#include <iostream>
#include <random>

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        std::cerr << "wrong number of arguments";
        return 1;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    assert(n >= 0 && k >= 0 && k < n);
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());

    if (argc == 3) { //basic rand generator
        std::uniform_real_distribution<double> dist(0, 2*n-1);
        std::cout << n << ' ' << k << ' ';
        for (int i = 0; i < n; i++) {
            int x = floor(dist(mt));
            std::cout << x << ' ';
        }
    }
    else if (std::string(argv[3]) == "-a") { //ascending
        int i = 0;
        int cnt = 0;
        std::uniform_real_distribution<double> dist(0, 1);
        std::cout << n << ' ';
        std::cout << k << ' ';
        while (i <= 2 * n - 1 && cnt < n) {
            double pbb = (dist(mt));
            if (pbb < 0.65) {
                std::cout << i << ' ';
                cnt++;
            }
            i++;
        }
        if (cnt < n) {
            for (int j = 0; j < n - cnt; j++)
                std::cout << i - 1 << ' ';
        }
    }
    else if (std::string(argv[3]) == "-d") { //descending order
        int i = 2 * n - 1;
        int cnt = 0;
        std::uniform_real_distribution<double> dist(0, 1);
        std::cout << n << ' ';
        std::cout << k << ' ';
        while (i >= 0 && cnt < n) {
            double pbb = (dist(mt));
            if (pbb < 0.65) {
                std::cout << i << ' ';
                cnt++;
            }
            i--;
        }
        if (cnt < n) {
            for (int j = 0; j < n - cnt; j++)
                std::cout << i - 1 << ' ';
        }
    }
    return 0;
}