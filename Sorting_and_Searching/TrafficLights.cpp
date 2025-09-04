#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    
    set<int> lights;           // positions of traffic lights
    multiset<int> segments;    // lengths of segments between lights
    
    // Initialize: lights at 0 and n, one segment of length n
    lights.insert(0);
    lights.insert(n);
    segments.insert(n);
    
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        
        // Find the segment that will be split by adding light at x
        auto right = lights.upper_bound(x);  // first light > x
        auto left = prev(right);             // light just before x
        
        // Remove the old segment length
        segments.erase(segments.find(*right - *left));
        
        // Add the two new segment lengths
        segments.insert(x - *left);         // left segment
        segments.insert(*right - x);        // right segment
        
        // Add the new light
        lights.insert(x);
        
        // Output the maximum segment length
        cout << *segments.rbegin() << " ";
    }
    
    return 0;
}