// Apple Division (CSES)
// Goal: split n weights into two groups minimizing the difference of sums.
// Approach: enumerate all subsets (n <= 20) and minimize |total - 2 * subset_sum|.
// Complexity: O(n * 2^n), which is fine for n <= 20.
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
void findBest(const vector<long long>& apples, long long & total, long long & best,long long current, int i, int & n) {
    if(total < 2*current) return;   

    if(i==n && total >= 2*current){
        best = min(best, total - 2*current);
        return;
    }

    findBest(apples, total, best, current + apples[i], i + 1, n); // include apples[i]
    findBest(apples, total, best, current, i + 1, n); // exclude apples[i]
}

int main() {
    ios::sync_with_stdio(false); // fast I/O
    cin.tie(nullptr);

    int n;
    cin >> n;

    std::vector<long long> apples(n); // use long long for safe summation
    for (int i = 0; i < n; i++) {
        cin >> apples[i];
    }

    long long total = accumulate(apples.begin(), apples.end(), 0LL); // total sum of all apples

    long long best = total; // track minimal difference |total - 2 * s|
    findBest(apples, total, best, 0, 0, n);

    cout << best << '\n'; // minimal achievable difference
    return 0;
}