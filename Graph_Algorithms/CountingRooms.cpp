#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int x, int y, vector<vector<char>>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    queue<pair<int, int>> q;
    int dir[5] = {-1, 0, 1, 0, -1};

    q.push({x, y});

    while(!q.empty()) {
        auto [startX, startY] = q.front();
        q.pop();

        for(int i=0; i<4; i++) {
            int a = startX + dir[i];
            int b = startY + dir[i+1];
            if(a>=0 && a<m && b>=0 && b<n && grid[a][b] == '.') {
                q.push({a, b});
                grid[a][b] = '#';
            }
        }
    }
}


int main() {
    int m , n ;
    cin >> m >> n;

    vector<vector<char>> grid(m,vector<char>(n, '-'));

    for(int i=0; i<m; i++) {
        for(int j=0;j<n; j++) {
            cin >> grid[i][j];
        }
    }

    int count = 0;
    for(int i=0; i<m; i++) {
        for(int j=0;j<n;j++) {
            if(grid[i][j] == '.'){
                bfs(i, j, grid);
                count++;

            }
        }
    }
    cout << count << endl;

    return 0;
}