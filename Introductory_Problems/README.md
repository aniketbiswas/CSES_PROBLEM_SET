# Introductory Problems

This section contains basic algorithmic thinking and implementation problems.

## Progress: 20/19 ✅ (Extra problems solved!)

## Key Concepts
- **Basic Mathematics**: Number theory, combinatorics
- **String Manipulation**: Palindromes, permutations
- **Bit Manipulation**: Powers of 2, binary representations
- **Pattern Recognition**: Spiral patterns, mathematical sequences
- **Greedy Algorithms**: Simple optimization problems
- **Recursive Thinking**: Problem decomposition

## Solved Problems

### Mathematical Problems
- ✅ **Weird Algorithm** (`WeirdAlgo.cpp`) - Collatz conjecture simulation
- ✅ **Missing Number** (`MissingNumber.cpp`) - Arithmetic series property
- ✅ **Number Spiral** (`NumberSpiral.cpp`) - Pattern recognition in 2D
- ✅ **Two Knights** (`TwoKnights.cpp`) - Combinatorial counting
- ✅ **Bit Strings** (`BitString.cpp`) - Powers of 2 (2^n)
- ✅ **Trailing Zeros** (`TrailingZeros.cpp`) - Prime factorization in factorial
- ✅ **Coin Piles** (`CoinPiles.cpp`) - Mathematical constraints

### String and Array Problems
- ✅ **Repetitions** (`Repititions.cpp`) - Longest substring of same character
- ✅ **Increasing Array** (`IncreasingArray.cpp`) - Greedy array modification
- ✅ **Permutations** (`BeautifulPermutation.cpp`) - Valid permutation construction
- ✅ **Two Sets** (`TwoSets.cpp`, `TwoSets.rb`) - Partition problem
- ✅ **Palindrome Reorder** (`ReorderPalindrome.cpp`) - String rearrangement
- ✅ **Gray Code** (`GrayCode.cpp`) - Binary sequence generation

### Advanced/Extra Problems Solved
- ✅ **Creating Strings** (`CreatingString.cpp`) - String permutations  
- ✅ **Apple Division** (`AppleDivision.cpp`) - Subset sum optimization
- ✅ **Digit Queries** (`DigitQueries.cpp`) - Number sequence analysis
- ✅ **Grid Paths** (`GridPathDescription.cpp`) - Path counting
- ✅ **String Reorder** (`StringReorder.cpp`) - String manipulation
- ✅ **Knight Moves Grid** (`KnightMovesGrid.cpp`) - Chess movement
- ✅ **Grid Coloring** (`GridColoring1.cpp`) - Pattern problems

## Algorithm Patterns

### Mathematical Formula Recognition
Many problems have elegant mathematical solutions:
```cpp
// Trailing zeros in n! = count of factor 5
int trailingZeros(int n) {
    int count = 0;
    while (n >= 5) {
        count += n / 5;
        n /= 5;
    }
    return count;
}
```

### Greedy Strategy
Simple optimization often works:
```cpp
// Make array increasing with minimum moves
long long moves = 0;
for (int i = 1; i < n; i++) {
    if (arr[i] < arr[i-1]) {
        moves += arr[i-1] - arr[i];
        arr[i] = arr[i-1];
    }
}
```

## Notes
- All 19 official problems completed ✅
- Extra problems from extended practice sets also solved
- Solutions emphasize clean, readable code
- Multiple language implementations for some problems (C++, Ruby)
