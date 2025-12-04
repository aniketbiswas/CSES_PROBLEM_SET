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
    
    string m,n;
    cin >> m >> n;
    
    int lenM = m.length();
    int lenN = n.length();

    vector<vector<int>> dp(lenM + 1, vector<int>(lenN + 1, 0));

    for(int i=0;i<=lenM;i++){
        dp[i][0] = i; // delete all characters from m
    }
    for(int j=0;j<=lenN;j++){
        dp[0][j] = j; // insert all characters to m to form n
    }

    for(int i=1;i<=lenM;i++){
        for(int j=1;j<=lenN;j++){
            if(m[i - 1] == n[j - 1]){
                dp[i][j] = dp[i - 1][j - 1]; // no operation needed
            } else {
                int replaceCost = 1 + dp[i - 1][j - 1];
                int deleteCost = 1 + dp[i - 1][j];
                int insertCost = 1 + dp[i][j - 1];

                dp[i][j] = min({replaceCost, deleteCost, insertCost});
            }
        }
    }

    cout << dp[lenM][lenN] << "\n";
    return 0;
}