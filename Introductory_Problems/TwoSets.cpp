// Two sets can be formed if and only if n*(n+1)/2 is even
// This happens when n%4 == 0 or n%4 == 3
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    long long totalSum = (long long)n * (n + 1) / 2;
    
    if (totalSum % 2 == 1) {
        cout << "NO" << endl;
        return 0;
    }
    
    cout << "YES" << endl;
    
    vector<int> set1, set2;
    long long target = totalSum / 2;
    
    // Greedy approach: start from largest number and add to set1 if possible
    for (int i = n; i >= 1; i--) {
        if (target >= i) {
            set1.push_back(i);
            target -= i;
        } else {
            set2.push_back(i);
        }
    }
    
    cout << set1.size() << endl;
    for (int num : set1) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << set2.size() << endl;
    for (int num : set2) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}