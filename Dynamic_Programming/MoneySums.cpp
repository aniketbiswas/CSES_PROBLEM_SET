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
#include <numeric>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;

    cin >> n;

    vector<int> coins(n);

    for(int i=0;i<n;i++){
        cin >> coins[i];
    }

    int maxSum = accumulate(coins.begin(), coins.end(), 0);


    vector<bool> dp(maxSum + 1, false);

    dp[0] = true; // sum of 0 is always possible

    for(int coin : coins) {
        for(int sum = maxSum - coin; sum >= 0; sum--){
            if(dp[sum]){
                dp[sum + coin] = true;
            }
        }
    }

    int count = 0;
    vector<int> results;
    for(int s = 1;s<=maxSum;s++){
        if(dp[s]){
            results.push_back(s);
            count++;
        }
    }
    cout << count << '\n';

    for(int res : results) {
        cout << res << " ";
    }
    cout << '\n';
    
    return 0;
}