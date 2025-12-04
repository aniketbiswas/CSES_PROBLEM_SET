/*
 * CSES - Movie Festival 2
 * 
 * Problem: Given n movies (each with start and end time) and k people,
 * find the maximum number of movies that can be watched in total.
 * Each person can watch one movie at a time (no overlaps for same person).
 * Different people can watch overlapping movies.
 * 
 * Key Insights:
 * 1. Extension of Movie Festival 1 (which had k=1 person)
 * 2. Greedy approach: Sort by end time, then assign optimally
 * 3. Use multiset to track when each person becomes free
 * 
 * Algorithm:
 * 1. Sort movies by end time (greedy choice)
 * 2. For each movie, find a person who is free before movie starts
 * 3. Among available people, choose the one who became free most recently
 *    (this maximizes flexibility for future assignments)
 * 
 * Time Complexity: O(n log n + n log k) = O(n log(n+k))
 * Space Complexity: O(k)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <climits>
#include <cmath>
using namespace std;
 
typedef long long ll;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, k;
    cin >> n >> k;
 
    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; i++) {
        cin >> movies[i].first >> movies[i].second;
    }
 
    // Sort movies by end time (greedy choice)
    // If end times are equal, sort by start time (minor optimization)
    sort(movies.begin(), movies.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if(a.second == b.second)
            return a.first < b.first;
        return a.second < b.second;
    });
 
    // Use multiset to track when each person becomes free
    // multiset automatically keeps elements sorted
    // Allows O(log k) insertion, deletion, and search operations
    multiset<int> people;
    
    // Initially all k people are free at time 0
    for (int i = 0; i < k; i++) {
        people.insert(0);
    }
    
    int totalCount = 0;

    for(const auto& movie : movies) {
        int start = movie.first;
        int end = movie.second;
        
        /*
         * Critical Logic: Finding the optimal person assignment
         * 
         * Goal: Find a person who is free before this movie starts
         * Strategy: Among all available people, choose the one who became free most recently
         * 
         * upper_bound(start) returns iterator to first element > start
         * This gives us the first person who becomes free AFTER movie starts
         * 
         * Case Analysis:
         * 1. if (it == people.begin()): 
         *    - ALL people become free after movie starts
         *    - No one is available → skip this movie
         * 
         * 2. if (it != people.begin()):
         *    - At least one person is free before movie starts
         *    - --it gives us the person with maximum free_time ≤ start_time
         *    - This is the greedy choice (latest available person)
         * 
         * 3. if (it == people.end()):
         *    - All people become free before movie starts
         *    - --it gives us the person who became free latest
         */
        auto it = people.upper_bound(start);
        if (it != people.begin()) {
            --it; // Get the person who became free most recently but still before movie starts
            people.erase(it);                // Remove this person's current free time
            people.insert(end);              // This person now becomes free at movie end time
            totalCount++;
        }
        // If it == people.begin(), no one is available, skip this movie
    }    cout << totalCount << endl;
 
    return 0;
}

/*
 * Example Walkthrough:
 * Input: n=4, k=2, movies: (1,3), (2,5), (6,8), (8,10)
 * 
 * After sorting by end time: (1,3), (2,5), (6,8), (8,10)
 * Initial: people = {0, 0}
 * 
 * Movie (1,3):
 *   - people = {0, 0}, start = 1
 *   - upper_bound(1) → points to end() (no element > 1)
 *   - it != begin() → true, --it points to last 0
 *   - Assign movie: people = {0, 3}, count = 1
 * 
 * Movie (2,5):
 *   - people = {0, 3}, start = 2
 *   - upper_bound(2) → points to 3
 *   - it != begin() → true, --it points to 0
 *   - Assign movie: people = {3, 5}, count = 2
 * 
 * Movie (6,8):
 *   - people = {3, 5}, start = 6
 *   - upper_bound(6) → points to end()
 *   - it != begin() → true, --it points to 5
 *   - Assign movie: people = {3, 8}, count = 3
 * 
 * Movie (8,10):
 *   - people = {3, 8}, start = 8
 *   - upper_bound(8) → points to end()
 *   - it != begin() → true, --it points to 8
 *   - Assign movie: people = {3, 10}, count = 4
 * 
 * Answer: 4 movies
 * 
 * Key Learning: 
 * The greedy choice of picking the person who became free most recently
 * (among available people) maximizes future assignment flexibility.
 */