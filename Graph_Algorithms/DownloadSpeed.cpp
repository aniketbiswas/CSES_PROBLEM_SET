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
long long INF = 1e18;


long long bfs(int s, int t, vector<vector<int>> &adj, vector<vector<long long>> &capacity, vector<int> &parent) {

    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2; // mark the source as visited
    queue<pair<int, long long>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        long long flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) { // not visited and has capacity left
                parent[v] = u;
                long long new_flow = min(flow, capacity[u][v]);
                if (v == t) {
                    return new_flow;
                }
                q.push({v, new_flow});
            }
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n,m;

    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<vector<long long>> capacity(n,vector<long long>(n,0));

    // node 0 is source, node n-1 is sink
    for(int i=0;i<m;i++){
        int u,v;
        long long cap;
        cin >> u >> v >> cap;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u); // we need the reverse edge for residual graph
        capacity[u][v] += cap;
    }

    ll totalFlow = 0;
    vector<int> parent(n);
    while (true) {
        long long flow = bfs(0, n - 1, adj, capacity, parent);
        if (flow == 0) {
            break; // no more augmenting path
        }
        totalFlow += flow;
        int v = n - 1;
        while (v != 0) {
            int u = parent[v];
            capacity[u][v] -= flow;
            capacity[v][u] += flow;
            v = u;
        }
    }

    cout << totalFlow << endl;
    return 0;
}