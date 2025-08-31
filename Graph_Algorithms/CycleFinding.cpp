#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = 1e18;  // Large value representing infinity

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, long long>> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    // Bellman-Ford Algorithm for Cycle Detection

    vector<long long> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);

    for(int i=0;i<=n-1;i++) {
        for(const auto &[u, v, w] : edges) {

            // Relaxation step
            if(dist[v] > dist[u] + w) { 
                dist[v] = min(dist[v], dist[u] + w);
                    parent[v] = u;  // Track the parent for cycle reconstruction
            }
        }
    }

    int cycleStart = -1;
    for (const auto &[u, v, w] : edges) {
        if ( dist[v] > dist[u] + w) {
            cycleStart = v;
            dist[v] = dist[u] + w;
            parent[v] = u;

            // If we found a cycle, we can break
            break;
        }
    }

    if (cycleStart != -1) {
        // If a cycle was found, we need to find the cycle nodes
        cout << "YES" << endl;

        for(int i=0;i<n;i++) {
            cycleStart = parent[cycleStart];
        }

        vector<int> cycle;
        int curr = cycleStart;

        do {
            cycle.push_back(curr);
            curr = parent[curr];
        } while (curr != cycleStart);

        cout << cycleStart << " ";
        reverse(cycle.begin(), cycle.end());
        for (int node : cycle) {
            cout << node << " ";
        }


    } else {
        cout << "NO" << endl;
    }




    return 0;
}