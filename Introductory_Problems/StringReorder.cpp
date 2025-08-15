#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.length();
    
    // Count frequency of each character
    vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'A']++;
    }
    
    // Check if solution is possible
    int maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        maxFreq = max(maxFreq, freq[i]);
    }
    
    if (maxFreq > (n + 1) / 2) {
        cout << -1 << endl;
        return 0;
    }
    
    string result = "";
    
    for (int pos = 0; pos < n; pos++) {
        bool placed = false;
        
        // Try characters A to Z (lexicographically)
        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) continue; // Character not available
            
            char candidate = 'A' + i;
            
            // Can't place if same as previous character
            if (pos > 0 && result[pos-1] == candidate) {
                continue;
            }
            
            // Critical check: Can we place remaining characters after using this one?
            freq[i]--; // Temporarily use this character
            
            // Check if remaining characters can be arranged
            vector<int> remaining = freq;
            int maxRemaining = 0;
            int totalRemaining = n - pos - 1;
            
            for (int j = 0; j < 26; j++) {
                maxRemaining = max(maxRemaining, remaining[j]);
            }
            
            // After placing this character, can we arrange the rest?
            bool canArrange = (maxRemaining <= (totalRemaining + 1) / 2);
            
            if (canArrange) {
                result += candidate;
                placed = true;
                break;
            } else {
                freq[i]++; // Restore the count and try next character
            }
        }
        
        // If no character could be placed, solution is impossible
        if (!placed) {
            cout << -1 << endl;
            return 0;
        }
    }
    
    cout << result << endl;
    return 0;
}