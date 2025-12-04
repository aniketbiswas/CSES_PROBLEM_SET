/*
 * SRTBOT Framework Analysis:
 * 
 * Problem: Fill missing values (0s) in array such that adjacent elements differ by at most 1
 *          Count total number of valid ways to fill the array
 * 
 * S (Subproblem): dp[i][v] = number of ways to fill positions [0...i] such that
 *                            position i has value v
 * 
 * R (Recurrence): For position i with value v:
 *                 dp[i][v] = sum of dp[i-1][u] where |u - v| ≤ 1
 *                 
 *                 i.e., u ∈ {v-1, v, v+1} (transition from adjacent values)
 *                 
 *                 Special cases:
 *                 - If arr[i] = 0 (missing): sum over all valid v (1 to m)
 *                 - If arr[i] = k (fixed): only compute dp[i][k], others = 0
 * 
 * T (Topological Order): 
 *                 OUTER loop: Position i from 0 to n-1 (left to right)
 *                 INNER loop: Value v from 1 to m
 *                 TRANSITION: Check previous values u ∈ {v-1, v, v+1}
 *                 
 *                 Sequential processing ensures dp[i-1][*] is computed before dp[i][*]
 * 
 * B (Base case): Position 0:
 *                - If arr[0] = 0: dp[0][v] = 1 for all v ∈ [1, m]
 *                - If arr[0] = k: dp[0][k] = 1, dp[0][v≠k] = 0
 * 
 * O (Original Problem): Sum of dp[n-1][v] for all v ∈ [1, m]
 *                       (Total ways to reach end position with any valid value)
 * 
 * T (Time Complexity): O(n × m × 3) = O(n × m)
 *                      - n positions, m values, 3 transitions per state
 *                      Space: O(n × m) or O(m) with rolling array optimization
 * 
 * Mental Model: Path Counting in Layered Graph
 * - Each (position, value) is a node
 * - Edge exists from (i-1, u) to (i, v) if |u - v| ≤ 1
 * - Fixed values = only one active node at that position
 * - Missing values = all m nodes active at that position
 * - Count all paths from layer 0 to layer n-1
 * 
 * Key Insight: Right constraints (future fixed values) naturally propagate through
 *              sequential DP - invalid paths get 0 count automatically!
 */

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
    
    int n,m;
    cin >> n >> m;

    vector<int> upper(n);

    for(int i=0;i<n;i++){
        cin >> upper[i];
    }

    const int MOD = 1e9 + 7;

    vector<vector<ll>> dp(n,vector<ll>(m + 1,0));

    // Base case: position 0
    if(upper[0] == 0){
        for(int v=1;v<=m;v++){
            dp[0][v] = 1;
        }
    } else {
        dp[0][upper[0]] = 1;
    }

    for(int i=1;i<n;i++) {
        if(upper[i] == 0){
            // we just need to see i-1, for all v and if |u - v| ≤ 1
            // then we update the dp[i][v] accordingly 
            for(int v=1;v<=m;v++){
                for(int u = max(1, v - 1); u <= min(m, v + 1); u++){
                    dp[i][v] = (dp[i][v] + dp[i - 1][u]) % MOD;
                }
            }
        } else {
            // If upper[i] is not 0, we only need to consider that specific value
            int v = upper[i];
            for(int u = max(1, v - 1); u <= min(m, v + 1); u++){
                dp[i][v] = (dp[i][v] + dp[i - 1][u]) % MOD;
            }
        }
    }


    ll result = 0;
    for(int v=1;v<=m;v++){
        result = (result + dp[n - 1][v]) % MOD;
    }
    cout << result << "\n";
    
    return 0;
}