/*
 * ============================================================================
 * OPTIVER SHOPPING - Supermarket Checkout System
 * ============================================================================
 * 
 * PROBLEM STATEMENT:
 * A supermarket has many customers entering and exiting at various points. 
 * They want to keep track of customers and get notification when a customer 
 * leaves the store. There are number of checkout lines, where customers with 
 * basket of items queue to pay and exit the store.
 * 
 * CHECKOUT RULES:
 * - A customer cannot add items to purchase once they join a checkout line
 * - If a customer increases their items, they must go to the back of the same line
 * - If a customer removes items, they keep their position in line
 * - A customer leaves immediately when they have no items left
 * - Lines with smaller IDs are closer to exit (priority for simultaneous exits)
 * 
 * OPERATIONS:
 * 1. CustomerEnter <CustomerId> <LineNumber> <NumItems>
 *    - Customer joins a checkout line with specified items
 * 
 * 2. BasketChange <CustomerId> <NewNumItems>
 *    - Customer changes total number of items in basket
 *    - If increased: customer goes to back of same line
 *    - If decreased: customer keeps position (or leaves if 0 items)
 * 
 * 3. LineService <LineNumber> <NumProcessedItems>
 *    - Process specified number of items from front of the line
 *    - Customers leave when all their items are processed
 * 
 * 4. LinesService
 *    - Process one item from every active line simultaneously
 *    - Customers leaving simultaneously exit in line ID order (ascending)
 * 
 * CONSTRAINTS:
 * - 0 ≤ N, CustomerId, LineNumber ≤ 2^32
 * - 0 ≤ NumItems, NewNumItems, NumProcessedItems ≤ 10^3
 * - BasketChange only happens for customers still in store
 * 
 * INPUT FORMAT:
 * First line: N (number of instructions)
 * Next N lines: One instruction each as described above
 * 
 * OUTPUT:
 * Print CustomerId when each customer leaves the store (one per line)
 * 
 * KEY DATA STRUCTURES:
 * - map<LineNumber, list<Customer>>: Each line as a queue of customers
 * - map<CustomerId, pair<LineNumber, iterator>>: Track customer positions
 * - unordered_set<LineNumber>: Track active lines (non-empty lines)
 * 
 * ALGORITHM COMPLEXITY:
 * - CustomerEnter: O(1)
 * - BasketChange: O(1) for decrease, O(1) for increase (move to back)
 * - LineService: O(customers processed)
 * - LinesService: O(active lines + customers leaving * log(customers leaving))
 * ============================================================================
 */

#include <cstddef>
#include <cstdint>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using CustomerId = int64_t;
using LineNumber = int64_t;

// Enter your solution here
struct Customer
{
    CustomerId id;
    int64_t originalItems;
    int64_t remainingItems;
    Customer(CustomerId id, int64_t originalItems, int64_t remainingItems) : id(id), originalItems(originalItems), remainingItems(remainingItems) {}
};

map<LineNumber, list<Customer>> lines;

map<int64_t, pair<LineNumber, list<Customer>::iterator>> customerPosition;

unordered_set<LineNumber> activeLines;

void lineService(int lineNumber, int numProcessedItems)
{
    while (!lines[lineNumber].empty() && numProcessedItems > 0)
    {
        Customer &frontCustomer = lines[lineNumber].front();
        CustomerId customerId = frontCustomer.id;
        int64_t remainingItems = frontCustomer.remainingItems;

        if (remainingItems <= numProcessedItems)
        {
            numProcessedItems -= remainingItems;
            lines[lineNumber].pop_front();
            if (lines[lineNumber].empty())
            {
                activeLines.erase(lineNumber);
            }
            customerPosition.erase(customerId);
            cout << customerId << endl;
        }
        else
        {
            frontCustomer.remainingItems -= numProcessedItems;
            numProcessedItems = 0;
        }
    }
}

void basketChange(CustomerId customerId, int64_t newNumItems)
{
    if (customerPosition.find(customerId) != customerPosition.end())
    {
        auto [lineNumber, customerIt] = customerPosition[customerId];
        int64_t originalItems = customerIt->originalItems;
        int64_t remainingItems = customerIt->remainingItems;
        int64_t diffItems = newNumItems - originalItems;
        if (diffItems > 0)
        {
            lines[lineNumber].erase(customerIt);
            customerPosition.erase(customerId);

            lines[lineNumber].emplace_back(customerId, newNumItems, remainingItems + diffItems);
            auto newIt = prev(lines[lineNumber].end());
            customerPosition[customerId] = {lineNumber, newIt};
        }
        else
        {
            if (remainingItems + diffItems <= 0)
            {
                lines[lineNumber].erase(customerIt);
                if (lines[lineNumber].empty())
                {
                    activeLines.erase(lineNumber);
                }
                customerPosition.erase(customerId);
                cout << customerId << endl;
            }
            else
            {
                customerIt->originalItems = newNumItems;
                customerIt->remainingItems += diffItems;
            }
        }
    }
}

void customerEnter(CustomerId &customerId, LineNumber &lineNumber, int64_t &numItems)
{
    if (lines[lineNumber].empty())
    {
        activeLines.insert(lineNumber);
    }
    lines[lineNumber].emplace_back(customerId, numItems, numItems);
    auto it = prev(lines[lineNumber].end());
    customerPosition[customerId] = {lineNumber, it};
}

void linesService()
{
    vector<pair<LineNumber, CustomerId>> leavingCustomers;
    unordered_set<LineNumber> remainingLines = activeLines;

    for (LineNumber lineNumber : activeLines)
    {
        auto &l = lines[lineNumber];
        if (!l.empty())
        {
            auto &frontCustomer = l.front();
            CustomerId customerId = frontCustomer.id;

            if (frontCustomer.remainingItems == 1)
            {
                l.pop_front();
                customerPosition.erase(customerId);
                leavingCustomers.push_back({lineNumber, customerId});

                if (l.empty())
                {
                    remainingLines.erase(lineNumber);
                }
            }
            else
            {
                frontCustomer.remainingItems -= 1;
            }
        }
    }
    // cout<<leavingCustomers.size()<<endl;
    sort(leavingCustomers.begin(), leavingCustomers.end());
    activeLines = remainingLines;
    for (auto [line, customer] : leavingCustomers)
    {
        cout << customer << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    uint64_t N;
    std::cin >> N;

    for (size_t i = 0; i < N; ++i)
    {
        std::string instructionText;
        std::cin >> instructionText;
        if (instructionText == "CustomerEnter")
        {
            CustomerId customerId;
            LineNumber lineNumber;
            int64_t numItems;
            std::cin >> customerId >> lineNumber >> numItems;
            // TODO Implement
            customerEnter(customerId, lineNumber, numItems);
        }
        else if (instructionText == "BasketChange")
        {
            CustomerId customerId;
            int64_t newNumItems;
            std::cin >> customerId >> newNumItems;
            // TODO Implement
            basketChange(customerId, newNumItems);
        }
        else if (instructionText == "LineService")
        {
            LineNumber lineNumber;
            int64_t numProcessedItems;
            std::cin >> lineNumber >> numProcessedItems;
            // TODO Implement
            lineService(lineNumber, numProcessedItems);
        }
        else if (instructionText == "LinesService")
        {
            // TODO Implement
            linesService();
        }
        else
        {
            std::cerr << "Malformed input! " << instructionText << std::endl;
            return -1;
        }
    }

    return 0;
}
