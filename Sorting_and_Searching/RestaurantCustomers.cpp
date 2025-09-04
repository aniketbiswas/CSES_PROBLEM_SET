#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    map<int,int> mp;

    for(int i=0;i<n;i++){
        int x, y;
        cin >> x >> y;
        mp[x]++;
        mp[y+1]--;
    }

    int currCustomers = 0;
    int maxCustomers = 0;

    for(auto [time,change] : mp) {
        currCustomers += change;
        maxCustomers = max(maxCustomers, currCustomers);
    }
    cout << maxCustomers << endl;

    return 0;
}