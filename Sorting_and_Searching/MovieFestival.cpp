#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<long long>> movies(n, vector<long long>(2));

    for(int i=0;i<n;i++){
        cin >> movies[i][0] >> movies[i][1];
    }

    sort(movies.begin(),movies.end(), [](const vector<long long>& a, const vector<long long>& b) {
        if(a[1] == b[1])
            return a[0] < b[0];
        return a[1] < b[1];
    });

    long long maxMovies = 0;
    long long lastEndTime = 0;

    for(const auto& movie : movies) {
        if(movie[0] >= lastEndTime) {
            maxMovies++;
            lastEndTime = movie[1];
        }
    }

    cout << maxMovies << endl;

    return 0;
}