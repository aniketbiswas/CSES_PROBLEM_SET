#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int m, n;
    cin >> m >> n;

    pair<int, int> start,end;
    vector<vector<char>> grid(m, vector<char>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if(grid[i][j] == 'A') {
                start = {i, j};
            }
            if(grid[i][j] == 'B') {
                end = {i, j};
            }
        }
    }

    queue<pair<int, int>> q;
    q.push(start);
    vector<vector<int>> dist(m, vector<int>(n, -1));
    dist[start.first][start.second] = 0;

    int dir[5] = {-1, 0, 1, 0, -1};
    // LRUD = U , R , D , L
    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        // cout<<q.size() << " " << x << " " << y << endl;
        for(int i=0; i<4; i++) {
            int a = x + dir[i];
            int b = y + dir[i+1];
            if(a>=0 && a<m && b>=0 && b<n && grid[a][b] != '#' && dist[a][b] == -1) {
                dist[a][b] = dist[x][y] + 1;
                q.push({a, b});
            }
        }
    }


    if(dist[end.first][end.second] == -1){
     cout<< "NO";
        return 0;
    }

    cout<< "YES"<<endl;
    cout << dist[end.first][end.second] << endl;

    // for path as L, R, U, D
    vector<char> path;
    pair<int, int> curr = end;
    while (curr != start) {
        for (int i = 0; i < 4; i++) {
            int a = curr.first + dir[i];
            int b = curr.second + dir[i+1];
            if (a >= 0 && a < m && b >= 0 && b < n && dist[a][b] == dist[curr.first][curr.second] - 1) {
                curr = {a, b};
                path.push_back("URDL"[i]);
                break;
            }
        }
    }

    reverse(path.begin(), path.end());
    for (char c : path) {
        // reverse direction LRUD -> RLDU
        cout << "RLDU"[string("LRUD").find(c)] ;
    }

    cout << endl;

    return 0;
}