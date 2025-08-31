# Sorting and Searching

This section focuses on array manipulation, binary search, greedy algorithms, and efficient data structures.

## Progress: 6/35 ✅

## Key Concepts
- **Sorting Algorithms**: Built-in sort, custom comparators
- **Binary Search**: Lower/upper bound, custom search predicates
- **Two Pointers**: Efficient array traversal techniques
- **Greedy Algorithms**: Optimal choice strategies
- **Data Structures**: Set, multiset, priority queue
- **Time Complexity**: Optimization from O(n²) to O(n log n)

## Solved Problems

### Basic Sorting and Counting
- ✅ **Distinct Numbers** (`DistinctNumCount.cpp`) - Count unique elements using set
- ✅ **Apartments** (`Apartments.cpp`) - Assignment problem with sorting
- ✅ **Ferris Wheel** (`FerrisWheel.cpp`) - Two pointers optimization

### Binary Search and Data Structures  
- ✅ **Concert Tickets** (`ConcertTickets.cpp`) - Upper bound with multiset
- ✅ **Josephus Problem I** (`JosephusProblem1.cpp`) - Simulation with queue
- ✅ **Josephus Problem II** (`JosephusProblem2.cpp`) - Advanced Josephus variant

## Algorithm Patterns

### Two Pointers Technique
Used in problems like Ferris Wheel and Sum of Two Values:
```cpp
int left = 0, right = n - 1;
while (left < right) {
    if (arr[left] + arr[right] == target) {
        // Found solution
    } else if (arr[left] + arr[right] < target) {
        left++;
    } else {
        right--;
    }
}
```

### Binary Search on Answer
Pattern for optimization problems where we can check if a solution is feasible:
```cpp
int low = 0, high = MAX_ANSWER;
while (low < high) {
    int mid = (low + high) / 2;
    if (canAchieve(mid)) {
        high = mid;
    } else {
        low = mid + 1;
    }
}
```

## Remaining Problems (29/35)
- [ ] Restaurant Customers
- [ ] Movie Festival
- [ ] Sum of Two Values
- [ ] Maximum Subarray Sum
- [ ] Stick Lengths
- [ ] Playlist
- [ ] Towers
- [ ] Traffic Lights
- [ ] Room Allocation
- [ ] Factory Machines
- [ ] Tasks and Deadlines
- [ ] Reading Books
- [ ] Sum of Three Values
- [ ] Sum of Four Values
- [ ] Nearest Smaller Values
- [ ] Subarray Sums I & II
- [ ] Subarray Divisibility
- [ ] Array Division
- [ ] Sliding Window Median
- [ ] Sliding Window Cost
- [ ] Movie Festival II
- [ ] Maximum Subarray Sum II
