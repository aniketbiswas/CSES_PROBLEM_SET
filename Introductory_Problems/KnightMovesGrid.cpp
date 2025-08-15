#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

/*
There is a knight on an n \times n chessboard. For each square, print the minimum number of moves the knight needs to do to reach the top-left corner.
Input
The only line has an integer n.
Output
Print the number of moves for each square.
Constraints

4 \le n \le 1000
*/

int main() {
    int n;
    cin >> n;

    vector<vector<int>> moves(n, vector<int>(n, -1));

    // BFS to find the minimum moves for each square
    queue<pair<int, int>> q;
    q.push({0, 0});
    moves[0][0] = 0;

    vector<pair<int, int>> directions = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (const auto& [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && moves[nx][ny] == -1) {
                moves[nx][ny] = moves[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    for (const auto& row : moves) {
        for (int move : row) {
            cout << move << " ";
        }
        cout << "\n";
    }

    return 0;
}