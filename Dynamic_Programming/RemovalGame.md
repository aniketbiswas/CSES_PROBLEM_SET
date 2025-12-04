# Removal Game (Interval DP + Game Theory)

**File:** `RemovalGame.cpp`

**Difficulty:** ⭐⭐⭐⭐ (Medium-Hard)

**Problem:** Two players alternately remove either the first or last element from a list, adding it to their score. Both play optimally. Find the maximum score for Player 1.

---

## SRTBOT Framework

### S - Subproblem

`dp[i][j]` = maximum score the **current player** can achieve when the remaining elements are the subarray from index `i` to `j`.

- Subproblems: O(n²) intervals

---

### R - Relation (Recurrence)

```
dp[i][j] = max(
    x[i] + sum(i+1, j) - dp[i+1][j],   // take left
    x[j] + sum(i, j-1) - dp[i][j-1]    // take right
)
```

**Key insight:** If you take `x[i]`, opponent gets `dp[i+1][j]` from remaining interval. You get the rest: `sum(i+1,j) - dp[i+1][j]`.

---

### T - Topological Order

Fill by **increasing interval length** (len = 1, 2, ..., n). 

This ensures smaller intervals are computed before larger ones.

```
Length 1: dp[0][0], dp[1][1], ..., dp[n-1][n-1]
Length 2: dp[0][1], dp[1][2], ..., dp[n-2][n-1]
Length 3: dp[0][2], dp[1][3], ...
...
Length n: dp[0][n-1]
```

---

### B - Base Case

```
dp[i][i] = x[i]
```

Single element — current player takes it.

---

### O - Original Problem

```
Answer = dp[0][n-1]
```

Maximum score for Player 1 when the full array is available.

---

### T - Time Complexity

- **Time:** O(n²)
- **Space:** O(n²) for DP table + O(n) for prefix sums

---

## Example Walkthrough: `[4, 5, 1, 3]`

### DP Table Structure

We fill the upper triangle (where i ≤ j):

```
     j=0   j=1   j=2   j=3
i=0   4     5     5     8  ← answer
i=1   -     5     5     6
i=2   -     -     1     3
i=3   -     -     -     3
```

### Step-by-Step Computation

| len | Interval | Calculation | Result |
|-----|----------|-------------|--------|
| 1 | [4] | base case | dp[0][0] = 4 |
| 1 | [5] | base case | dp[1][1] = 5 |
| 1 | [1] | base case | dp[2][2] = 1 |
| 1 | [3] | base case | dp[3][3] = 3 |
| 2 | [4,5] | max(4+5-5, 5+4-4) = max(4,5) | dp[0][1] = 5 |
| 2 | [5,1] | max(5+1-1, 1+5-5) = max(5,1) | dp[1][2] = 5 |
| 2 | [1,3] | max(1+3-3, 3+1-1) = max(1,3) | dp[2][3] = 3 |
| 3 | [4,5,1] | max(4+6-5, 1+9-5) = max(5,5) | dp[0][2] = 5 |
| 3 | [5,1,3] | max(5+4-3, 3+6-5) = max(6,4) | dp[1][3] = 6 |
| 4 | [4,5,1,3] | max(4+9-6, 3+10-5) = max(7,8) | dp[0][3] = **8** ✓ |

---

## Key Technique: Minimax via Subtraction

Instead of alternating max/min for each player, we **always maximize** but subtract the opponent's optimal score from the remaining pool.

Both players use the same recurrence — the "current player" perspective handles the alternation automatically!

**Why it works:**
- Total sum of interval `[i,j]` is fixed
- If opponent gets `dp[...]`, you get `sum - dp[...]`
- No need for separate "player 1" and "player 2" states
