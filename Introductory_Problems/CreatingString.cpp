#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

void createPermutations(string s, int l, int r, unordered_set<string> &permutations) {
    if (l == r) {
        permutations.insert(s);
    } else {
        for (int i = l; i <= r; i++) {
            swap(s[l], s[i]);
            createPermutations(s, l + 1, r, permutations);
            swap(s[l], s[i]); // backtrack
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    unordered_set<string> permutations;

    sort(s.begin(), s.end());

    createPermutations(s, 0, n - 1, permutations);
    vector<string> result(permutations.begin(), permutations.end());
    sort(result.begin(), result.end());
    cout << result.size() << '\n';
    for (const string &perm : result) {
        cout << perm << '\n';
    }

    return 0;
}