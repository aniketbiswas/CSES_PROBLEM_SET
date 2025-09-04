#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


int main () {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());
    
    long long totalCost = 0;
    for(int i=0;i<n/2;i++) {
        totalCost += (long long)arr[n-i-1] - (long long)arr[i];
    }

    cout << totalCost << endl;

    return 0;
}