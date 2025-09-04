# Sorting and Searching

This section focuses on array manipulation, binary search, greedy algorithms, and efficient data structures.

## Progress: 16/35 ✅

## Key Concepts
- **Sorting Algorithms**: Built-in sort, custom comparators
- **Binary Search**: Lower/upper bound, custom search predicates
- **Two Pointers**: Efficient array traversal techniques
- **Greedy Algorithms**: Optimal choice strategies
- **Data Structures**: Set, multiset, priority queue, sliding window
- **Advanced Patterns**: Coordinate compression, sweep line algorithms

## Solved Problems

### Basic Sorting and Counting
- ✅ **Distinct Numbers** (`DistinctNumCount.cpp`) - Count unique elements using set
- ✅ **Apartments** (`Apartments.cpp`) - Assignment problem with sorting
- ✅ **Ferris Wheel** (`FerrisWheel.cpp`) - Two pointers optimization

### Binary Search and Data Structures  
- ✅ **Concert Tickets** (`ConcertTickets.cpp`) - Upper bound with multiset
- ✅ **Sum of Two Values** (`SumOfTwoValues.cpp`) - Two pointers after sorting
- ✅ **Towers** (`Towers.cpp`) - Greedy with binary search (LIS variant)

### Greedy Algorithms
- ✅ **Movie Festival** (`MovieFestival.cpp`) - Activity selection (sort by end time)
- ✅ **Restaurant Customers** (`RestaurantCustomers.cpp`) - Sweep line algorithm
- ✅ **Stick Lengths** (`StickLengths.cpp`) - Median minimizes absolute deviations

### Advanced Array Techniques
- ✅ **Maximum Subarray Sum** (`MaximumSubarraySum.cpp`) - Kadane's algorithm
- ✅ **Missing Coin Sum** (`MissingCoinSum.cpp`) - Greedy gap-finding
- ✅ **Collecting Numbers** (`CollectingNumbers.cpp`) - Position tracking

### Sliding Window & Dynamic Structures
- ✅ **Playlist** (`Playlist.cpp`) - Sliding window with hash map
- ✅ **Traffic Lights** (`TrafficLights.cpp`) - Dynamic segments with set/multiset

### Mathematical Sequences
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

### Sliding Window with Hash Map
Pattern for longest substring problems (Playlist):
```cpp
map<int, int> lastPos;
int left = 0, best = 0;
for (int right = 0; right < n; right++) {
    if (lastPos.count(arr[right]) && lastPos[arr[right]] >= left) {
        left = lastPos[arr[right]] + 1;
    }
    lastPos[arr[right]] = right;
    best = max(best, right - left + 1);
}
```

### Sweep Line Algorithm
For event processing (Restaurant Customers):
```cpp
vector<pair<int, int>> events; // {time, type}
sort(events.begin(), events.end());
int active = 0, maxActive = 0;
for (auto [time, type] : events) {
    active += type; // +1 for arrival, -1 for departure
    maxActive = max(maxActive, active);
}
```

### Greedy with Binary Search
For optimal placement problems (Towers):
```cpp
vector<int> towers; // maintain sorted invariant
for (int cube : cubes) {
    auto it = lower_bound(towers.begin(), towers.end(), cube + 1);
    if (it == towers.end()) {
        towers.push_back(cube);
    } else {
        *it = cube;
    }
}
```

## Key Insights by Problem

- **Movie Festival**: Sort by end time for activity selection
- **Missing Coin Sum**: If you can make {1..k}, adding coin c≤k+1 extends to {1..k+c}
- **Towers**: Each tower top represents minimum value that can be placed
- **Traffic Lights**: Maintain segments dynamically with set + multiset
- **Playlist**: Track last position of each element for sliding window

## Remaining Problems (19/35)
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
