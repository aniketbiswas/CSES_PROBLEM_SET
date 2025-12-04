/*
 * ============================================================================
 * LEXICOGRAPHICALLY MINIMAL GRID PATH
 * ============================================================================
 * 
 * DIFFICULTY: ⭐⭐⭐⭐⭐ SUPER HARD - REVISIT THIS PROBLEM!
 * 
 * Pattern: Suffix Ranking DP Optimization
 * Similar to: Suffix Array construction
 * 
 * ============================================================================
 * PROBLEM:
 * ============================================================================
 * Given an n×n grid of letters (A-Z), find the lexicographically smallest
 * string by moving from top-left (0,0) to bottom-right (n-1,n-1).
 * You can only move RIGHT or DOWN.
 * 
 * Example:
 *   AACA
 *   BABC
 *   ABDA
 *   AACA
 * 
 *   Answer: AAABACA (path: A→A→A→B→A→C→A)
 * 
 * ============================================================================
 * WHY IS THIS HARD?
 * ============================================================================
 * 
 * NAIVE APPROACH (what most people think first):
 *   - Store the entire string at each cell in a 2D DP table
 *   - dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
 *   - Problem: Each string has length O(n), so space is O(n³) - TOO MUCH!
 * 
 * THE KEY INSIGHT:
 *   - We don't need to store entire strings!
 *   - We only need to know: "Is path A lexicographically smaller than path B?"
 *   - We can encode this comparison ability into a single integer "RANK"
 * 
 * ============================================================================
 * THE BRILLIANT IDEA: SUFFIX RANKING
 * ============================================================================
 * 
 * Think about it this way:
 *   - Two paths from cell (i,j) to the end are EQUIVALENT if they produce
 *     the same string suffix
 *   - We assign a RANK to each cell: lower rank = lexicographically smaller path
 * 
 * How to compute ranks?
 *   - Process cells in REVERSE order (from destination back to start)
 *   - For each cell, its "signature" is: (its_character, best_rank_it_can_reach)
 *   - Cells with the SAME signature get the SAME rank
 *   - Cells with DIFFERENT signatures get DIFFERENT ranks
 * 
 * WHY DIAGONALS?
 *   - All cells on the same diagonal have the same distance to destination
 *   - So paths from them have the same LENGTH
 *   - We can compare them fairly!
 * 
 * ============================================================================
 * ALGORITHM WALKTHROUGH:
 * ============================================================================
 * 
 * Step 1: Process diagonals from bottom-right to top-left
 *         (diagonal d = cells where row + col = d)
 * 
 * Step 2: For each cell on current diagonal:
 *         - Look at neighbors (down and right) - these are on the NEXT diagonal
 *         - Pick the neighbor with the SMALLER rank (better path)
 *         - Create signature: (my_character, best_neighbor_rank)
 * 
 * Step 3: Sort all cells on this diagonal by their signatures
 *         - Use STABLE sort so equal elements keep their order
 *         - Assign ranks: same signature = same rank, different = different
 * 
 * Step 4: After processing all diagonals, reconstruct the path
 *         - Start at (0,0)
 *         - At each step, pick neighbor with smallest (character, rank)
 * 
 * ============================================================================
 * COMPLEXITY:
 * ============================================================================
 *   Time:  O(n²) - each cell processed once
 *   Space: O(n²) - only store one integer rank per cell!
 * 
 * Compare to naive: O(n³) space for storing strings
 * 
 * ============================================================================
 * RESOURCES TO LEARN MORE:
 * ============================================================================
 *   - CP-Algorithms: Suffix Array construction (similar ranking idea)
 *   - Competitive Programmer's Handbook: String algorithms chapter
 *   - Codeforces blogs on "DP State Compression"
 * 
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;

/*
 * STABLE COUNTING SORT
 * ====================
 * 
 * What is it?
 *   A sorting algorithm that:
 *   1. Counts how many times each value appears
 *   2. Uses counts to place elements in correct positions
 *   3. STABLE: equal elements stay in their original relative order
 * 
 * Why stable?
 *   We sort by TWO keys: (character, rank)
 *   By sorting by rank first, then by character (both stable),
 *   we get a sort by the pair (character, rank).
 *   This is called RADIX SORT.
 * 
 * Parameters:
 *   cells - vector of cells, each cell is {character, nextRank, row, col}
 *   keyIndex - which index to sort by (0 = character, 1 = nextRank)
 */
