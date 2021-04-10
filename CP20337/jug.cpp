#include <fstream>
#include <array>
#include <algorithm>

using namespace std;

constexpr int kMaxN = 100;
int main()
{
	ifstream in("jug.inp", ios::in);
	ofstream out("jug.out", ios::out);

	array<int, 4> actions;
	array<int, 10> problems;
	array<array<bool, 4>, kMaxN + 1> DP;
	for (int i = 1; i < 4; ++i)
		in >> actions[i];
	for (int i = 0; i < 10; ++i)
		in >> problems[i];
	
	//! Base condition
	DP[0] = { true, false, false, false };

	//! Precompute DP table.
	const int maxN = *max_element(problems.begin(), problems.end());
	for (int N = 1; N <= maxN; ++N)
	{
		//! Handle pass first.
		if (N < actions[1])
			DP[N][0] = true;
		else
			DP[N][0] = false;

		//! Handle s1, s2, s3
		for (int actionIdx = 1; actionIdx < 4; ++actionIdx)
		{
			int newN = N - actions[actionIdx];
			if (newN >= 0)
			{
				bool S_win = false;
				for (int i = 0; i < 4; ++i)
				{
					if (i != actionIdx)
						S_win |= DP[newN][i];
				}
				DP[N][actionIdx] = !S_win;
			}
			else
				DP[N][actionIdx] = false;
		}
	}

	for (int N : problems)
		if (any_of(DP[N].begin(), DP[N].end(), [](bool bWin) { return bWin; }))
			out << "F" << endl;
		else
			out << "S" << endl;

	out.close();
	in.close();
	return 0;
}