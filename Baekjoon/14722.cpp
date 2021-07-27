#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

inline int next(int m) 
{
    return m + 1 % 3;
}

int N;
vector<vector<int>> maps;
vector<vector<array<int, 4>>> dpTable;

int walkMap(int x, int y, int status)
{
    int& count = dpTable[y][x][status + 1];
    if (count != -1) return count;
    count = 0;

    //! Go right
    if (x + 1 != N)
    {
        if (maps[y][x + 1] == next(status)) count = max(count, walkMap(x + 1, y, next(status)) + 1);
        count = max(count, walkMap(x + 1, y, status));
    }
    //! Go down
    if (y + 1 != N)
    {
        if (maps[y + 1][x] == next(status)) count = max(count, walkMap(x, y + 1, next(status)) + 1);
        count = max(count, walkMap(x, y + 1, status));
    }
    return count;
}

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    cin >> N;
    maps.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> maps[i][j];

    dpTable.resize(N, vector<array<int, 4>>(N, {-1, -1, -1, -1}));

    if (maps[0][0] == 0)
        cout << walkMap(0, 0, 0) + 1;
    else
        cout << walkMap(0, 0, -1);

    return 0;
}