/*
 * SRTBOT Framework Analysis:
 * 
 * S (Subproblem): dp[i] = number of UNORDERED ways to make sum i using given coins
 *                 (Order doesn't matter: {1,2} and {2,1} are the same)
 * 
 * R (Recurrence): dp[i] = sum of dp[i-c] for current coin c
 *                 (For each coin type, add ways using that coin to make remaining sum)
 * 
 * T (Topological Order): OUTER loop: for each coin type
 *                        INNER loop: amount from 1 to x
 *                        This order counts UNORDERED combinations
 *                        (Process one coin type completely before moving to next)
 *                        Swapping loops would count ORDERED sequences
 * 
 * B (Base case): dp[0] = 1 (one way to make sum 0: use no coins)
 * 
 * O (Original Problem): dp[x] = number of unordered ways to make sum x
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    const int MOD = 1e9 + 7;
    vector<int> dp(x + 1, 0);

    dp[0] = 1;

    for (int coin : coins)
    {
        for (int amount = 1; amount <= x; amount++)
        {
            if ((amount - coin) >= 0)
            {
                dp[amount] += dp[amount - coin] % MOD;
                dp[amount] %= MOD;
            }
        }
    }
    cout << dp[x] << "\n";
    return 0;
}