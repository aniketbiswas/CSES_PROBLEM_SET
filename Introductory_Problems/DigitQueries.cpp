// NOT SUBMITTED

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;
/*
Consider an infinite string that consists of all positive integers in increasing order:
12345678910111213141516171819202122232425...
Your task is to process q queries of the form: what is the digit at position k in the string?
Input
The first input line has an integer q: the number of queries.
After this, there are q lines that describe the queries. Each line has an integer k: a 1-indexed position in the string.
Output
For each query, print the corresponding digit.
Constraints

1 \le q \le 1000
1 \le k \le 10^{18}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    // Precompute powers of 10 up to 10^18
    vector<unsigned long long> pow10(19, 1ULL);
    for (int i = 1; i <= 18; ++i) pow10[i] = pow10[i - 1] * 10ULL;

    while (q--) {
        unsigned long long k; // up to 1e18
        cin >> k;

        // Find the digit length group containing position k
        int d = 1; // current digit length
        __int128 kk = k; // use 128-bit for safe arithmetic
        for (; d <= 18; ++d) {
            __int128 cnt = (__int128)9 * (__int128)pow10[d - 1] * d; // total digits contributed by d-digit numbers
            if (kk > cnt) {
                kk -= cnt;
            } else {
                break;
            }
        }

        // kk is 1-indexed position within the d-digit block
        unsigned long long start = pow10[d - 1]; // first d-digit number
        unsigned long long idx0 = (unsigned long long)(kk - 1); // 0-indexed within the block
        unsigned long long number_index = idx0 / (unsigned long long)d; // which number within the block
        unsigned long long digit_index = idx0 % (unsigned long long)d; // which digit within that number (from left, 0-based)
        unsigned long long number = start + number_index;

        string s = to_string(number);
        char ans = s[(size_t)digit_index];
        cout << ans << '\n';
    }

    return 0;
}