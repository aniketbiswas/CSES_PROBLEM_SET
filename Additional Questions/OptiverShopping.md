# Optiver Shopping - Supermarket Checkout System

## Problem Overview

A supermarket has many customers entering and exiting at various points. They want to keep track of customers and get notification when a customer leaves the store. There are number of checkout lines, where customers with basket of items queue to pay and exit the store. Individual checkout lines and customers are assigned numerical IDs.

## Rules and Constraints

### Checkout Rules
- A customer **cannot add items** to purchase once they join a given checkout line
- If a customer **increases their items**, they must go to the **back of the same line**
- If a customer **removes items**, they will **keep their position** in the line (or leave if no items remain)
- A customer leaves the supermarket as soon as they have **no items left** to checkout
- Lines with **smaller IDs are closer to the exit** (priority for simultaneous exits)

### Technical Constraints
- `0 ≤ N, CustomerId, LineNumber ≤ 2^32`
- `0 ≤ NumItems, NewNumItems, NumProcessedItems ≤ 10^3`
- **BasketChange** will only happen for customers who are still in the store
- Line service calls with no queue should be **ignored**

## Operations

### 1. CustomerEnter
**Format**: `CustomerEnter <CustomerId> <LineNumber> <NumItems>`

**Description**: A customer joins a checkout line with a specified number of items.

**Example**: `CustomerEnter 101 2 5` - Customer 101 joins line 2 with 5 items

### 2. BasketChange
**Format**: `BasketChange <CustomerId> <NewNumItems>`

**Description**: A customer changes the total number of items in their basket.
- **Increase**: Customer goes to the back of their current line
- **Decrease**: Customer keeps their position (or leaves if 0 items)

**Example**: `BasketChange 101 3` - Customer 101 now has 3 items total

### 3. LineService
**Format**: `LineService <LineNumber> <NumProcessedItems>`

**Description**: Process a specified number of items from the front of a specific line.
- Customers leave when all their items are processed
- Processing continues until items are exhausted or line is empty

**Example**: `LineService 2 10` - Process 10 items from line 2

### 4. LinesService
**Format**: `LinesService`

**Description**: Process exactly one item from every active (non-empty) line.
- If multiple customers leave simultaneously, they exit in **line ID order** (ascending)

## Input Format

```
N
<Instruction 1>
<Instruction 2>
...
<Instruction N>
```

Where each instruction follows one of the four formats above.

## Output Format

Print the `CustomerId` of each customer as they leave the store (one per line).

## Algorithm & Data Structures

### Key Data Structures
1. **`map<LineNumber, list<Customer>>`** - Each line as a queue of customers
2. **`map<CustomerId, pair<LineNumber, iterator>>`** - Track customer positions
3. **`unordered_set<LineNumber>`** - Track active (non-empty) lines

### Customer Structure
```cpp
struct Customer {
    CustomerId id;
    int64_t originalItems;    // Items when customer entered/last moved
    int64_t remainingItems;   // Items still to be processed
};
```

### Time Complexity
- **CustomerEnter**: O(1)
- **BasketChange**: O(1) for decrease, O(1) for increase (move to back)
- **LineService**: O(customers processed)
- **LinesService**: O(active lines + customers leaving × log(customers leaving))

## Example Walkthrough

```
Input:
6
CustomerEnter 101 1 3
CustomerEnter 102 1 2
LineService 1 1
BasketChange 101 1
LineService 1 2
LinesService

Execution:
1. Customer 101 enters line 1 with 3 items: Line 1: [101(3)]
2. Customer 102 enters line 1 with 2 items: Line 1: [101(3), 102(2)]
3. LineService 1 1: Process 1 item from line 1: Line 1: [101(2), 102(2)]
4. BasketChange 101 1: Customer 101 reduces to 1 item total (was 3, now 1): Line 1: [101(0), 102(2)]
5. Customer 101 leaves immediately (0 items): Output "101", Line 1: [102(2)]
6. LineService 1 2: Process 2 items from line 1: Line 1: [102(0)]
7. Customer 102 leaves: Output "102"
8. LinesService: No active lines, no output

Output:
101
102
```

## Key Implementation Challenges

1. **Position Tracking**: Efficiently track customer positions using iterators
2. **Simultaneous Exits**: Handle multiple customers leaving at once with proper ordering
3. **Basket Changes**: Correctly handle item increases (move to back) vs decreases (stay in place)
4. **Edge Cases**: Empty lines, customers with 0 items, invalid operations

## Problem Source
**Company**: Optiver  
**Type**: Technical Interview Question  
**Category**: Data Structures, Simulation  
**Difficulty**: Medium-Hard  
**Topics**: Queue Management, Hash Maps, Iterator Manipulation