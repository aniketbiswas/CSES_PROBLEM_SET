#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m , k;

    cin >> n >> m >> k;

    vector<int> apartments(n);
    vector<int> requirements(m);
    for (int i = 0; i < n; i++) {
        cin >> apartments[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> requirements[i];
    }

    sort(apartments.begin(), apartments.end());
    sort(requirements.begin(), requirements.end());

    int satisfied = 0;
    int j = 0;
    for( int i=0;i<n;i++) {
        while(j<m && requirements[j] < apartments[i]-k) j++;

        if(j<m && requirements[j] <= apartments[i]+k) {
            satisfied++;
            j++;
        }
    }

    cout << satisfied << '\n';

    return 0;
}