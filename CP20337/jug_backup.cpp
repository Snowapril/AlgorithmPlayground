#include <fstream>
#include <array>
#include <algorithm>
#include <vector>
#include <cstring>

#include <iostream>
using namespace std;

int main()
{
    ifstream in("jug.inp");
    ofstream out("jug.out");

    int actions[4] = { 0, };
    in >> actions[1] >> actions[2] >> actions[3];

    vector<int> N;
    int temp_N;
    while (in >> temp_N) N.push_back(temp_N);

    array<array<bool, 4>, 100> DP[3];
    memset(DP[0].data(), 0, 3 * 4 * 100);

    DP[0][0] = { true, false, false, false };
    DP[1][0] = { false, false, false, false };
    DP[2][0] = { false, false, false, false };

    const int max_N = *max_element(N.begin(), N.end());
    for (size_t temp_N = 1; temp_N < 100; ++temp_N)
    {
        for (int i = 0; i < 3; ++i)
        {
            int new_N = temp_N - actions[i + 1];
            if (new_N >= 0)
            {
                bool S_win = false;
                for (int j = 0; j < 3; ++j)
                {
                    if (i != j) S_win |= DP[2][new_N][j];
                }
                DP[2][temp_N][i] = !S_win;
            }
        }
        DP[2][temp_N][3] = any_of(DP[2][temp_N].begin(), DP[2][temp_N].begin() + 3, [](bool b) { return b; });

        for (int i = 0; i < 3; ++i)
        {
            bool S_win = false;
            int new_N = temp_N - actions[i + 1];
            if (new_N >= 0)
            {
                S_win |= !DP[2][new_N][3];
                for (int j = 0; j < 3; ++j)
                {
                    if (i != j)
                    {
                        bool F_win = false;
                        int current_N = new_N - actions[j + 1];
                        if (current_N >= 0)
                        {
                            for (int k = 0; k < 3; ++k)
                            {
                                if (j != k) F_win |= DP[1][current_N][k];
                            }
                        }
                        else
                            F_win = true;

                        S_win |= !F_win;
                    }
                }
                DP[1][temp_N][i] = !S_win;
            }
            else
            {
                DP[1][temp_N][i] = false;
            }
        }

        DP[1][temp_N][3] = any_of(DP[1][temp_N].begin(), DP[1][temp_N].begin() + 3, [](bool b) { return b; });

        for (int i = 1; i < 4; ++i)
        {
            int new_N = temp_N - actions[i];
            if (new_N >= 0)
            {
                bool S_win = false;
                for (int j = 0; j < 4; ++j)
                {
                    if (i != j) S_win |= DP[0][new_N][j];
                }
                DP[0][temp_N][i] = !S_win;
            }
        }
        bool S_win = false;
        for (int i = 1; i < 4; ++i)
        {
            int new_N = temp_N - actions[i];
            if (new_N >= 0)
            {
                bool F_win = false;
                for (int j = 0; j < 3; ++j)
                {
                    if ((i - 1) != j) F_win |= DP[1][new_N][j];
                }
                S_win |= !F_win;
            }
        }
        DP[0][temp_N][3] = !S_win;
    }

    for (int temp_N : N)
    {
        if (any_of(DP[0][temp_N].begin(), DP[0][temp_N].end(), [](bool b) {return b; }))
            out << "F" << endl;
        else
            out << "S" << endl;
    }

    out.close();
    in.close();

    return 0;
}