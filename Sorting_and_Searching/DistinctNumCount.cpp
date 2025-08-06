#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> numbers(n);
    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end());

    int distinct = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0 || numbers[i] != numbers[i - 1])
        {
            distinct++;
        }
    }

    cout << distinct << '\n';

    return 0;
}