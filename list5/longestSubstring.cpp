#include <iostream>
#include <string>
#include <random>
#include <time.h>
int LCSubstring(std::string& a, std::string& b);

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "wrong number of arguments";
        return 1;
    }
    const int n = atoi(argv[1]);
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string a = "";
    std::string b = "";
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, alphabet.size());
    for (int i = 0; i < n; i++) {
        a += alphabet[floor(dist(mt))];
        b += alphabet[floor(dist(mt))];
    }
    std::cout << a << '\n' << b;
    std::cout << "\nLCS length: " << LCSubstring(a,b);
    return 0;
}

int LCSubstring(std::string& a, std::string& b) {
    const int n = a.length();
    const int m = b.length();
    int dp[n][m];
    int mx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (a[i] == b[j]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                if (dp[i][j] > mx) 
                    mx = dp[i][j];
            }
            else dp[i][j] = 0;
        }
    }
    return mx;
}