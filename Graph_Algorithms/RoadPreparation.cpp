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
#include <unordered_set>
using namespace std;

typedef long long ll;

/*
 * CSES - Road Reparation (Problem 1675)
 * 
 * PROBLEM: Given n cities and m roads with repair costs, find minimum cost 
 * to repair roads so that all cities are connected (Minimum Spanning Tree)
 * 
 * ALGORITHM: Prim's Algorithm
 * 1. Start with arbitrary vertex (vertex 0)
 * 2. Maintain priority queue of edges from current MST to remaining vertices
 * 3. Always pick minimum weight edge that connects MST to new vertex
 * 4. Repeat until all vertices are included
 * 
 * TIME COMPLEXITY: O((V + E) log V) with priority queue
 * SPACE COMPLEXITY: O(V + E)
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m , n;

    cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n);
    for(int i=0;i<m;i++){
        int u , v;
        ll cost;
        cin >> u >> v >> cost;
        u--;v--;
        adj[u].push_back({v,cost});
        adj[v].push_back({u,cost});
    }

    unordered_set<int> visited;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    pq.push({0,0});
    ll total_cost = 0LL;
    while(!pq.empty() && visited.size()<n){
        auto [cost,u] = pq.top();
        pq.pop();
        if(visited.find(u)!=visited.end()) continue;
        visited.insert(u);
        total_cost += cost;
        for(auto &[v,c]:adj[u]){
            if(visited.find(v)==visited.end()){
                pq.push({c,v});
            }
        }
    }

    if(visited.size()<n){
        cout << "IMPOSSIBLE\n";
    } else {
        cout << total_cost << "\n";
    }
    
    return 0;
}