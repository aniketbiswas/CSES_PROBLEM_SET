#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;


int main () {
    int n,m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<pair<int,int>> q;
    pair<int,int> start, end = make_pair(-1,-1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if(grid[i][j] == 'M') {
                dist[i][j] = 0;
                q.push({i,j}); // push monster's position to the queue
                
            }
            if(grid[i][j] == 'A') {
                start = {i,j};
            }
        }
    }


    char arrow[4] = {'U', 'R', 'D', 'L'};
    int dir[5] = {-1, 0 , 1, 0 , -1};
   
    // first BFS to find position of monster at each timestamp

    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for(int i=0;i<4;i++) {
            int nx = x + dir[i];
            int ny = y + dir[i+1];
            if(nx>=0 && ny>=0 && nx<n && ny<m && grid[nx][ny] != '#' && dist[nx][ny] > dist[x][y] + 1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }

    }

    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
    // second BFS to find the shortest path from the start to the end
    q.push(start);
    dist[start.first][start.second] = 0;

    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        if(x == 0 || y == 0 || x == n-1 || y == m-1) {
            end = {x, y};
            break;
        }
        for(int i=0;i<4;i++) {
            int nx = x + dir[i];
            int ny = y + dir[i+1];
            if(nx>=0 && ny>=0 && nx<n && ny<m && grid[nx][ny] != '#' && grid[nx][ny] != 'M' && dist[nx][ny] > dist[x][y] + 1) {
                parent[nx][ny] = {x, y}; // store the position of the parent
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
                if(nx == 0 || ny == 0 || nx == n-1 || ny == m-1) {
                    end = {nx, ny};
                    break;
                }
            }
        }
    }

    if(end.first == -1) {
        cout<< "NO";
        return 0;
    } 

    // reconstruct the path from start to end
    cout<< "YES" << endl;
    string path;
    int x = end.first, y = end.second;
    do {
        auto [px, py] = parent[x][y];
        if(px < 0 || py < 0 || px >= n || py >= m) break;

        for(int i=0;i<4;i++) {
            if(px + dir[i] == x && py + dir[i+1] == y) {
                path += arrow[i];
                break;
            }
        }
        x = px;
        y = py;
    } while (x != start.first || y != start.second);

    cout << path.size() << endl;
    reverse(path.begin(), path.end());
    cout << path << endl;

    return 0;

}