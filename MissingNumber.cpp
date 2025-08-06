#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void missingNumber(const vector<int>& numbers, int n) {
    
    int misNum = 0;
    
    for (int num : numbers) {
        misNum ^= num;
    }

    for(int i=1;i<=n;i++) {
        misNum ^= i;
    }

    cout << misNum << endl;
}

int main() {
    int n ;
    cin >> n;
   
    vector<int> numbers(n-1);
    for (int i = 0; i < n - 1; ++i)
        cin >> numbers[i];

    missingNumber(numbers, n);
    return 0;
}