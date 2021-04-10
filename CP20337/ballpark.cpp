#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ifstream in("ballpark.inp");
    ofstream out("ballpark.out");
    
    int n, m;
    in >> n >> m;
    
    vector<vector<int>> ballpark(n, vector<int>(m));
    string temp;
    for (int i = 0; i < n; ++i)
    {
        in >> temp;
        int* row = ballpark[i].data();
        for (char c : temp)
            *row++ = (c - '0') == 0 ? 1 : 0;
    }

    int maxArea = numeric_limits<int>::min(), maxCount = 0;
    for (int i = n - 2; i >= 0; --i)
    {
        auto& row = ballpark[i];
        auto& above_row = ballpark[i + 1];
        for (int j = 1; j < m; ++j)
        {
            if (row[j])
            {
                row[j] = min({ above_row[j], above_row[j - 1], row[j - 1] }) + 1;
                if (maxArea == row[j])
                    ++maxCount;
                else if (row[j] > maxArea)
                {
                    maxCount = 1;
                    maxArea = row[j];
                }
            }
        }
    }

    out << maxArea << ' ' << maxCount << endl;

    for (int j = 1; j < m; ++j)
    {
        for (int i = n - 1; i >= 0; --i)
        {
            if (ballpark[i][j] == maxArea)
                out << j - maxArea + 2 << ' ' << n - 1 - i - maxArea + 2 << endl;
        }
    }

    out.close();
    in.close();

    return 0;
}