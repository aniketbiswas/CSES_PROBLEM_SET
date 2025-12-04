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
    
    int n;
    cin >> n;
    
    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    // prefix sum for quick range sum queries
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + x[i];
    }
    
    // sum of elements from i to j (inclusive)
    auto rangeSum = [&](int i, int j) -> long long {
        return prefix[j + 1] - prefix[i];
    };
    
    // dp[i][j] = max score current player can get from interval [i, j]
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    
    // base case: single element
    for (int i = 0; i < n; i++) {
        dp[i][i] = x[i];
    }
    
    // fill by increasing interval length
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            
            // take left: x[i] + (remaining sum - opponent's optimal)
            long long takeLeft = x[i] + rangeSum(i + 1, j) - dp[i + 1][j];
            
            // take right: x[j] + (remaining sum - opponent's optimal)
            long long takeRight = x[j] + rangeSum(i, j - 1) - dp[i][j - 1];
            
            dp[i][j] = max(takeLeft, takeRight);
        }
    }
    
    cout << dp[0][n - 1] << "\n";
    
    return 0;
}
