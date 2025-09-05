# Sorting and Searching

This section focuses on array manipulation, binary search, greedy algorithms, and efficient data structures.

## Progress: 25/35 ✅

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

### Binary Search on Answer
- ✅ **Room Allocation** (`RoomAllocation.cpp`) - Event-based room assignment with sweep line
- ✅ **Factory Machines** (`FactoryMachines.cpp`) - Binary search on time with production capacity check
- ✅ **Array Division** (`ArrayDivision.cpp`) - Binary search on maximum sum with greedy validation

### Advanced Optimization
- ✅ **Tasks and Deadlines** (`TasksAndDeadlines.cpp`) - Greedy scheduling by duration
- ✅ **Reading Books** (`ReadingBooks.cpp`) - Load balancing with bottleneck analysis

### Prefix Sums and Hash Maps
- ✅ **Subarray Sums I** (`SubarraySum1.cpp`) - Sliding window technique for positive arrays
- ✅ **Subarray Sums II** (`SubarraySum2.cpp`) - Hash map + prefix sums for any integers

### Stack Algorithms  
- ✅ **Nearest Smaller Values** (`NearestSmallerValues.cpp`) - Monotonic stack for nearest element queries

### Additional Problems
- ✅ **Distinct Value Subarrays** (`DistinctValueSubarrays.cpp`) - Advanced sliding window

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

### Binary Search on Answer
For optimization problems (Factory Machines, Array Division):
```cpp
bool check(ll mid) {
    // Can we achieve goal with parameter mid?
    return feasible;
}

ll left = theoretical_minimum;
ll right = theoretical_maximum;
while (left < right) {
    ll mid = left + (right - left) / 2;
    if (check(mid)) {
        right = mid;  // Try smaller values
    } else {
        left = mid + 1;  // Need larger values
    }
}
```

### Monotonic Stack
For nearest element problems (Nearest Smaller Values):
```cpp
stack<int> st;
for (int i = 0; i < n; i++) {
    while (!st.empty() && arr[st.top()] >= arr[i]) {
        st.pop();  // Remove larger elements
    }
    result[i] = st.empty() ? 0 : st.top() + 1;
    st.push(i);
}
```

### Prefix Sums with Hash Map
For subarray sum problems (Subarray Sums II):
```cpp
map<ll, int> prefixCount;
prefixCount[0] = 1;
ll prefixSum = 0, result = 0;
for (int i = 0; i < n; i++) {
    prefixSum += arr[i];
    result += prefixCount[prefixSum - target];
    prefixCount[prefixSum]++;
}
```

## Key Insights by Problem

- **Movie Festival**: Sort by end time for activity selection
- **Missing Coin Sum**: If you can make {1..k}, adding coin c≤k+1 extends to {1..k+c}
- **Towers**: Each tower top represents minimum value that can be placed
- **Traffic Lights**: Maintain segments dynamically with set + multiset
- **Playlist**: Track last position of each element for sliding window
- **Factory Machines**: Binary search on time + greedy capacity checking
- **Tasks and Deadlines**: Sort by duration (shortest first) for optimal scheduling
- **Reading Books**: Answer = max(total_time, 2 * longest_book) - two bottlenecks
- **Room Allocation**: Event-based sweep line with available room stack
- **Array Division**: Binary search on max sum + greedy subarray validation  
- **Subarray Sums I**: Sliding window works for positive arrays only
- **Subarray Sums II**: Hash map + prefix sums handles negative numbers
- **Nearest Smaller Values**: Monotonic stack maintains increasing elements

## Remaining Problems (10/35)
- [ ] Sum of Three Values
- [ ] Sum of Four Values
- [ ] Subarray Divisibility
- [ ] Sliding Window Median
- [ ] Sliding Window Cost
- [ ] Movie Festival II
- [ ] Maximum Subarray Sum II
