#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long twoKnights(long long n) {
    if (n <= 1) return 0; // No valid configurations for n < 3

    long long totalWays = (n * n) * (n * n - 1LL) / 2LL; // Total ways to place two knights
    long long attackWays = (long long)(n - 1) * (n - 2) * 4LL; // Ways where knights attack each other

    return totalWays - attackWays;
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cout << twoKnights((long long)i) << endl;
    }

    return 0;
}