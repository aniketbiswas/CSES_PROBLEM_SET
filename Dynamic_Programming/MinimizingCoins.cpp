/*
 * SRTBOT Framework Analysis:
 * 
 * S (Subproblem): dp[i] = minimum number of coins needed to make sum i
 * 
 * R (Recurrence): dp[i] = min(dp[i-c1] + 1, dp[i-c2] + 1, ..., dp[i-ck] + 1)
 *                 where c1, c2, ..., ck are available coin values
 *                 (Try using each coin and take the minimum)
 * 
 * T (Topological Order): Iterate amount from 1 to x (increasing order)
 *                        For each amount, try all available coins
 * 
 * B (Base case): dp[0] = 0 (zero coins needed to make sum 0)
 *                dp[i] = INT_MAX initially (impossible until computed)
 * 
 * O (Original Problem): dp[x] = minimum coins needed to make sum x
 *                       Return -1 if dp[x] == INT_MAX (impossible)
 * 
 * T (Time Complexity): O(x * n) where x is target sum, n is number of coins
 *                      Space: O(x)
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
    
    int n, x;
    cin >> n >> x;

    vector<int> coins(n);

    for(int i=0;i<n;i++){
        cin >> coins[i];
    }

    vector<int> dp(x + 1, INT_MAX);

    dp[0] = 0;
    for(int amount=1;amount<=x;amount++){
        for(int coin : coins) {
            if(amount - coin >= 0 && dp[amount - coin] != INT_MAX){
                dp[amount] = min(dp[amount], dp[amount - coin] + 1);
            }
        }
    }

    if(dp[x] == INT_MAX){
        cout << -1 << "\n";
    } else {
        cout << dp[x] << "\n";
    }

    
    return 0;
}