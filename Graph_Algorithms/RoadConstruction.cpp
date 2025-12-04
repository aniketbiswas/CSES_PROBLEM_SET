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
#include <numeric>
using namespace std;

typedef long long ll;

class UnionFind {

    vector<int> size;
    vector<int> parent;
    int numComponents;
    int largestComponent;

public:
    UnionFind(int n) {
        size.resize(n,1);
        parent.resize(n);
        iota(parent.begin(),parent.end(),0);
        numComponents = n;
        largestComponent = 1;
    }

    int find(int &x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    bool join(int &x , int &y){
        
        int parX = find(x);
        int parY = find(y);

        if(parX == parY )return false;

        if(size[parX] >= size[parY]){
            parent[parY] = parX;
            size[parX]+=size[parY];
            largestComponent = max(largestComponent,size[parX]);
        } else {
            parent[parX] = parY;
            size[parY]+=size[parX];
            largestComponent = max(largestComponent,size[parY]);
        }

        numComponents--;
        return true;
    }


    vector<int> response() {
        return {numComponents,largestComponent};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m,n;

    cin >> n >> m;

    UnionFind uf(n);

    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        x--;y--;

        uf.join(x,y);

        vector<int> resp = uf.response();
        cout<< resp[0]<<' '<< resp[1]<<endl;
    }
    
    
    return 0;
}