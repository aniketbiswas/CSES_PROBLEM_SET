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
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n , x;
    cin >> n >> x;

    unordered_map<ll, int> prefixSum;
    vector<int> arr(n);
    prefixSum[0] = 1;

    ll currentSum = 0;
    ll count = 0;

    for(int i=0;i<n;i++)
        cin >> arr[i];

    int minEl = *min_element(arr.begin(), arr.end());

    for(int i=0; i<n; i++){
        currentSum += arr[i];

        if(prefixSum.find(currentSum - x) != prefixSum.end()){
            count += prefixSum[currentSum - x];
        }

        prefixSum[currentSum]++;
    }

    cout << count << endl;

    return 0;
}