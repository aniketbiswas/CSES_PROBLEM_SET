#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <climits>
#include <cmath>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

long long binomialExponentiation(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;
    while(exp > 0){
        if(exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        
        // Handle edge cases carefully
        
        // Case 1: a = 1 (1^anything = 1)
        if(a == 1) {
            cout << 1 << "\n";
            continue;
        }
        
        // Case 2: c = 0 (b^0 = 1, so result is a^1 = a)
        if(c == 0) {
            cout << a % MOD << "\n";
            continue;
        }
        
        // Case 3: b = 0 (0^c = 0 for c > 0, so result is a^0 = 1)
        if(b == 0) {
            cout << 1 << "\n";
            continue;
        }
        
        // Case 4: a = 0 (but only after checking if exponent is 0)
        // We already know b != 0 and c != 0 from above
        // So b^c > 0, which means 0^(positive) = 0
        if(a == 0) {
            cout << 0 << "\n";
            continue;
        }
        
        // General case: Use Euler's theorem
        // a^(b^c) ≡ a^(b^c mod φ(MOD)) (mod MOD)
        // Since MOD = 10^9 + 7 is prime, φ(MOD) = MOD - 1
        ll phi_mod = MOD - 1;
        
        // Compute b^c mod φ(MOD)
        ll exponent = binomialExponentiation(b, c, phi_mod);
        
        // Important: If exponent becomes 0, we need to use φ(MOD) instead
        // This happens because a^0 = 1, but we want a^(φ(MOD)) when b^c ≡ 0 (mod φ(MOD))
        if(exponent == 0) {
            exponent = phi_mod;
        }
        
        // Compute a^exponent mod MOD
        ll result = binomialExponentiation(a, exponent, MOD);
        
        cout << result << "\n";
    }

    return 0;
}