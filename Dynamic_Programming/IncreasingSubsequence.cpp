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
    int n;
    cin >> n;
    vector<int> sequence(n);
    for (int i = 0; i < n; i++) cin >> sequence[i];
    
    // tails[i] = smallest ending element of all increasing subsequences of length i+1
    vector<int> tails;
    
    for (int x : sequence) {
        // Binary search for position to insert/replace
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);  // Extend longest subsequence
        } else {
            *it = x;  // Replace to keep smallest tail
        }
    }
    
    cout << tails.size() << endl;
    
    return 0;
}