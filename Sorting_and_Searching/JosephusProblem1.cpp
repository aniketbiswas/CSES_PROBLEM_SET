#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;

    queue<int> children, qualifiers;

    for (int i = 1; i <= n; i++) {
        children.push(i);
    }

    bool isOut = false;

    while (!children.empty()) {
        int size = children.size();
        while(size > 0) {
            int curr = children.front();
            children.pop();
            if (!isOut) {
                qualifiers.push(curr);
            } else {
                cout << curr << " ";
            }
            isOut = !isOut;
            size--;
        }
        children = qualifiers;
        qualifiers = queue<int>(); // Clear qualifiers for the next round
    }




    return 0;
}