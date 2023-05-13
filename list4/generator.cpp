#include <iostream>
#include <random>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "wrong number of arguments";
        return 1;
    }
    int n = atoi(argv[1]);
    assert(n >= 0);
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 2*n-1);
    
    int arr[2*n];
    for (int i = 0; i < 2*n; i++)
        arr[i] = i;

    if (argc == 2) { //basic unique numbers rand generator
        std::cout << n << ' ';
        //nodes to insert
        for (int i = 0; i < n; i++) {
            bool inserted = false;
            while (!inserted) {
                int x = floor(dist(mt));
                if (arr[x] != -1) {
                    std::cout << arr[x] << ' ';
                    arr[x] = -1;
                    inserted = true;
                }
            }
        }
        //nodes to delete
        for (int i = 0; i < n; i++) {
            int x = floor(dist(mt));
            std::cout << x << ' ';
        }
    }

    else if (std::string(argv[2]) == "-a") { //ascending
        std::cout << n << ' ';
        int seq[n];
        for (int i = 0; i < n; i++) {
            bool inserted = false;
            while (!inserted) {
                int x = floor(dist(mt));
                if (arr[x] != -1) {
                    seq[i] = arr[x];
                    arr[x] = -1;
                    inserted = true;
                }
            }
        }
        std::sort(seq, seq + n);
        for (int i = 0; i < n; i++)
            std::cout << seq[i] << ' ';
        
        //nodes to delete
        for (int i = 0; i < n; i++) {
            int x = floor(dist(mt));
            std::cout << x << ' ';
        }
    }
    return 0;
}