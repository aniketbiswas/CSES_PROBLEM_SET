#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long numberSpiral(long long x, long long y)
{
    long long layer = max(x, y);
    long long layerEnd = layer * layer;
    long long layerStart = (layer - 1) * (layer - 1) + 1;

    // If the layer is odd, the spiral starts at the bottom right corner
    if (layer % 2 == 1)
    {
        // If x == layer, we just need to find the value at the bottom right corner
        if (x == layer)
        {
            return layerStart + y - 1;
        }
        else
        {
            // left column - x
            return layerEnd - (x - 1);
        }
    }
    else
    {
        // If the layer is even, the spiral starts at the top left corner
        if (y == layer)
        {
            // right column - y
            return layerStart + x - 1;
        }
        else
        {
            // top row - y
            return layerEnd - (y - 1);
        }
    }
}

int main()
{
    int numberOfQueries;
    cin >> numberOfQueries;

    while (numberOfQueries--)
    {
        long long x, y;
        cin >> x >> y;
        cout << numberSpiral(x, y) << endl;
    }
    return 0;
}