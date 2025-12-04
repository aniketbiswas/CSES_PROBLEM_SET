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

struct MaxFlow {
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> cap;

    explicit MaxFlow(int n) : n(n), adj(n), cap(n, vector<int>(n, 0)) {}

    void add_edge(int u, int v, int c = 1) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] += c;         // allow multiple edges to accumulate
    }

    int bfs(int s, int t, vector<int>& parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, int>> q;
        q.push({s, INT_MAX});

        while (!q.empty()) {
            auto [u, flow] = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (parent[v] == -1 && cap[u][v] > 0) {
                    parent[v] = u;
                    int new_flow = min(flow, cap[u][v]);
                    if (v == t) return new_flow;
                    q.push({v, new_flow});
                }
            }
        }
        return 0;
    }

    int edmonds_karp(int s, int t) {
        vector<int> parent(n);
        int total_flow = 0;
        while (int flow = bfs(s, t, parent)) {
            total_flow += flow;
            for (int v = t; v != s; v = parent[v]) {
                int u = parent[v];
                cap[u][v] -= flow;
                cap[v][u] += flow;
            }
        }
        return total_flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int boys, girls, k;
    cin >> boys >> girls >> k;

    const int source = 0;
    const int sink = boys + girls + 1;
    MaxFlow mf(sink + 1);

    // source → boys
    for (int b = 1; b <= boys; ++b) {
        mf.add_edge(source, b);
    }
    // girls → sink
    for (int g = 1; g <= girls; ++g) {
        mf.add_edge(boys + g, sink);
    }

    vector<vector<char>> seen(boys + 1, vector<char>(girls + 1, 0));
    vector<pair<int, int>> edges;
    edges.reserve(k);

    for (int i = 0; i < k; ++i) {
        int b, g;
        cin >> b >> g;
        if (!seen[b][g]) {
            seen[b][g] = 1;
            edges.emplace_back(b, g);
            mf.add_edge(b, boys + g);
        }
    }

    int total_matches = mf.edmonds_karp(source, sink);

    vector<pair<int, int>> matches;
    matches.reserve(total_matches);
    for (auto [b, g] : edges) {
        int u = b;
        int v = boys + g;
        // After flow, if reverse capacity (v -> u) > 0, edge carried flow
        if (mf.cap[v][u] > 0) {
            matches.emplace_back(b, g);
        }
    }

    cout << total_matches << '\n';
    for (auto [b, g] : matches) {
        cout << b << ' ' << g << '\n';
    }
    return 0;
}