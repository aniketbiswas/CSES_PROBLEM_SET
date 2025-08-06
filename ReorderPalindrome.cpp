#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    int count[26] = {0};

    for(int i=0;i<s.length();i++) {
        count[s[i] - 'A']++;
    }

    int oddCount = 0;
    char oddChar = ' ';
    for(int i=0;i<26;i++) {
        if(count[i] % 2 == 1) {
            oddCount++;
            count[i]--;
            oddChar = 'A' + i; // Store the character with odd count
        }
    }

    if(oddCount > 1) {
        cout << "NO SOLUTION";
        return 0;
    }

    string half = "";
    for(int i=0;i<26;i++) {
        half += string(count[i] / 2, 'A' + i);
    }

    string result = half;
    if(oddCount == 1) {
        result += oddChar;
    }
    reverse(half.begin(), half.end());
    result += half;

    cout << result;
    return 0;
}