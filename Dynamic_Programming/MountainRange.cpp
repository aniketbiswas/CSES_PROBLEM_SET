#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

// O(n log n) solution using monotonic stack + binary search
//
// Key insight: From position i going RIGHT, the valid landing spots j are those where:
//   h[j] > max(h[i+1..j-1])
// These elements form a DECREASING sequence (each new valid spot must be smaller
// than all previous valid spots, otherwise it would be blocked).
//
// Similarly for going LEFT.
//
// Since valid spots form a decreasing sequence, we can BINARY SEARCH
// for the closest value to h[i] (but still < h[i]).

int n;
vector<int> h;
vector<int> closestLeft, closestRight;
vector<int> dp;

// Binary search in a decreasing sequence for largest value < target
// Returns index in original array, or -1 if not found
int binarySearchClosest(const vector<pair<int,int>>& candidates, int target) {
    // candidates = [(height, original_index), ...] in DECREASING order of height
    // Find the one with height < target and closest to target
    
    if (candidates.empty()) return -1;
    
    // Binary search for first element with height < target
    int lo = 0, hi = candidates.size() - 1;
    int result = -1;
    
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (candidates[mid].first < target) {
            result = mid;  // This is valid, but try to find closer (larger value)
            hi = mid - 1;  // Look for larger values (earlier in decreasing sequence)
        } else {
            lo = mid + 1;  // Too big, look for smaller values
        }
    }
    
    if (result == -1) return -1;
    return candidates[result].second;
}

void precompute() {
    closestLeft.assign(n, -1);
    closestRight.assign(n, -1);
    
    // Compute closestRight for each i
    // Process from right to left, maintaining valid landing spots
    vector<pair<int,int>> rightCandidates;  // (height, index), decreasing by height
    
    for (int i = n - 1; i >= 0; i--) {
        // Find closest among rightCandidates with height < h[i]
        closestRight[i] = binarySearchClosest(rightCandidates, h[i]);
        
        // Add h[i] to candidates, maintaining decreasing property
        // Remove all elements <= h[i] (they're now blocked by h[i])
        while (!rightCandidates.empty() && rightCandidates.back().first <= h[i]) {
            rightCandidates.pop_back();
        }
        rightCandidates.push_back({h[i], i});
    }
    
    // Compute closestLeft for each i
    // Process from left to right
    vector<pair<int,int>> leftCandidates;
    
    for (int i = 0; i < n; i++) {
        // Find closest among leftCandidates with height < h[i]
        closestLeft[i] = binarySearchClosest(leftCandidates, h[i]);
        
        // Add h[i] to candidates
        while (!leftCandidates.empty() && leftCandidates.back().first <= h[i]) {
            leftCandidates.pop_back();
        }
        leftCandidates.push_back({h[i], i});
    }
}

int solve(int i) {
    if (dp[i] != -1) return dp[i];
    
    int res = 1;
    
    if (closestLeft[i] != -1) {
        res = max(res, 1 + solve(closestLeft[i]));
    }
    
    if (closestRight[i] != -1) {
        res = max(res, 1 + solve(closestRight[i]));
    }
    
    return dp[i] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    h.resize(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    
    precompute();
    dp.assign(n, -1);
    
    int ans = 1;
    for (int i = 0; i < n; i++) {
        ans = max(ans, solve(i));
    }
    
    cout << ans << endl;
    return 0;
}