#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class UnionFind
{
    vector<int> parent, rank;
    int numComponents;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 1);
        numComponents = n;
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int &x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            numComponents--;
        }
    }

    int getNumComponents() const
    {
        return numComponents;
    }
};

int main()
{
    int n, m;

    cin >> n >> m;

    UnionFind uf(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        uf.unite(u - 1, v - 1); // Convert to 0-indexed
    }

    if (uf.getNumComponents() == 1)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    int firstTeam = -1;
    for (int i = 0; i < n; i++)
    {
        int parent = uf.find(i);
        if (firstTeam == -1)
        {
            firstTeam = parent;
        }

        if (parent == firstTeam)
        {
            cout << "1 ";
        }
        else
        {
            cout << "2 ";
        }
    }

    cout << endl;

    return 0;
}