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
#include <unordered_set>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    unordered_map<int, int> freq;
    int distinctCount = 0;
    long long totalCount = 0;
    int left = 0;
    
    for(int right = 0; right < n; right++) {
        // Add current element
        if(freq[arr[right]] == 0) {
            distinctCount++;
        }
        freq[arr[right]]++;

        // Shrink window while too many distinct elements
        while(left < right && distinctCount > k) {
            freq[arr[left]]--;
            if(freq[arr[left]] == 0) {
                distinctCount--;
                freq.erase(arr[left]);
            }
            left++;
        }

        // All subarrays ending at 'right' with start >= 'left' are valid
        totalCount += (right - left + 1);
    }

    cout << totalCount << endl;
    return 0;
}