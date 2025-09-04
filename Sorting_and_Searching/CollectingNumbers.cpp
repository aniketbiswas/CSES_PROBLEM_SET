#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Naive Approach 
    // vector<pair<int,int>> nums(n);

    // for(int i=0;i<n;i++) {
    //     cin >> nums[i].first;
    //     nums[i].second = i;
    // }

    // sort(nums.begin(),nums.end());

    // int count = 1;
    // for(int i=1;i<n;i++) {
    //    if(nums[i].second < nums[i-1].second) {
    //       count++;
    //    }
    // }

    // cout << count << endl;
    // return 0;

    // Efficient Approach
    vector<int> position(n);

    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        position[x-1] = i;  // Store the position of number x
    }

    int count = 1;
    for(int i=1;i<n;i++){
        if(position[i] < position[i-1]){
            count++;
        }
    }

    cout << count << endl;
    return 0;

}


// 4 2 1 5 3
// 1 2 3 4 5


// 1 2 3 4 5
// 3 2 5 1 4