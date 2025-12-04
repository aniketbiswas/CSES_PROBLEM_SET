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

    vector<int> first(n, 0);
    vector<int> second(m, 0);

    for(int i=0;i<n;i++){
        cin >> first[i];
    }

    for(int j=0;j<m;j++){
        cin >> second[j];
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));


    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(first[i-1] == second[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    cout << dp[n][m]<<endl;

    // After building dp table:
    string lcs = "";
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (first[i-1] == second[j-1]) {
            // Character match - part of LCS
            lcs = to_string(first[i-1]) + " " + lcs;  // Prepend to result
            i--;
            j--;
        }
        else if (dp[i-1][j] > dp[i][j-1]) {
            // Came from top (skip element from first array)
            i--;
        }
        else {
            // Came from left (skip element from second array)
            j--;
        }
    }

    cout << lcs << "\n";
    return 0;
}