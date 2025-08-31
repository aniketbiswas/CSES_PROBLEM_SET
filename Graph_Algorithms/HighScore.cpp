/*
 * CSES High Score Problem Solution
 * 
 * PROBLEM INTUITION:
 * We need to find the maximum score path from node 1 to node n in a directed graph.
 * This is equivalent to finding the shortest path with negated weights.
 * However, we must handle the case where there's a positive cycle that can be reached
 * from node 1 and from which we can reach node n - in this case, we can get infinite score.
 * 
 * ALGORITHM VISUAL:
 * 1. Convert max path problem to min path by negating all edge weights
 * 2. Use Bellman-Ford to detect negative cycles (originally positive cycles)
 * 3. Check if any negative cycle affects the path from 1 to n
 * 
 * EXAMPLE:
 * Original graph:     After negation:
 * 1 --+3--> 2        1 ---3--> 2
 * |         |        |         |
 * +2        +5       -2        -5
 * |         |        |         |
 * v         v        v         v
 * 3 --+4--> 4        3 ---4--> 4
 * 
 * If there's a positive cycle reachable from 1 and n is reachable from the cycle,
 * then we can achieve infinite score by looping in the cycle.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = 1e18;  // Large value representing infinity

int main() {
    // Read number of nodes (n) and edges (m)
    int n, m;
    cin >> n >> m;

    // Store all edges as (source, destination, weight)
    // KEY INSIGHT: We negate weights to convert "maximum path" to "minimum path"
    // This allows us to use Bellman-Ford algorithm for shortest paths
    vector<tuple<int,int,long long>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges[i] = make_tuple(u, v, -w);  // Negate weight for max->min conversion
    }

    /*
     * BELLMAN-FORD ALGORITHM PHASE 1: Find shortest distances
     * 
     * VISUAL REPRESENTATION:
     * Iteration 0: dist[1] = 0, all others = INF
     * Iteration 1: Update all neighbors of node 1
     * Iteration 2: Update neighbors of updated nodes from iteration 1
     * ...
     * After (n-1) iterations: All shortest paths found (if no negative cycles)
     * 
     * WHY (n-1) ITERATIONS?
     * In a graph with n nodes, the longest simple path has at most (n-1) edges.
     * So after (n-1) iterations, we're guaranteed to find all shortest paths.
     */
    vector<long long> dist(n + 1, INF);  // Distance array, initially all infinity
    dist[1] = 0;  // Starting node has distance 0

    // Standard Bellman-Ford: Relax all edges (n-1) times
    for (int i = 1; i <= n - 1; i++) {
        for (const auto& edge : edges) {
            auto [u, v, w] = edge;  // Destructure edge into source, dest, weight
            // Relaxation step: if we can reach u and going through u gives better path to v
            if (dist[u] != INF ) {
                dist[v] = min(dist[v], dist[u] + w);
            }
        }
    }

    // Check if destination node n is reachable from source node 1
    if (dist[n] == INF) {
        cout << -1 << "\n";  // Node n not reachable - no path exists
        return 0;
    }

    /*
     * BELLMAN-FORD PHASE 2: Detect and propagate negative cycles
     * 
     * INTUITION:
     * After (n-1) iterations, if we can still improve any distance,
     * it means there's a negative cycle. But we need to be more careful:
     * we only care about negative cycles that affect the path to node n.
     * 
     * VISUAL EXAMPLE:
     * If there's a negative cycle: A -> B -> C -> A (with total weight < 0)
     * and we can reach this cycle from node 1, and reach node n from this cycle,
     * then we can get infinite score by looping in the cycle.
     * 
     * ALGORITHM:
     * 1. Save current distances
     * 2. Run n more iterations to detect and mark all nodes affected by negative cycles
     * 3. If a negative cycle affects node n, return -1 (infinite score possible)
     */
    vector<long long> dist_copy = dist;  // Save original distances before cycle detection
    
    // Run additional n iterations to detect and propagate negative cycle effects
    for (int i = 1; i <= n; i++) {
        for (auto [u, v, w] : edges) {
            // If we can still improve distance to v, there's a negative cycle affecting it
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = -INF;  // Mark v as affected by negative cycle
            }
            // Propagate negative cycle marking: if u is in a cycle, so is v
            if (dist[u] == -INF) {
                dist[v] = -INF;  // Propagate cycle marking through the graph
            }
        }
    }

    /*
     * FINAL RESULT DETERMINATION:
     * 
     * Case 1: dist[n] == -INF
     *   Node n is affected by a negative cycle (originally positive cycle)
     *   This means we can achieve infinite score by using the cycle
     *   Return -1 to indicate infinite score is possible
     * 
     * Case 2: dist[n] != -INF  
     *   Node n is not affected by any negative cycle
     *   Return the maximum score = -(minimum distance with negated weights)
     *   We use dist_copy[n] which contains the distance before cycle detection
     */
    if (dist[n] == -INF) {
        cout << -1 << "\n";  // Infinite score possible due to positive cycle
    } else {
        // Convert back from minimum distance to maximum score by negating
        cout << -dist_copy[n] << "\n";  // Use original distance before cycle detection
    }

    return 0;
}