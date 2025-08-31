#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Define a type for pairs to make the code cleaner: {cost, city}
using pii = pair<long long, int>;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    // Adjacency list to store the graph: graph[u] = {{v1, w1}, {v2, w2}, ...}
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    // dists[i] will store the costs of the k cheapest routes to city i
    vector<long long> dists[n + 1];
    
    // Min-priority queue for Dijkstra's algorithm. It stores {cost, city}.
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Start the search from city 1 with a cost of 0
    pq.push({0, 1});

    while (!pq.empty()) {
        // Get the path with the smallest cost from the priority queue
        auto [cost, city] = pq.top();
        pq.pop();

        // If we have already found k cheapest paths to this city,
        // any further path we extract for it will be more expensive.
        // So, we can ignore it and all paths branching from it.
        if (dists[city].size() >= k) {
            continue;
        }

        // This is a new, valid path. Store its cost.
        dists[city].push_back(cost);

        // Explore all outgoing flights from the current city
        for (auto& edge : graph[city]) {
            int neighbor = edge.first;
            int weight = edge.second;
            
            // Push the new path to the priority queue for future exploration.
            // The new cost is the current path's cost plus the flight's weight.
            pq.push({cost + weight, neighbor});
        }
    }

    // The k cheapest routes to the destination city 'n' are now in dists[n].
    // The problem asks for them to be printed in increasing order.
    // The priority queue doesn't guarantee we find them in order, so we sort.
    sort(dists[n].begin(), dists[n].end());

    // Print the k cheapest costs
    for (int i = 0; i < k; ++i) {
        cout << dists[n][i] << (i == k - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}