# Dynamic Programming

Dynamic programming problems focusing on optimal substructure and overlapping subproblems.

## Problems to Solve

1. Dice Combinations
2. Minimizing Coins
3. Coin Combinations I
4. Coin Combinations II
5. Removing Digits
6. Grid Paths
7. Book Shop
8. Array Description
9. Counting Towers
10. Edit Distance
11. Rectangle Cutting
12. Money Sums
13. Removal Game
14. Two Sets II
15. Increasing Subsequence
16. Projects
17. Elevator Rides
18. Counting Tilings
19. Counting Numbers

## Key Concepts
- Memoization
- Tabulation
- State space design
- Optimization problems
- Combinatorial DP
---

## ⭐ SUPER HARD Problems - REVISIT!

### Minimal Grid Path (Lexicographically Smallest)
**Files:** 
- `MinimalGridPath.cpp` - Suffix Ranking approach
- `MinimalGridPath_BFS.cpp` - BFS with Greedy Pruning (more intuitive!)

**Difficulty:** ⭐⭐⭐⭐⭐ SUPER HARD

**Two Approaches:**

#### Approach 1: BFS with Greedy Pruning ✅ (Recommended for interviews!)
- Process cells level by level (diagonal = row + col)
- At each level, find the MINIMUM character among reachable cells
- Keep ONLY cells with this minimum character (prune the rest)
- Uses visited array to avoid duplicates
- **Very intuitive and easy to implement!**

#### Approach 2: Suffix Ranking DP
- Assign integer RANKS to cells based on lexicographic order of paths
- Uses stable radix sort and diagonal processing
- More complex but equally efficient

**Complexity (both approaches):**
- Time: O(n²)
- Space: O(n²)

**Key Insight:**
Cells with larger characters at the same level can NEVER lead to the optimal path, so we can safely prune them!

**Resources:**
- CP-Algorithms: Suffix Array construction
- Competitive Programmer's Handbook: String algorithms chapter
- Codeforces blogs on "DP State Compression"

---

### Removal Game (Interval DP + Game Theory)
**Files:** `RemovalGame.cpp`, `RemovalGame.md`

**Difficulty:** ⭐⭐⭐⭐ (Medium-Hard)

See [RemovalGame.md](RemovalGame.md) for detailed SRTBOT breakdown and example walkthrough.