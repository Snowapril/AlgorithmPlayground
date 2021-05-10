#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void printStack(stack<int> s)
{
	stack<int> temp;
	while (s.empty() == false)
	{
		temp.push(s.top());
		s.pop();
	}
	while (temp.empty() == false)
	{
		cout << temp.top() << ' ';
		temp.pop();
	}
	cout << '\n';
}

int main()
{
	stack<int> stackPerm;

	//! initial setup
	int numPerm;
	cin >> numPerm;
	for (int i = 0; i < numPerm; ++i)
		stackPerm.push(i + 1);

	//! permutation
	vector<int> bin;
	do {
		printStack(stackPerm);

		bin.push_back(stackPerm.top());
		stackPerm.pop();

		int target = -1;
		bool found = false;
		while (!stackPerm.empty())
		{
			if (bin.back() > stackPerm.top())
			{
				target = stackPerm.top();
				bin.push_back(target);
				stackPerm.pop();
				found = true;
				break;
			}
			bin.push_back(stackPerm.top());
			stackPerm.pop();
		}

		if (!found)
			break;

		sort(bin.begin(), bin.end());
		for (auto iter = bin.begin(); iter != bin.end();)
		{
			if (*iter > target)
			{
				stackPerm.push(*iter);
				iter = bin.erase(iter);
				break;
			}
			else
			{
				++iter;
			}
		}

		for (auto iter = bin.begin(); iter != bin.end(); ++iter)
		{
			stackPerm.push(*iter);
		}
		bin.clear();

	} while (true);

	return 0;
}