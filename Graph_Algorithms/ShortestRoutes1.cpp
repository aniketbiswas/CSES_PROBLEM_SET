#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // Adjacency list: adj[u] = {v, weight}
    vector<vector<pair<int, long long>>> adj(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }
    
    // Distance array
    vector<long long> dist(n + 1, INF);
    
    // Priority queue: {distance, node}
    // Using greater<> for min-heap
    priority_queue<pair<long long, int>, 
                   vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> pq;
    
    // Start from node 1
    dist[1] = 0;
    pq.push({0, 1});
    
    // Dijkstra's algorithm
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        // Skip if we've already found a better path
        if (d > dist[u]) continue;
        
        // Relax all edges from u
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    // Output distances
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << "\n";
    
    return 0;
}