#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> adj;
vector<int> parent;
vector<int> visited;
int cycleStart = -1, cycleEnd = -1;

bool dfs(int v, int p)
{
    visited[v] = 1;
    for (int nbr : adj[v])
    {
        if (nbr == p)
            continue; // Skip the parent
        if (visited[nbr] == 1)
        {
            // Found a cycle
            cycleStart = nbr;
            cycleEnd = v;
            return true;
        } else if (visited[nbr] == 0) 
        {

            parent[nbr] = v; // Set the parent only if not visited
            if (dfs(nbr, v))
                return true;
        }
    }

    visited[v] = 2;
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;

    adj.resize(n);
    parent.resize(n, -1);
    visited.resize(n, 0);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            if (dfs(i, -1))
            {
                break;
            }
        }
    }

    if (cycleStart == -1)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<int> cycle;

    cycle.push_back(cycleStart);
    for (int v = cycleEnd; v != cycleStart; v = parent[v])
    {
        cycle.push_back(v);
    }
    cycle.push_back(cycleStart);

    cout << cycle.size() << endl;
    for (int v : cycle)
    {
        cout << v + 1 << " ";
    }

    return 0;
}