static void stableCountingSort(vector<array<int,4>>& cells, int keyIndex) {
    if (cells.empty()) return;
    
    // Step 1: Find the minimum and maximum values for this key
    // We need this to create a count array of the right size
    int minValue = cells[0][keyIndex];
    int maxValue = cells[0][keyIndex];
    for (int i = 1; i < (int)cells.size(); ++i) {
        minValue = min(minValue, cells[i][keyIndex]);
        maxValue = max(maxValue, cells[i][keyIndex]);
    }
    
    // Step 2: Create count array
    // count[v] will tell us how many elements have value < v
    int rangeSize = maxValue - minValue + 1;
    vector<int> count(rangeSize + 1, 0);
    
    // Count occurrences of each value
    for (auto& cell : cells) {
        count[cell[keyIndex] - minValue + 1]++;
    }
    
    // Convert to cumulative counts (prefix sums)
    // After this, count[v] = number of elements with value < (v + minValue)
    for (int i = 1; i <= rangeSize; ++i) {
        count[i] += count[i - 1];
    }
    
    // Step 3: Place elements in sorted order
    // We go through original array and place each element at its correct position
    vector<array<int,4>> sortedCells(cells.size());
    for (auto& cell : cells) {
        int position = count[cell[keyIndex] - minValue]++;
        sortedCells[position] = cell;
    }
    
    cells.swap(sortedCells);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // ========================================================================
    // READ INPUT
    // ========================================================================
    int numRows;
    if (!(cin >> numRows)) return 0;
    
    vector<string> grid(numRows);
    for (int i = 0; i < numRows; ++i) {
        cin >> grid[i];
    }
    int numCols = numRows > 0 ? grid[0].size() : 0;
    
    // ========================================================================
    // INITIALIZE RANK TABLE
    // ========================================================================
    // rank[i][j] = lexicographic rank of the best path from (i,j) to destination
    // Lower rank = lexicographically smaller path
    // INF = "not computed yet" or "unreachable"
    
    const int INF = 1e9 + 7;
    vector<vector<int>> rank(numRows, vector<int>(numCols, INF));
    
    // ========================================================================
    // PROCESS DIAGONALS (from bottom-right to top-left)
    // ========================================================================
    // 
    // What is a diagonal?
    //   All cells where (row + col) = constant
    // 
    // Example for 4x4 grid:
    //   Diagonal 0: (0,0)
    //   Diagonal 1: (0,1), (1,0)
    //   Diagonal 2: (0,2), (1,1), (2,0)
    //   ...
    //   Diagonal 6: (3,3)
    // 
    // Why process in reverse?
    //   Because rank[i][j] depends on rank[i+1][j] and rank[i][j+1]
    //   (the cells we can move TO)
    //   So we need to compute those first!
    
    int maxDiagonal = numRows + numCols - 2;  // diagonal of bottom-right corner
    
    for (int diagonal = maxDiagonal; diagonal >= 0; --diagonal) {
        
        // Collect all cells on this diagonal
        // cells[k] = {character, bestNextRank, row, col}
        vector<array<int,4>> cellsOnDiagonal;
        
        // Calculate which rows are on this diagonal
        // row + col = diagonal, so col = diagonal - row
        // col must be in [0, numCols-1], so:
        //   0 <= diagonal - row <= numCols - 1
        //   diagonal - numCols + 1 <= row <= diagonal
        int minRow = max(0, diagonal - (numCols - 1));
        int maxRow = min(numRows - 1, diagonal);
        
        for (int row = minRow; row <= maxRow; ++row) {
            int col = diagonal - row;
            
            // What's the best rank we can reach from this cell?
            // We can go DOWN to (row+1, col) or RIGHT to (row, col+1)
            int rankFromBelow = (row + 1 < numRows) ? rank[row + 1][col] : INF;
            int rankFromRight = (col + 1 < numCols) ? rank[row][col + 1] : INF;
            int bestNextRank = min(rankFromBelow, rankFromRight);
            
            // Special case: destination cell
            // It has no "next" cell, so we give it a special marker rank of -1
            if (row == numRows - 1 && col == numCols - 1) {
                bestNextRank = -1;
            }
            
            // Store: {character_at_cell, best_reachable_rank, row, col}
            cellsOnDiagonal.push_back({
                (int)grid[row][col],  // character (as int for sorting)
                bestNextRank,          // best rank we can reach from here
                row,                   // row coordinate (to update rank table later)
                col                    // col coordinate
            });
        }
        
        // ====================================================================
        // SORT BY (character, bestNextRank) using stable radix sort
        // ====================================================================
        // 
        // Why sort?
        //   Cells with the same (character, bestNextRank) produce equivalent paths
        //   They should get the SAME rank
        // 
        // How radix sort works:
        //   1. Sort by SECONDARY key first (bestNextRank)
        //   2. Then sort by PRIMARY key (character)
        //   Because both sorts are STABLE, equal elements from step 2
        //   remain sorted by the secondary key from step 1
        
        stableCountingSort(cellsOnDiagonal, 1);  // Sort by bestNextRank (secondary)
        stableCountingSort(cellsOnDiagonal, 0);  // Sort by character (primary)
        
        // ====================================================================
        // ASSIGN RANKS
        // ====================================================================
        // 
        // After sorting, cells with same (char, nextRank) are adjacent
        // We assign the same rank to cells with identical signatures
        // Different signatures get incrementing ranks
        
        int currentRank = -1;
        for (int k = 0; k < (int)cellsOnDiagonal.size(); ++k) {
            // Check if this cell has a different signature than the previous one
            bool isNewSignature = (k == 0) ||                                    // first cell always starts new group
                                  (cellsOnDiagonal[k][0] != cellsOnDiagonal[k-1][0]) ||  // different character
                                  (cellsOnDiagonal[k][1] != cellsOnDiagonal[k-1][1]);    // different bestNextRank
            
            if (isNewSignature) {
                ++currentRank;
            }
            
            // Update the rank table
            int row = cellsOnDiagonal[k][2];
            int col = cellsOnDiagonal[k][3];
            rank[row][col] = currentRank;
        }
    }
    
    // ========================================================================
    // RECONSTRUCT THE PATH
    // ========================================================================
    // 
    // Now rank[i][j] tells us how "good" the path from (i,j) is
    // Starting from (0,0), at each step we greedily pick the neighbor with:
    //   1. Smallest character (most important)
    //   2. If tie, smallest rank (tiebreaker)
    
    string result;
    int currentRow = 0, currentCol = 0;
    result.push_back(grid[currentRow][currentCol]);
    
    while (currentRow != numRows - 1 || currentCol != numCols - 1) {
        // Find the best next move
        char bestChar = (char)127;  // larger than any letter
        int bestRank = INT_MAX;
        int nextRow = currentRow, nextCol = currentCol;
        
        // Option 1: Move DOWN (if possible)
        if (currentRow + 1 < numRows) {
            char downChar = grid[currentRow + 1][currentCol];
            int downRank = rank[currentRow + 1][currentCol];
            
            // Is this better than our current best?
            // Compare as pair: (character, rank)
            if (make_pair(downChar, downRank) < make_pair(bestChar, bestRank)) {
                bestChar = downChar;
                bestRank = downRank;
                nextRow = currentRow + 1;
                nextCol = currentCol;
            }
        }
        
        // Option 2: Move RIGHT (if possible)
        if (currentCol + 1 < numCols) {
            char rightChar = grid[currentRow][currentCol + 1];
            int rightRank = rank[currentRow][currentCol + 1];
            
            if (make_pair(rightChar, rightRank) < make_pair(bestChar, bestRank)) {
                bestChar = rightChar;
                bestRank = rightRank;
                nextRow = currentRow;
                nextCol = currentCol + 1;
            }
        }
        
        // Make the move
        currentRow = nextRow;
        currentCol = nextCol;
        result.push_back(grid[currentRow][currentCol]);
    }
    
    cout << result << '\n';
    return 0;
}
