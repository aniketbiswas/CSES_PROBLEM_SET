#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, allowedWeight;

    cin >> n >> allowedWeight;

    vector<int> weights(n);

    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    sort(weights.begin(), weights.end());

    int left = 0, right = n-1;

    while(left < right) {
        if(weights[left] + weights[right] <= allowedWeight) {
            left++;
            right--;
        } else {
            right--;
        }
    }

    cout << (n - left) << endl;

    return 0;
}