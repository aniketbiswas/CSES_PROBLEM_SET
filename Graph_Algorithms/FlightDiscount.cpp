#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    int m,n;

    cin >> n >> m;

    vector<vector<pair<int,long long>>> graph(n+1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>, greater<tuple<long long,int,int>>> pq;
    vector<vector<long long>> dist(n+1, vector<long long>(2, INF));
    dist[1][0] = 0;
    pq.emplace(0, 1, 0);

    while(!pq.empty()){
        auto [d, u, used_discount] = pq.top();
        pq.pop();

        if(d > dist[u][used_discount]) continue;

        for(auto &[v,w] : graph[u]) {

            if(d + w < dist[v][used_discount]) {
                dist[v][used_discount] = d + w;
                pq.emplace(dist[v][used_discount], v, used_discount);
            }

            if(!used_discount) {
                long long discounted_dist = d + w / 2;
                if(discounted_dist < dist[v][1]) {
                    dist[v][1] = discounted_dist;
                    pq.emplace(discounted_dist, v, 1);
                }
            }
        }
    }

    cout << (dist[n][0] == INF && dist[n][1] == INF ? -1 : min(dist[n][0], dist[n][1])) << endl;
    return 0;
}