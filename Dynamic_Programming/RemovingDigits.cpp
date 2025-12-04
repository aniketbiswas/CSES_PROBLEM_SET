/*
 * SRTBOT Framework Analysis:
 * 
 * S (Subproblem): dp[i] = minimum number of steps to reduce number i to 0
 *                 by repeatedly subtracting one of its digits
 * 
 * R (Recurrence): dp[i] = 1 + min(dp[i - d]) for all digits d in i
 *                 where d is a non-zero digit in the decimal representation of i
 *                 (Try subtracting each digit and take the path with minimum steps)
 * 
 * T (Topological Order): Iterate i from 1 to n (increasing order)
 *                        When computing dp[i], all values dp[i-d] are already computed
 *                        since i-d < i for any digit d in i
 * 
 * B (Base case): dp[0] = 0 (already at 0, need 0 steps)
 *                dp[i] = INT_MAX initially (unknown until computed)
 * 
 * O (Original Problem): dp[n] = minimum steps to reduce n to 0
 * 
 * T (Time Complexity): O(n × d) where d ≤ 9 is max number of digits in a number
 *                      Effectively O(n) since d is constant
 *                      Space: O(n)
 * 
 * Key Insight: Greedy (always subtract largest digit) doesn't always work.
 *              Need to explore all digit choices and pick the optimal path.
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

vector<int> getDigits(int n) {
    vector<int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    return digits;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for(int i=1;i<=n;i++) {
        vector<int> digits = getDigits(i);
        for(int digit : digits) {
            if(i - digit >= 0 && dp[i - digit] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - digit] + 1);
            }
        }

    }
    cout << dp[n] << "\n"; 
    
    return 0;
}