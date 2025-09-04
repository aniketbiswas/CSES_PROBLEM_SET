#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i=0;i<n;i++) {
        cin>>arr[i];
    }

    sort(arr.begin(), arr.end());

    long long target = 1;

    for(int i=0;i<n ; i++) {
        if(arr[i] > target){
            cout << target << endl;
            return 0;
        }
        target += arr[i];
    }

    cout << target << endl;
    return 0;
}