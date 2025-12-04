# Greedy Algorithms with Multiset - Advanced Techniques

## Movie Festival 2 - Multi-Resource Scheduling

### Problem Statement
Given `n` movies (each with start and end time) and `k` people, find the maximum number of movies that can be watched in total. Each person can watch one movie at a time (no overlaps for same person). Different people can watch overlapping movies.

### Key Insights
1. **Extension of Movie Festival 1** (which had k=1 person)
2. **Greedy approach**: Sort by end time, then assign optimally
3. **Data structure choice**: Use `multiset` to efficiently track when each person becomes free
4. **Greedy choice**: Among available people, choose the one who became free most recently

### Algorithm Breakdown

#### Step 1: Sort Movies by End Time
```cpp
sort(movies.begin(), movies.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
    if(a.second == b.second)
        return a.first < b.first;  // Tie-breaking by start time
    return a.second < b.second;     // Primary: sort by end time
});
```

**Why sort by end time?** 
- Greedy principle: Process movies that free up people earliest
- Maximizes opportunities for future assignments

#### Step 2: Track People Availability with Multiset
```cpp
multiset<int> people;  // Stores when each person becomes free
for (int i = 0; i < k; i++) {
    people.insert(0);  // Initially all people free at time 0
}
```

**Why multiset?**
- Automatically maintains sorted order
- O(log k) insertion, deletion, and search
- Supports duplicate values (multiple people free at same time)

#### Step 3: The Critical Assignment Logic

```cpp
auto it = people.upper_bound(start);
if (it != people.begin()) {
    --it;                    // Get optimal person
    people.erase(it);        // Remove their current free time
    people.insert(end);      // Update to new free time
    totalCount++;
}
```

### Understanding `upper_bound()` Logic

#### What `people.upper_bound(start)` returns:
- Iterator to **first element > start**
- If no such element exists, returns `people.end()`

#### Case Analysis:

**Case 1: `it == people.begin()`**
```
people: [5, 7, 9]    start = 3
         ^
         it points here (5 > 3, and it's the first element)
```
- **Meaning**: ALL people become free AFTER movie starts
- **Action**: Skip this movie (no one available)

**Case 2: `it != people.begin()` (Normal case)**
```
people: [2, 5, 7]    start = 6
            ^
            it points here (7 > 6)
            --it points to 5 (person free at time 5 can watch movie starting at 6)
```
- **Meaning**: At least one person is free before movie starts
- **Action**: `--it` gives us person with maximum free_time ≤ start_time

**Case 3: `it == people.end()` (All people available)**
```
people: [1, 3, 5]    start = 8
               ^
               it points to end() (no element > 8)
               --it points to 5 (latest available person)
```
- **Meaning**: All people become free before movie starts
- **Action**: Choose person who became free latest

### Why This Greedy Choice Works

**Key Principle**: Among all available people, choose the one who became free **most recently**

**Intuition**: 
- Person who became free at time 5 vs person who became free at time 2
- Both can watch a movie starting at time 6
- Choose person at time 5 because:
  - Person at time 2 gives more flexibility for earlier future movies
  - We're processing movies in end-time order, so earlier availability is more valuable

### Complete Example Walkthrough

**Input**: n=4, k=2, movies: (1,3), (2,5), (6,8), (8,10)

**After sorting by end time**: (1,3), (2,5), (6,8), (8,10)

```
Initial: people = {0, 0}

Movie (1,3):
  - people = {0, 0}, start = 1
  - upper_bound(1) → end() (no element > 1)
  - it != begin() → true, --it points to last 0
  - Assign: people = {0, 3}, count = 1

Movie (2,5):
  - people = {0, 3}, start = 2
  - upper_bound(2) → points to 3
  - it != begin() → true, --it points to 0
  - Assign: people = {3, 5}, count = 2

Movie (6,8):
  - people = {3, 5}, start = 6
  - upper_bound(6) → end()
  - it != begin() → true, --it points to 5
  - Assign: people = {3, 8}, count = 3

Movie (8,10):
  - people = {3, 8}, start = 8
  - upper_bound(8) → end()
  - it != begin() → true, --it points to 8
  - Assign: people = {3, 10}, count = 4
```

**Answer**: 4 movies

### Time & Space Complexity
- **Time**: O(n log n) for sorting + O(n log k) for processing = **O(n log(n+k))**
- **Space**: **O(k)** for tracking people availability

### Related Problems & Variations
1. **Movie Festival 1**: Single person (k=1), simpler greedy
2. **Meeting Rooms II**: Same concept, different context
3. **Activity Selection with Multiple Resources**: General framework
4. **Job Scheduling with Multiple Machines**: Industrial application

### Key Takeaways for Future Problems
1. **Multiset for dynamic sorted collections** with duplicates
2. **upper_bound() technique** for finding "first element greater than X"
3. **Iterator arithmetic** for accessing adjacent elements safely
4. **Greedy choice in resource allocation**: Pick latest available resource
5. **Sort by end time** for interval scheduling problems

### Common Pitfalls to Avoid
1. Don't forget the `it != people.begin()` check
2. Remember that `upper_bound()` returns "first greater than", not "first greater or equal"
3. When using `--it`, ensure the iterator is decrementable
4. Consider tie-breaking in sort comparator for deterministic behavior

### Template Code Structure
```cpp
// 1. Sort intervals by end time
sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
    return a.second < b.second;
});

// 2. Track resource availability
multiset<int> resources;
for (int i = 0; i < k; i++) {
    resources.insert(0);
}

// 3. Greedy assignment
for (auto& interval : intervals) {
    auto it = resources.upper_bound(interval.first);
    if (it != resources.begin()) {
        --it;
        resources.erase(it);
        resources.insert(interval.second);
        count++;
    }
}
```

This pattern appears in many scheduling and resource allocation problems!