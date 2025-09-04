#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>


using namespace std;

int main () {
    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }


    long long totalSum = 0;
    int maxElement = *max_element(arr.begin(), arr.end());
    long long maxSum = maxElement;
    for(int i=0;i<n;i++) {
        totalSum += arr[i];
        if(totalSum < 0){
            totalSum = 0;
        }
        maxSum = max(maxSum, totalSum);
    }

    cout << (maxSum == 0 ? maxElement : maxSum) << endl;

    return 0;
}