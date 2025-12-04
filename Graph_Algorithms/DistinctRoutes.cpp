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

int bfs(int s, int t, vector<vector<int>> &adj, vector<vector<long long>> &capacity, vector<int> &parent) {

    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2; // mark the source as visited
    queue<pair<int, long long>> q;
    q.push({s, LLONG_MAX});

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
    vector<pair<int,int>> edges(m);

    // node 0 is source, node n-1 is sink
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v ;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u); // store reverse neighbour for residual graph traversal
        capacity[u][v] += 1; // allow multiple edges to accumulate
        edges[i] = {u,v};
    }


    int s = 0;
    int t = n-1;
    vector<int> parent(n);
    long long total_flow = 0;
    int currentFlow = 0;
    while ((currentFlow = bfs(s, t, adj, capacity, parent))) {
        total_flow += currentFlow;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= currentFlow;
            capacity[v][u] += currentFlow;
        }
    }

    vector<vector<int>> flow_adj(n);
    for (const auto &[u, v] : edges) {
        if (capacity[v][u] > 0) {
            flow_adj[u].push_back(v);
        }
    }

    cout << total_flow << '\n';
    for (long long i = 0; i < total_flow; ++i) {
        vector<int> path;
        int node = s;
        path.push_back(node);
        while (node != t) {
            if (flow_adj[node].empty()) {
                break;
            }
            int nxt = flow_adj[node].back();
            flow_adj[node].pop_back();
            node = nxt;
            path.push_back(node);
        }

        cout << path.size() << '\n';
        for (int v : path) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}