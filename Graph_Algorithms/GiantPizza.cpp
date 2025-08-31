#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> gr, grt; // original and transpose graphs
vector<bool> used;
vector<int> order, comp;

void dfs1(int v) {
    used[v] = true;
    for (int u : gr[v]) {
        if (!used[u]) {
            dfs1(u);
        }
    }
    order.push_back(v);
}

void dfs2(int v, int color) {
    comp[v] = color;
    for (int u : grt[v]) {
        if (comp[u] == -1) {
            dfs2(u, color);
        }
    }
}

void addImplication(int a, int b) {
    gr[a].push_back(b);
    grt[b].push_back(a);
}

void addClause(int a, bool va, int b, bool vb) {
    // Convert to 0-indexed nodes
    // If va is true, use 2*a (positive), else use 2*a+1 (negative)
    int node_a = 2 * a + (va ? 0 : 1);
    int node_b = 2 * b + (vb ? 0 : 1);
    int not_a = 2 * a + (va ? 1 : 0);
    int not_b = 2 * b + (vb ? 1 : 0);
    
    addImplication(not_a, node_b); // !a -> b
    addImplication(not_b, node_a); // !b -> a
}

bool solveTwoSAT(int n) {
    // Initialize global vectors
    used.assign(2 * n, false);
    order.clear();
    
    // First DFS to get finishing times (Kosaraju's step 1)
    for (int i = 0; i < 2 * n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    
    // Second DFS on transpose graph in reverse order (Kosaraju's step 2)
    comp.assign(2 * n, -1);
    int color = 0;
    
    for (int i = 2 * n - 1; i >= 0; i--) {
        int v = order[i];
        if (comp[v] == -1) {
            dfs2(v, color++);
        }
    }
    
    // Check if any variable and its negation are in same SCC
    for (int i = 0; i < n; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) {
            return false; // Unsatisfiable
        }
    }
    
    return true;
}

vector<bool> getAssignment(int n) {
    vector<bool> assignment(n);
    for (int i = 0; i < n; i++) {
        // Assign truth value based on SCC order
        // If positive literal has higher SCC number, assign true
        assignment[i] = comp[2 * i] > comp[2 * i + 1];
    }
    return assignment;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    // Initialize graphs
    gr.assign(2 * m, vector<int>());
    grt.assign(2 * m, vector<int>());
    
    // Read family member wishes and build 2-SAT clauses
    for (int i = 0; i < n; i++) {
        char sign1, sign2;
        int x, y;
        cin >> sign1 >> x >> sign2 >> y;
        x--; y--; // Convert to 0-indexed
        
        bool val1 = (sign1 == '+');
        bool val2 = (sign2 == '+');
        
        // Add clause: wish1 OR wish2
        addClause(x, val1, y, val2);
    }
    
    // Solve 2-SAT using Kosaraju's algorithm
    if (solveTwoSAT(m)) {
        vector<bool> assignment = getAssignment(m);
        for (int i = 0; i < m; i++) {
            cout << (assignment[i] ? '+' : '-');
            if (i < m - 1) cout << ' ';
        }
        cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }
    
    return 0;
}