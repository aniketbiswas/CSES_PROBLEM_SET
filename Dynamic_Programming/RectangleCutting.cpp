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

    vector<string> grid(n);

    for(string &row : grid){
        cin >> row;
    }

    vector<vector<char>> dp(n,vector<char>(n,'-'));

    dp[0][0] = 'O'; // starting point

    for(int i=1;i<n;i++){
        dp[i][0] = 'D' ; // can only come from above
        dp[0][i] = 'R' ; // can only come from left
    }

    for(int i=1;i<n;i++){
        for(int j=1;j<n;j++){
            if(grid[i-1][j] < grid[i][j-1]){
                dp[i][j] = 'D'; // came from above
            } else {
                dp[i][j] = 'R'; // came from left
            }
        }
    }


    string result = "";

    int r = n - 1;
    int c = n - 1;

    while(!(r == 0 && c == 0)){
        char move = dp[r][c];
        result += move;
        if(move == 'D'){
            r--;
        } else if(move == 'R'){
            c--;
        }
    }

    reverse(result.begin(), result.end());
    cout << grid[0][0] + result << "\n";
    
    return 0;
}