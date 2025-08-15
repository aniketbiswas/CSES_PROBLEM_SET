#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

class UnionFind
{
  vector<int> parent, rank;

public:
  UnionFind(int n)
  {
    parent.resize(n);
    rank.resize(n, 1);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int &x)
  {
    if (parent[x] != x)
    {
      parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
  }

  void unite(int x, int y)
  {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
    {
      if (rank[rootX] < rank[rootY])
      {
        parent[rootX] = rootY;
        rank[rootY] += rank[rootX];
      }
      else
      {
        parent[rootY] = rootX;
        rank[rootX] += rank[rootY];
      }
    }
  }

  void print()
  {
    // print number of unique components
    set<int> uniqueComponents;
    for (int i = 0; i < (int)parent.size(); ++i)
    {
      uniqueComponents.insert(find(i));
    }

    cout << uniqueComponents.size() - 1<< endl;
    if(uniqueComponents.size() <= 1) {
      return; // No edges needed if all nodes are already connected
    }

    // print edges required to connect these components sequentially
    auto it = uniqueComponents.begin();
    while (it != uniqueComponents.end())
    {
      int u = *it;
      ++it;
      if (it != uniqueComponents.end())
      {
        int v = *it;
        cout << u + 1 << ' ' << v + 1 << endl;
      }
    }
  }
};


int main() {
  int n, m;
  cin >> n >> m;

  UnionFind uf(n);
  for (int i = 0; i < m; ++i)
  {
    int u, v;
    cin >> u >> v;
    uf.unite(u - 1, v - 1);
  }

  uf.print();
  return 0;
}
