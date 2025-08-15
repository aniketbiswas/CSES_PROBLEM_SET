#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Global variables for cleaner code
bool visited[7][7];
int total_paths = 0;

// Check if a position is valid and not visited
bool isValid(int x, int y) {
    return x >= 0 && x < 7 && y >= 0 && y < 7 && !visited[x][y];
}

void dfs(const string& path, int step, int x, int y) {
    // Base case: completed all 48 steps
    if (step == 48) {
        // Check if we reached the destination (6, 0)
        if (x == 6 && y == 0) {
            total_paths++;
        }
        return;
    }
    
    // Early termination: reached destination before completing all steps
    if (x == 6 && y == 0) {
        return;
    }
    
    // Mark current position as visited
    visited[x][y] = true;
    
    // Optimization: avoid splitting into disconnected regions
    // If we can only go up/down but not left/right (or vice versa), it's likely a dead end
    bool canUp = isValid(x - 1, y);
    bool canDown = isValid(x + 1, y);
    bool canLeft = isValid(x, y - 1);
    bool canRight = isValid(x, y + 1);
    
    // Pruning: if we're forced into a "corridor" that splits the unvisited area
    if ((canUp && canDown && !canLeft && !canRight) || 
        (!canUp && !canDown && canLeft && canRight)) {
        visited[x][y] = false;
        return;
    }
    
    char direction = path[step];
    
    if (direction == '?') {
        // Try all four directions
        if (canUp) dfs(path, step + 1, x - 1, y);      // Up
        if (canRight) dfs(path, step + 1, x, y + 1);   // Right  
        if (canDown) dfs(path, step + 1, x + 1, y);    // Down
        if (canLeft) dfs(path, step + 1, x, y - 1);    // Left
    } else {
        // Fixed direction
        if (direction == 'U' && canUp) {
            dfs(path, step + 1, x - 1, y);
        } else if (direction == 'R' && canRight) {
            dfs(path, step + 1, x, y + 1);
        } else if (direction == 'D' && canDown) {
            dfs(path, step + 1, x + 1, y);
        } else if (direction == 'L' && canLeft) {
            dfs(path, step + 1, x, y - 1);
        }
        // If the fixed direction is blocked, this path is invalid (no recursive call)
    }
    
    // Backtrack: unmark current position
    visited[x][y] = false;
}

int main() {
    string path;
    cin >> path;
    
    // Initialize visited array
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            visited[i][j] = false;
        }
    }
    
    // Start DFS from top-left corner (0, 0)
    total_paths = 0;
    dfs(path, 0, 0, 0);
    
    cout << total_paths << endl;
    return 0;
}