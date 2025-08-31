#include <iostream>
#include <vector>
#include <queue>


using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u-1].push_back(v-1);
        indegree[v-1]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo_order;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        topo_order.push_back(curr + 1); // Store 1-indexed result
        for (int neighbor : adj[curr]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }

    }

    if((int)topo_order.size() != n) {
        cout << "IMPOSSIBLE" << endl;
        return 0; // Exit if cycle is detected
    }
    for (int i : topo_order) {
        cout << i << " ";
    }

    return 0;
}