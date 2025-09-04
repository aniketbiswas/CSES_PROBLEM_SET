#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> towers; // stores the top cube of each tower
    
    for (int i = 0; i < n; i++) {
        int cube;
        cin >> cube;
        
        // Find the leftmost tower where we can place this cube
        // We want the smallest tower top that is > cube
        auto it = lower_bound(towers.begin(), towers.end(), cube + 1);

        if (it == towers.end()) {
            // No tower found, create a new tower
            towers.push_back(cube);
        } else {
            // Replace the top of the found tower
            *it = cube;
        }
    }
    
    cout << towers.size() << endl;
    return 0;
}
