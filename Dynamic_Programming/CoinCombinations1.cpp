/*
 * SRTBOT Framework Analysis:
 * 
 * S (Subproblem): dp[i] = number of ORDERED ways to make sum i using given coins
 *                 (Order matters: {1,2} and {2,1} are different)
 * 
 * R (Recurrence): dp[i] = sum of dp[i-c1] + dp[i-c2] + ... + dp[i-ck]
 *                 where c1, c2, ..., ck are available coin values
 *                 (For each coin, add ways to make the remaining sum)
 * 
 * T (Topological Order): OUTER loop: amount from 1 to x
 *                        INNER loop: for each coin
 *                        This order counts ORDERED sequences (permutations)
 *                        Swapping loops would count UNORDERED combinations
 * 
 * B (Base case): dp[0] = 1 (one way to make sum 0: use no coins)
 * 
 * O (Original Problem): dp[x] = number of ordered ways to make sum x
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

    for (int amount = 1; amount <= x; amount++)
    {
    // Looping amounts outside counts ordered sequences: for each partial sum we
    // decide which coin is appended next. Switching loop order (coins outer,
    // amounts inner) turns the DP into the combination variant where order
    // does not matter (Coin Combinations II).
        for (int coin : coins)
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