# Binary Lifting / Exponential Search Technique

## 🎯 **What is Binary Lifting Search?**

Binary lifting is an optimized binary search technique that builds the answer bit by bit, starting from the most significant bit. Instead of maintaining explicit `left` and `right` bounds, it constructs the boundary value directly.

## 🏭 **Example: Factory Machines Problem**

**Problem**: Find minimum time needed for `n` machines to produce `t` products total.

### **Traditional Binary Search**
```cpp
ll left = 0, right = 1e18;
while (left < right) {
    ll mid = left + (right - left) / 2;
    if (check(mid)) {
        right = mid;
    } else {
        left = mid + 1;
    }
}
cout << left << "\n";
```

### **Binary Lifting Approach**
```cpp
ll k = 0;
for (ll b = 1e18; b >= 1; b /= 2) {
    while (!check(k + b)) k += b;
}
cout << k + 1 << "\n";
```

## 🔍 **How Binary Lifting Works**

### **Core Concept**
- `k` = largest value where `check(k)` is **false**
- `k + 1` = smallest value where `check(k + 1)` is **true**
- We build `k` by testing each binary digit position

### **Step-by-Step Process**

1. **Initialize**: `k = 0` (our answer candidate)
2. **For each bit size** `b` (from largest to smallest):
   - Keep adding `b` to `k` while `check(k + b)` returns false
   - When `check(k + b)` becomes true, move to next smaller bit
3. **Result**: `k + 1` is our answer

### **Visual Example**
Suppose the answer is 42:

```
Initial: k = 0
Bit positions to test: [32, 16, 8, 4, 2, 1]

b = 32: k=0, check(0+32=32) = false → k = 32
b = 16: k=32, check(32+16=48) = true → skip (don't add)
b = 8:  k=32, check(32+8=40) = false → k = 40  
b = 4:  k=40, check(40+4=44) = true → skip
b = 2:  k=40, check(40+2=42) = true → skip
b = 1:  k=40, check(40+1=41) = false → k = 41

Final: k = 41, answer = k + 1 = 42
```

## ⚡ **Code Template**

```cpp
// Binary lifting to find minimum x where check(x) is true
auto check = [&](ll x) {
    // Return true if x satisfies our condition
    // Return false otherwise
};

ll k = 0;
for (ll b = MAX_VALUE; b >= 1; b /= 2) {
    while (!check(k + b)) k += b;
}
ll answer = k + 1;
```

## 🎯 **When to Use Binary Lifting**

### **Perfect for:**
- Finding minimum value satisfying a condition
- When you don't know the upper bound
- Monotonic predicates (if `check(x)` is true, then `check(x+1)` is also true)

### **Examples:**
- **Factory Machines**: Minimum time to produce t products
- **Finding square root**: Largest integer whose square ≤ n
- **Capacity problems**: Minimum capacity needed
- **Parametric search**: Finding optimal parameter value

## 📊 **Complexity Analysis**

- **Time**: O(log(MAX_VALUE) × check_function_time)
- **Space**: O(1)
- **Same complexity** as traditional binary search
- Often **faster in practice** due to better cache locality

## 🔄 **Comparison with Traditional Binary Search**

| Aspect | Traditional Binary Search | Binary Lifting |
|--------|--------------------------|----------------|
| Bounds | Need explicit left/right | No bounds needed |
| Code | More verbose | More concise |
| Debugging | Easier to visualize | Requires understanding bits |
| Flexibility | Standard approach | More elegant |
| Performance | Good | Often slightly better |

## 🧠 **Key Insights**

1. **Building Answer Bit by Bit**: We're essentially constructing the binary representation of our answer
2. **Invariant**: At each step, `k` represents the largest "bad" value
3. **Termination**: When we finish, `k+1` is the smallest "good" value
4. **No Overflow Issues**: We start from a safe upper bound and work down

## 📝 **Practice Problems**

### **CSES Problems using Binary Lifting:**
- Factory Machines
- Array Division
- Book Shop (with modifications)
- Maximum Subarray Sum II (advanced)

### **Implementation Notes:**
- Always ensure `check(0)` is false and `check(infinity)` is true
- Use `long long` for large search spaces
- The predicate function must be monotonic

## 🚀 **Advanced Variations**

### **Finding Maximum Instead of Minimum**
```cpp
// Find maximum x where check(x) is true
ll k = 0;
for (ll b = MAX_VALUE; b >= 1; b /= 2) {
    if (check(k + b)) k += b;
}
// k is the answer (no +1 needed)
```

### **With Custom Step Sizes**
```cpp
// For floating point or custom increments
double k = 0;
for (double b = 1e9; b >= 1e-9; b /= 2) {
    while (!check(k + b)) k += b;
}
```

This technique is particularly powerful in competitive programming where elegant, efficient solutions are valued! 🏆