#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void findLongestRepetition(const string& s) {
    int maxCount = 1, currentCount = 1;

    for(size_t i = 1; i < s.length(); ++i) {
        if (s[i] == s[i - 1]) {
            currentCount++;
        } else {
            maxCount = max(maxCount, currentCount);
            currentCount = 1;
        }
    }
    maxCount = max(maxCount, currentCount);
    cout << maxCount << endl;
}

int main() {
    string s;
    cin >> s;

    findLongestRepetition(s);
    return 0;
}