#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
GRAY CODE ALGORITHM - MATHEMATICAL FOUNDATION:

The formula G(i) = i XOR (i >> 1) works because:

1. BINARY REPRESENTATION: Any number i has binary form [b_n, b_{n-1}, ..., b_1, b_0]
2. RIGHT SHIFT: i >> 1 gives [0, b_n, b_{n-1}, ..., b_1] (shifts all bits right by 1)
3. XOR OPERATION: For each bit position j: Gray_bit_j = Original_bit_j XOR Original_bit_{j+1}

This creates the property that consecutive Gray codes differ by exactly one bit.

EXAMPLE WALKTHROUGH (n=3):
i=0: 000 XOR 000 = 000  →  "000"
i=1: 001 XOR 000 = 001  →  "001"  (bit 0 different from previous)
i=2: 010 XOR 001 = 011  →  "011"  (bit 1 different from previous)
i=3: 011 XOR 001 = 010  →  "010"  (bit 0 different from previous)
i=4: 100 XOR 010 = 110  →  "110"  (bit 2 different from previous)
i=5: 101 XOR 010 = 111  →  "111"  (bit 0 different from previous)
i=6: 110 XOR 011 = 101  →  "101"  (bit 1 different from previous)
i=7: 111 XOR 011 = 100  →  "100"  (bit 0 different from previous)
*/

vector<string> generateGrayCode(int n) {
    vector<string> grayCodes;
    int totalCodes = 1 << n; // Calculate 2^n using bit shift

    for (int i = 0; i < totalCodes; ++i) {
        // CORE ALGORITHM: Convert index i to Gray code using mathematical formula
        int gray = i ^ (i >> 1);
        
        // BUILD STRING: Extract each bit from MSB to LSB
        string code = "";
        for (int j = n - 1; j >= 0; --j) {
            // Create bit mask for position j, extract bit, convert to character
            code += ((gray & (1 << j)) ? '1' : '0');
        }
        
        grayCodes.push_back(code);
    }

    return grayCodes;
}


int main() {
    int n;
    cin >> n;
    vector<string> grayCodes;

    grayCodes = generateGrayCode(n);
    for (const string& code : grayCodes) {
        cout << code << endl;
    }

    return 0;
}

