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

bool isFeasible(vector<int> &arr,ll & subSum, int & k){
    int count = 1;
    ll currentSum = 0;

    for(int i = 0; i < arr.size(); i++){
        if(currentSum + arr[i] > subSum){
            count++;
            currentSum = arr[i];
        } else {
            currentSum += arr[i];
        }
    }

    return count <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> arr(n);

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    ll left = *max_element(arr.begin(), arr.end());
    ll right = accumulate(arr.begin(), arr.end(), 0LL);
    ll answer = right;

    while(left <= right){
        ll mid = left + (right - left) / 2;

        if(isFeasible(arr, mid, k)){
            answer = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << answer << endl;

    return 0;
}