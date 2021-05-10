#include <iostream>
#include <array>
#include <stack>
#include <bitset>
#include <set>

void printStack(std::stack<std::bitset<4>> stack)
{
    while (stack.empty() == false)
    {
        std::cout << stack.top();
        stack.pop();
    }
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int N;
    std::cin >> N;

    std::array<double, 4> probabilities;
    for (double& p : probabilities)
    {
        std::cin >> p;
        p /= 100.0;
    }

    std::stack<std::bitset<4>> traverse;
    traverse.push(std::bitset<4>(0b1111));

    double complexProb = 0.0, currentProb = 1.0;
    std::pair<int, int> curCoord{ 0, 0 };
    std::set<std::pair<int, int>> coordPath;
    coordPath.insert(curCoord);

    while (!traverse.empty())
    {
        auto& visit = traverse.top();
        bool noWay = true;
        for (int i = 0; i < 4; ++i)
        {
            if (visit.test(i) && probabilities[i] > 1e-9)
            {
                traverse.push(std::bitset<4>(0b1111));
                visit.flip(i);
                currentProb *= probabilities[i];
                curCoord.first += (i & 1) * (-2) + 1;
                curCoord.second += ((i & 2) >> 1) * 2 - 1;
                if (coordPath.find(curCoord) != coordPath.end())
                {
                    complexProb += currentProb;
                    currentProb /= probabilities[i];
                    traverse.pop();
                }
                else
                {
                    coordPath.insert(curCoord);
                }
                noWay = false;
                break;
            }
        }
        printStack(traverse);

        if (noWay)
            traverse.
    }

    return 0;
}