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

    vector<pair<int,int>> tasks(n);

    for(int i=0;i<n;i++) {
        cin >> tasks[i].first >> tasks[i].second;
    }

    // Sort tasks by duration (shortest first) - this is optimal!
    sort(tasks.begin(), tasks.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first < b.first; // Sort by duration only
    });

    ll currentTime = 0, totalScore = 0;
    
    for(const auto& task : tasks) {
        currentTime += task.first;
        totalScore += task.second - currentTime;
    }

    cout << totalScore << "\n";
    return 0;
}