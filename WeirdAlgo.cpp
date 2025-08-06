#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void weirdAlgo(long long n) {
    while (n != 1) {
        cout<< n << " ";
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n * 3 + 1;
        }
    }

    cout << 1 << endl; // Print the last element which is always 1
}

int main() {
    long long n ;
    cin >> n;
    weirdAlgo(n);
    return 0;
}