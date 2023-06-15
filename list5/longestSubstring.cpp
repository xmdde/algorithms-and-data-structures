#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
std::string getRandString(const int len);
short LCSubstring(std::string& a, std::string& b);
void stats();
long long comps = 0;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "wrong number of arguments";
        return 1;
    }
    if (std::string(argv[1]) == "-s") {
        stats();
    }
    else {
        const int n = atoi(argv[1]);
        std::string a = getRandString(n);
        std::string b = getRandString(n);
        std::string c = "abaabbaaa";
        std::string d = "babab";
        //std::cout << a << '\n' << b;
        //std::cout << "\nLCS length: " << LCSubstring(a,b);
        std::cout << "\nLCS length: " << LCSubstring(d,c);
    }
    return 0;
}

short LCSubstring(std::string& a, std::string& b) {
    const int n = a.length();
    const int m = b.length();
    std::vector<short> dp[n+1];
    for (int i = 0; i < n; i++)
        dp[i] = std::vector<short>(m+1, 0);
    short mx = 0;
    std::string ans = "";

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            comps++;
            if (a[i-1] == b[j-1]) {
                dp[i][j] = 1 + dp[i-1][j-1];
                if (dp[i][j] > mx) {
                    mx = dp[i][j];
                }
                comps++;
            }
            else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    std::cout << "\ndp:\n    ";
    for (auto i : b) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " | ";
        for (int j = 0; j < m; j++) {
            std::cout << dp[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << ans;
    return mx;
}

void stats() {
    const int T = 100;
    std::ofstream file("/Users/justynaziemichod/Documents/SEM4/algorithms-and-data-structures/list5/LCSstats.txt", std::ios::app);
    file << "n;avg_comps\n";
    for (int n = 1000; n <= 5000; n += 1000) {
        comps = 0;
        for (int i = 0; i < T; i++) {
            std::string a = getRandString(n);
            std::string b = getRandString(n);
            int tmp = LCSubstring(a,b);
        }
        file << n << ';' << comps/T << '\n';
    }
}

std::string getRandString(const int len) {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string s = "";
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, alphabet.size());
    for (int i = 0; i < len; i++)
        s += alphabet[floor(dist(mt))];
    return s;
}