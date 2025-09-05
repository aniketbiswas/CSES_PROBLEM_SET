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
    
    ll n,t;

    cin >> n >> t;

    vector<int> machines(n);

    for (int i = 0; i < n; i++) {
        cin >> machines[i];
    }

    long long minTime = *min_element(machines.begin(), machines.end())*t;

    // if(n == 1) {
    //     cout << minTime << endl;
    //     return 0;
    // }

    long long left = 0 , right = minTime;

    while(left < right) {
        long long mid = left + (right - left) / 2LL;

        long long totalProducts = 0LL;
        for(int i=0;i<n;i++) {
            totalProducts += mid / (long long)machines[i];
        }

        if(totalProducts >= t) {
            right = mid;
        }
        else {
            left = mid + 1LL;
        }
    }

    cout << left << endl;

    return 0;
}