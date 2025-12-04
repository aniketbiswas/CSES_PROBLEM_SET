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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;

    cin >> t;

    const int MOD = 1e9 + 7;
    vector<int> dp(1e6 + 1, 0);
    vector<ll> split(1e6 + 1, 0);
    vector<ll> merged(1e6 + 1, 0);

    int maxSeen = 1;
    dp[0] = 0;
    dp[1] = 2; // base case

    while(t--){
        int n;
        cin >> n;
       
        if(dp[n] != 0){
            cout << dp[n] << "\n";
            continue;
        }

        // Base case
        split[1] = 1;
        merged[1] = 1;

        for(int i=maxSeen+1;i<=n;i++){
            split[i] = (split[i - 1] * 4 + merged[i - 1] * 1) % MOD;
            merged[i] = (split[i - 1] * 1 + merged[i - 1] * 2) % MOD;
            dp[i] = (split[i] + merged[i]) % MOD;
        }

        cout << dp[n] << "\n";
        maxSeen = max(maxSeen, n);
    }

    
    
    return 0;
}

