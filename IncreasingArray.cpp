#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void findMoves(vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
        cin >> nums[i];
    }

    long long moves = 0;
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < nums[i - 1]) {
            moves += nums[i - 1] - nums[i];
            nums[i] = nums[i - 1];
        }
    }

    cout << moves << endl;
}

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);

    findMoves(nums);
    return 0;
}