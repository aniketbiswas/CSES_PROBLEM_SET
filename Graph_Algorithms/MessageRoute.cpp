#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>
#include <set>

using namespace std;


int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

   // bfs to find the shortest path from 1 to n
   vector<int> dist(n + 1, -1);
   dist[1] = 0;
   queue<int> q;
   q.push(1);

   while (!q.empty()) {
       int node = q.front();
       q.pop();

       for (int neighbor : adj[node]) {
           if (dist[neighbor] == -1) {
               dist[neighbor] = dist[node] + 1;
               q.push(neighbor);
           }
       }
   }

   if (dist[n] == -1) {
       cout << "IMPOSSIBLE";
   } else {
       cout << dist[n]+1;
   }

   cout << endl;


   // if a path exists, print the path using dfs
   vector<int> parent(n + 1, -1);
   for (int i = 1; i <= n; i++) {
       for (int neighbor : adj[i]) {
           if (dist[neighbor] == dist[i] + 1) {
               parent[neighbor] = i;
           }
       }
   }

   // reconstruct path from 1 to n
   if (parent[n] != -1) {
       vector<int> path;
       for (int at = n; at != -1; at = parent[at]) {
           path.push_back(at);
       }
       reverse(path.begin(), path.end());

       for (size_t i = 0; i < path.size(); i++) {
           cout << path[i] << " ";
       }
       cout << endl;
   }

   return 0;

}