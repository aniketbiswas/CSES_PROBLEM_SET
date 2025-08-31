# Dijkstra's Algorithm and Its Variations in CSES Problem Set

This document provides a comprehensive guide to Dijkstra's algorithm and its various modifications as they appear in the CSES competitive programming problem set.

## Table of Contents

1. [Standard Dijkstra's Algorithm](#1-standard-dijkstras-algorithm)
2. [Variation 1: State-Space Dijkstra (Flight Discount)](#2-variation-1-state-space-dijkstra-flight-discount)
3. [Variation 2: K-Shortest Paths (Flight Routes)](#3-variation-2-k-shortest-paths-flight-routes)
4. [Variation 3: Augmented Information Dijkstra (Investigation)](#4-variation-3-augmented-information-dijkstra-investigation)
5. [Related Algorithm: Prim's Algorithm (Road Reparation)](#5-related-algorithm-prims-algorithm-road-reparation)
6. [Summary and Pattern Recognition](#6-summary-and-pattern-recognition)

---

## 1. Standard Dijkstra's Algorithm

### Overview

Dijkstra's algorithm finds the shortest paths from a single source vertex to all other vertices in a graph with **non-negative edge weights**. It's a greedy algorithm that builds the solution incrementally by always choosing the most promising path.

### Key Components

```cpp
vector<long long> dist(n + 1, INF);  // Distance array
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;  // Min-heap
```

### Core Algorithm

```cpp
dist[source] = 0;
pq.push({0, source});

while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    
    if (d > dist[u]) continue;  // Outdated entry
    
    for (auto& [v, w] : graph[u]) {
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
}
```

### Time Complexity: O((V + E) log V)

---

## 2. Variation 1: State-Space Dijkstra (Flight Discount)

### Problem Context

Find the shortest path from city 1 to city n with the option to use a 50% discount on exactly one flight.

### The Innovation

Instead of tracking just the city, we track a **state** consisting of `(city, discount_status)`. This effectively doubles the graph size but allows us to model the constraint.

### Implementation Details

```cpp
// 2D distance array: dist[city][discount_used]
vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));
priority_queue<tuple<long long, int, bool>, /* ... */> pq;

dist[1][0] = 0;
pq.push({0, 1, false});

while (!pq.empty()) {
    auto [d, u, used] = pq.top();
    pq.pop();
    
    if (d > dist[u][used]) continue;
    
    for (auto& [v, w] : graph[u]) {
        // Case 1: Don't use discount
        if (d + w < dist[v][used]) {
            dist[v][used] = d + w;
            pq.push({dist[v][used], v, used});
        }
        
        // Case 2: Use discount (if available)
        if (!used && d + w/2 < dist[v][1]) {
            dist[v][1] = d + w/2;
            pq.push({dist[v][1], v, true});
        }
    }
}
```

### Key Insight

This pattern can be generalized to any problem where the path has multiple "modes" or "states" (e.g., with/without power-ups, before/after using a special ability).

---

## 3. Variation 2: K-Shortest Paths (Flight Routes)

### Problem Context

Find the k cheapest routes from city 1 to city n (routes may contain cycles).

### The Innovation

Instead of maintaining a single distance per vertex, we maintain a list of up to k distances. We allow each vertex to be "finalized" multiple times.

### Implementation Details

```cpp
vector<long long> dists[n + 1];  // Lists of distances
priority_queue<pair<long long, int>, /* ... */> pq;

pq.push({0, 1});

while (!pq.empty()) {
    auto [cost, city] = pq.top();
    pq.pop();
    
    // Key modification: Allow up to k visits
    if (dists[city].size() >= k) continue;
    
    dists[city].push_back(cost);
    
    for (auto& [v, w] : graph[city]) {
        pq.push({cost + w, v});
    }
}
```

### Key Insight

This variation trades the "one optimal path per vertex" constraint for finding multiple near-optimal solutions.

---

## 4. Variation 3: Augmented Information Dijkstra (Investigation)

### Problem Context

Find not just the shortest path, but also:
- Number of shortest paths
- Minimum flights in a shortest path
- Maximum flights in a shortest path

### The Innovation

Maintain multiple pieces of information for each vertex and update them during relaxation.

### Implementation Details

```cpp
struct NodeInfo {
    long long dist = INF;
    long long count = 0;
    int min_flights = 0;
    int max_flights = 0;
};

vector<NodeInfo> info(n + 1);
info[1] = {0, 1, 0, 0};

while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    
    if (d > info[u].dist) continue;
    
    for (auto& [v, w] : graph[u]) {
        long long new_dist = info[u].dist + w;
        
        if (new_dist < info[v].dist) {
            // Found a better path - reset all statistics
            info[v].dist = new_dist;
            info[v].count = info[u].count;
            info[v].min_flights = info[u].min_flights + 1;
            info[v].max_flights = info[u].max_flights + 1;
            pq.push({new_dist, v});
        }
        else if (new_dist == info[v].dist) {
            // Found an equally good path - update statistics
            info[v].count = (info[v].count + info[u].count) % MOD;
            info[v].min_flights = min(info[v].min_flights, info[u].min_flights + 1);
            info[v].max_flights = max(info[v].max_flights, info[u].max_flights + 1);
        }
    }
}
```

### Key Insight

This shows how Dijkstra can be extended to gather rich path information beyond just distances.

---

## 5. Related Algorithm: Prim's Algorithm (Road Reparation)

### The Connection

While solving Minimum Spanning Tree (MST) problems, Prim's algorithm shares the same structure as Dijkstra's but with a different optimization criterion.

### Key Differences

| Aspect | Dijkstra's | Prim's |
|--------|-----------|---------|
| Goal | Shortest path from source | Minimum spanning tree |
| Priority | Distance from source | Edge weight to tree |
| Relaxation | `dist[u] + w < dist[v]` | `w < key[v]` |

### Implementation Comparison

```cpp
// Prim's Algorithm
vector<long long> key(n + 1, INF);
vector<bool> in_mst(n + 1, false);
priority_queue<pair<long long, int>, /* ... */> pq;

key[1] = 0;
pq.push({0, 1});

while (!pq.empty()) {
    auto [w, u] = pq.top();
    pq.pop();
    
    if (in_mst[u]) continue;
    in_mst[u] = true;
    mst_cost += w;
    
    for (auto& [v, weight] : graph[u]) {
        if (!in_mst[v] && weight < key[v]) {
            key[v] = weight;
            pq.push({weight, v});
        }
    }
}
```

---

## 6. Summary and Pattern Recognition

### Common Patterns in Dijkstra Variations

1. **State Expansion**: When constraints involve modes or limited resources
   - Add dimensions to the distance array
   - Expand the priority queue to include state information

2. **Multiple Solutions**: When finding k-best paths
   - Replace single distance with a collection
   - Allow multiple "visits" to each vertex

3. **Path Properties**: When tracking additional path information
   - Augment the relaxation step
   - Update multiple values during path exploration

### Problem Classification Guide

| Problem Type | Variation to Use |
|--------------|------------------|
| Shortest path with limited resource usage | State-Space Dijkstra |
| K shortest paths | K-Shortest Paths |
| Path counting/properties | Augmented Information |
| Minimum spanning tree | Prim's (structural cousin) |

### Implementation Tips

1. **Always use a min-heap** for the priority queue
2. **Check for outdated entries** with `if (d > dist[u]) continue`
3. **Use appropriate data types** (long long for distances to avoid overflow)
4. **Consider the state space** - what information uniquely identifies a position in your search?

### When to Use Each Variation

- **Standard Dijkstra**: Basic shortest path problems
- **State-Space**: Problems with modes, power-ups, or limited-use abilities
- **K-Shortest**: When you need multiple solutions or alternative routes
- **Augmented**: When you need statistics about the shortest paths
- **Prim's**: For minimum spanning tree problems

These variations demonstrate the flexibility of Dijkstra's core idea: greedy exploration guided by a priority queue. By understanding these patterns, you can adapt the algorithm to solve a wide variety of graph optimization problems.