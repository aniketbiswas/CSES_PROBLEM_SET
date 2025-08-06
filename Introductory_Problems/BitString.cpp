#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long long binomialExponentiation(long long power)
{
    long long base = 2;
    long long result = 1;
    int mod = 1000000007;
    while (power > 0)
    {
        if (power & 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1;
    }
    return result;
}

int main()
{
    long long n;
    cin >> n;
    cout << binomialExponentiation(n);

    return 0;
}