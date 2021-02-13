#include <iostream>
#include <vector>
#include <string>
#include <limits>

int main()
{
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);
	
	int row, col, K;
	std::cin >> row >> col;

	std::vector<std::string> table(row);
	for (int i = 0; i < row; ++i)
	{
		std::cin >> table[i];
	}

	std::cin >> K;

	int maxResult = std::numeric_limits<int>::min();
	for (const auto& rowLamps : table)
	{
		int numOff = 0;
		for (char c : rowLamps)
			if (c == 48)
				++numOff;

		int sum = 0;
		if (numOff <= K && (numOff % 2 == K % 2))
		{
			for (const auto& otherRowLamps : table)
			{
				if (rowLamps == otherRowLamps)
					++sum;
			}
		}

		maxResult = std::max(maxResult, sum);
	}

	std::cout << maxResult;
	return 0;
}