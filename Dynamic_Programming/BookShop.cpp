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
    
    int n,x;
    cin >> n >> x;
    vector<int> bookCost(n);
    vector<int> bookPages(n);

    for(int i=0;i<n;i++){
        cin >> bookCost[i];
    }

    for(int i=0;i<n;i++){
        cin >> bookPages[i];
    }

    vector<ll> dp(x + 1, 0);
    for(int i=0;i<n;i++){
        for(int amount = x; amount >= bookCost[i]; amount--){
            dp[amount] = max(dp[amount], dp[amount - bookCost[i]] + bookPages[i]);
        }
    }

    cout << dp[x] << endl;
    return 0;
}