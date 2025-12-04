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
#include <unordered_map>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;

    unordered_map<int, int> remainderCount;
    remainderCount[0] = 1;  // Empty prefix has remainder 0
    
    ll prefixSum = 0;
    ll result = 0;
    
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        
        prefixSum += x;
        
        // Handle negative remainders properly
        int remainder = ((prefixSum % n) + n) % n;
        
        // Add count of previous prefixes with same remainder
        result += remainderCount[remainder];
        
        // Update count for current remainder
        remainderCount[remainder]++;
    }

    cout << result << endl;
    return 0;
}