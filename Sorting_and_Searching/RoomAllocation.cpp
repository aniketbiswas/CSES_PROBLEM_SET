/*
 * CSES Room Allocation Problem
 * 
 * Problem: Given n customers with arrival and departure days,
 * find minimum number of hotel rooms needed and assign each customer to a room.
 * Two customers can share a room if one departs before the other arrives.
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Read the number of customers
    int numberOfCustomers;
    cin >> numberOfCustomers;

    // Create events list: each event contains [time, eventType, customerId]
    // eventType: 1 = arrival, 2 = departure
    vector<vector<int>> chronologicalEvents;
    
    // Process each customer's arrival and departure
    for (int customerId = 1; customerId <= numberOfCustomers; customerId++) {
        int arrivalDay, departureDay;
        cin >> arrivalDay >> departureDay;
        
        // Add arrival event: [arrivalDay, 1, customerId]
        chronologicalEvents.push_back({arrivalDay, 1, customerId});
        
        // Add departure event: [departureDay, 2, customerId]  
        chronologicalEvents.push_back({departureDay, 2, customerId});
    }

    // Sort events by time; when times are equal, departures (2) come before arrivals (1)
    // This ensures optimal room reuse when someone leaves and someone arrives on same day
    sort(chronologicalEvents.begin(), chronologicalEvents.end());

    // Available room numbers (stack-like behavior for efficient reuse)
    vector<int> availableRoomNumbers;
    
    // Total number of rooms created so far
    int totalRoomsCreated = 0;
    
    // Store room assignment for each customer: roomAssignment[customerId] = roomNumber
    vector<int> roomAssignment(numberOfCustomers + 1);

    // Process each event in chronological order (sweep line algorithm)
    for (auto currentEvent : chronologicalEvents) {
        int eventTime = currentEvent[0];
        int eventType = currentEvent[1];  // 1 = arrival, 2 = departure
        int customerId = currentEvent[2];
        
        // Handle customer arrival
        if (eventType == 1) {
            // If no rooms are available, create a new room
            if (availableRoomNumbers.empty()) {
                totalRoomsCreated++;
                availableRoomNumbers.push_back(totalRoomsCreated);
            }
            
            // Assign an available room to the arriving customer
            int assignedRoomNumber = availableRoomNumbers.back();
            roomAssignment[customerId] = assignedRoomNumber;
            availableRoomNumbers.pop_back();  // Room is now occupied
        }
        
        // Handle customer departure  
        if (eventType == 2) {
            // Return the customer's room to the available pool
            int releasedRoomNumber = roomAssignment[customerId];
            availableRoomNumbers.push_back(releasedRoomNumber);
        }
    }

    // Output the results
    // First line: minimum number of rooms needed
    cout << totalRoomsCreated << "\n";
    
    // Second line: room assignment for each customer (in input order)
    for (int customerId = 1; customerId <= numberOfCustomers; customerId++) {
        cout << roomAssignment[customerId] << " ";
    }
    cout << "\n";

    return 0;
}