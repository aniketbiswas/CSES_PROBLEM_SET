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

    vector<int> time(n);
    for(int i=0;i<n;i++) {
        cin >> time[i];
    }

    ll totalTime = accumulate(time.begin(), time.end(), 0LL);
    ll maxTime = *max_element(time.begin(), time.end());

    // Two cases:
    // 1. Total time is bottleneck (when books are evenly distributed)
    // 2. Longest book is bottleneck (one person reads it while other finishes rest)
    ll result = max(totalTime, 2LL * maxTime);

    cout << result << "\n";
    return 0;
}


// 1 2 3 4
// 1 4 -> 1 + 2 4 -> 