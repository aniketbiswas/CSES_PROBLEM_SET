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

long long binomialExponentiation(ll base, ll exp) {
    ll result = 1;
    const ll mod = 1e9 + 7;
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
    cin >> n ;

    for(int i=0; i<n; i++){
        ll base, exp;
        cin >> base >> exp;
        cout << binomialExponentiation(base, exp) << "\n";
    }

    return 0;
}