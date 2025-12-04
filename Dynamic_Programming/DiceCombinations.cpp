/*
 * SRTBOT Framework Analysis:
 * 
 * S (Subproblem): dp[i] = number of ways to construct sum i using dice throws (1-6)
 * 
 * R (Recurrence): dp[i] = sum of dp[i-1] + dp[i-2] + ... + dp[i-6]
 *                 (We can reach sum i by throwing 1,2,3,4,5, or 6 from previous states)
 * 
 * T (Topological Order): Iterate i from 0 to n (increasing order)
 *                        For each i, try all dice values 1-6
 * 
 * B (Base case): dp[0] = 1 (one way to make sum 0: throw nothing)
 * 
 * O (Original Problem): dp[n] = number of ways to construct sum n
 * 
 * T (Time Complexity): O(n * 6) = O(n)
 *                      Space: O(n)
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
    
    int n;
    cin >> n;

    const int MOD = 1e9 + 7;
    vector<int> dp(n + 1, 0);

    dp[0] = 1;

    for(int i=0;i<=n;i++){
        for(int dice=1;dice<=6;dice++){
            if(i - dice >= 0){
                dp[i] = (dp[i] + dp[i - dice]) % MOD;
            }
        }
    }
    cout << dp[n] << "\n";
    return 0;
}