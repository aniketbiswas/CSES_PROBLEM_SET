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
    int MOD = 1e9 + 7;
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> grid[i][j];
        }
    }

    if(grid[0][0] == '*' || grid[n-1][n-1] == '*'){
        cout << 0 << endl;
        return 0;
    }
    
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    dp[0][0] = 1;
    for(int i=1;i<n;i++){
        dp[i][0] = (grid[i][0] == '.' ? dp[i-1][0] : 0);
        if(grid[i][0] == '*') break;

    }

    for(int j=1;j<n;j++){
        dp[0][j] = (grid[0][j] == '.' ? dp[0][j-1] : 0);
        if(grid[0][j] == '*') break;
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            if(grid[i][j] == '.'){
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    cout << dp[n-1][n-1] << endl;
    return 0;
}