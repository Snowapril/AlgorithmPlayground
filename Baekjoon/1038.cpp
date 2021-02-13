#include <iostream>
#include <array>
#include <algorithm>

std::array<size_t, 1024> decNums;
unsigned int count = 0;

void dfs(size_t value)
{
	size_t val = value % 10, current = value * 10;
	for (size_t i = 0; i < val; ++i)
	{
		decNums[count++] = current + i;
		dfs(current + i);
	}
}

int main()
{
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);

	size_t order;
	std::cin >> order;

	for (int i = 0; i < 10; ++i)
	{
		decNums[count++] = i;
		dfs(i);
	}

	std::sort(decNums.begin(), decNums.begin() + count);

	if (order >= count) std::cout << -1;
	else std::cout << decNums[order];

	return 0;
}