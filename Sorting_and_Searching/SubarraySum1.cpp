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

    int n, x;
    cin >> n >> x;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Sliding window approach - works because all numbers are positive
    int left = 0;
    ll currentSum = 0;
    int count = 0;

    for(int right = 0; right < n; right++) {
        // Expand window by adding arr[right]
        currentSum += arr[right];

        // Shrink window from left while sum > target
        while(currentSum > x && left <= right) {
            currentSum -= arr[left];
            left++;
        }

        // Check if current window sum equals target
        if(currentSum == x) {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}