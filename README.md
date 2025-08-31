# CSES Problem Solutions

This repository contains my solutions to problems from the [CSES Problem Set](https://cses.fi/problemset/).

## Repository Structure

```
CSES/
├── Introductory_Problems/     # Basic algorithmic problems (20/19)
├── Sorting_and_Searching/     # Array and search problems (6/35)
├── Dynamic_Programming/       # DP problems (0/19)
├── Graph_Algorithms/         # Graph theory problems (16/36)
├── Range_Queries/            # Segment trees, BIT (0/19)
├── Tree_Algorithms/          # Tree-based problems (0/16)
├── Mathematics/              # Number theory, combinatorics (0/31)
├── String_Algorithms/        # String processing (0/17)
├── Geometry/                 # Computational geometry (0/7)
└── Advanced_Techniques/      # Advanced algorithms (0/24)
```

## Progress Overview

**Total Solved: 42/323** 🎯

### [Introductory Problems](Introductory_Problems/) - 20/19 ✅
- [x] Weird Algorithm
- [x] Missing Number  
- [x] Repetitions
- [x] Increasing Array
- [x] Permutations (Beautiful Permutation)
- [x] Number Spiral
- [x] Two Knights
- [x] Two Sets
- [x] Bit Strings
- [x] Trailing Zeros
- [x] Coin Piles
- [x] Palindrome Reorder
- [x] Gray Code
- [x] Creating Strings
- [x] Apple Division
- [x] Digit Queries
- [x] Grid Paths (Grid Path Description)
- [x] String Reorder
- [x] Knight Moves Grid
- [x] Grid Coloring

### [Sorting and Searching](Sorting_and_Searching/) - 6/35 🔄
- [x] Distinct Numbers
- [x] Apartments
- [x] Ferris Wheel  
- [x] Concert Tickets
- [x] Josephus Problem I
- [x] Josephus Problem II
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
- [ ] Subarray Sums I
- [ ] Subarray Sums II
- [ ] Subarray Divisibility
- [ ] Array Division
- [ ] Sliding Window Median
- [ ] Sliding Window Cost
- [ ] Movie Festival II
- [ ] Maximum Subarray Sum II

### [Graph Algorithms](Graph_Algorithms/) - 16/36 🔄
- [x] Counting Rooms (DFS/BFS)
- [x] Labyrinth (BFS)
- [x] Building Roads (Union-Find)
- [x] Message Route (BFS)
- [x] Building Teams (Graph Coloring/Bipartite)
- [x] Round Trip (Cycle Detection - Undirected)
- [x] Monsters (Multi-source BFS)
- [x] Shortest Routes I (Dijkstra)
- [x] Shortest Routes II (Floyd-Warshall)
- [x] High Score (Bellman-Ford/SPFA)
- [x] Flight Discount (Modified Dijkstra)
- [x] Cycle Finding (Negative Cycle Detection)
- [x] Flight Routes (K-Shortest Paths)
- [x] Round Trip II (Cycle Detection - Directed)
- [x] Course Schedule (Topological Sort)
- [x] Giant Pizza (2-SAT)
- [ ] Longest Flight Route
- [ ] Game Routes
- [ ] Investigation
- [ ] Planets Queries I
- [ ] Planets Queries II
- [ ] Planets Cycles
- [ ] Road Reparation
- [ ] Road Construction
- [ ] Flight Routes Check
- [ ] Planets and Kingdoms
- [ ] De Bruijn Sequence
- [ ] Teleporters Path
- [ ] Hamiltonian Flights
- [ ] Knight's Tour
- [ ] Download Speed
- [ ] Police Chase
- [ ] School Dance
- [ ] Distinct Routes
- [ ] Mail Delivery
- [ ] Shortest Routes III

### [Dynamic Programming](Dynamic_Programming/) - 0/19 📝
### [Range Queries](Range_Queries/) - 0/19 📝
### [Tree Algorithms](Tree_Algorithms/) - 0/16 📝
### [Mathematics](Mathematics/) - 0/31 📝
### [String Algorithms](String_Algorithms/) - 0/17 📝
### [Geometry](Geometry/) - 0/7 📝
### [Advanced Techniques](Advanced_Techniques/) - 0/24 📝

## Notes & Algorithm References

### Graph Algorithms
- **Dijkstra's Algorithm Variations**: The CSES set showcases several powerful variations:
  - State-Space Dijkstra (Flight Discount)
  - K-Shortest Paths (Flight Routes) 
  - Augmented Information Dijkstra (Investigation)
- **Cycle Detection**: Different approaches for directed vs undirected graphs
- **Union-Find**: Path compression and union by rank optimizations

### Common Patterns
- **Two Pointers**: Efficient O(n) solutions for sorted arrays
- **Binary Search**: Not just on arrays, but on answer spaces
- **Greedy Algorithms**: Often optimal for scheduling and assignment problems
- **DFS/BFS**: Grid traversal, connectivity, shortest paths

### Implementation Tips
- Use `long long` for large numbers to avoid overflow
- Fast I/O with `ios_base::sync_with_stdio(false); cin.tie(NULL);`
- STL containers: `set`, `multiset`, `priority_queue`, `deque`
- Graph representation: adjacency lists for sparse graphs

## Running Solutions
To compile and run any C++ solution:
```bash
g++ -o solution ProblemName.cpp
./solution < input.txt
```

Or for online judges:
```bash
g++ -std=c++17 -O2 -Wall ProblemName.cpp -o ProblemName
```
