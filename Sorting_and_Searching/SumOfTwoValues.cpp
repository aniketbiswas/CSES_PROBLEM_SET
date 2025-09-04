#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;

int main () {
    int n, sum;
    cin >> n >> sum;
    vector<pair<int,int>> arr(n);
    for(int i=0;i<n; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }

    sort(arr.begin(), arr.end());
    int start =  0, end = n-1;

    while(start < end) {
        int current_sum = arr[start].first + arr[end].first;
        if(current_sum == sum) {
            cout << arr[start].second + 1 << " " << arr[end].second + 1 << endl;
            return 0;
        }
        else if(current_sum < sum) {
            start++;
        }
        else {
            end--;
        }
    }

    cout<< "IMPOSSIBLE" ;
    return 0;
}