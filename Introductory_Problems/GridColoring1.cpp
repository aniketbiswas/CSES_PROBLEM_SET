#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> grid[i][j];
        }
    }

    char characters[4] = {'A', 'B', 'C', 'D'};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (char c : characters)
            {
                if (c != grid[i][j] && (i == 0 || grid[i - 1][j] != c) && (j == 0 || grid[i][j - 1] != c))
                {
                    grid[i][j] = c;
                    break;
                }
            }
        }
    }

    for (auto rows : grid)
    {
        for (auto ch : rows)
        {
            cout << ch;
        }
        cout << '\n';
    }

    return 0;
}