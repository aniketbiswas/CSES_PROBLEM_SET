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
    
    int n;
    cin >> n;

    vector<int> arr(n);
    vector<pair<int,int>> st;

    for(int i=0;i<n;i++){
        cin >> arr[i];

        while(!st.empty() && st.back().first >= arr[i]){
            st.pop_back();
        }

        if(st.empty()) {
            cout << 0 << " ";                    // No smaller element to the left
        } else {
            cout << st.back().second + 1 << " "; // Convert to 1-indexed position
        }

        st.push_back({arr[i],i});
    }

    
    return 0;
}