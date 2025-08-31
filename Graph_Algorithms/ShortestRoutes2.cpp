#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = 1e18;

int main () {
    int n, m, q;

    cin >> n >> m >> q;

    vector<vector<long long>> adj(n+1, vector<long long>(n+1, INF));

    for(int i=0; i<n+1; i++) {
        adj[i][i] = 0LL;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }

    for(int i=1; i<=n ; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(adj[j][i] != INF && adj[i][k] != INF){
                    adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
                }
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        if (adj[u][v] == INF) {
            cout << -1 << endl;
        } else {
            cout << adj[u][v] << endl;
            // for (int i = 1; i <= n; i++) {
            //     if (adj[u][i] != INT_MAX && adj[i][v] != INT_MAX) {
            //         cout << adj[u][i] + adj[i][v] << endl;
            //     }
            // }
        }
    }


    return 0;
}