#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>


using namespace std;

int main () {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    unordered_map<int,int> indexMap;

    long long left = 0, right = 0, distinctCount = 0;

    while (right < n) {
        
        indexMap[nums[right]]++;
        while (left < right && indexMap[nums[right]] > 1) {
            indexMap[nums[left]]--;
            left++;
        }
        
        right++;
        distinctCount += right - left;

        // Here, [left, right) is a valid range with at most 2 distinct values
        // Process this range as needed
    }

    cout << distinctCount << endl;
    return 0;
}