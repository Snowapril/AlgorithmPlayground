#include <iostream>
#include <iomanip>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int numCase;
    std::cin >> numCase;
    while(numCase--)
    {
        int numScore, tempScore;
        float totalScore { 0 };
        std::cin >> numScore;
        for (int i = 0; i < numScore; ++i)
        {
            std::cin >> tempScore;
            totalScore += tempScore;
        }
        totalScore /= numScore;
        std::cout << std::fixed << std::setprecision(3) << std::setfill('0') << totalScore << "%\n";
    }

    return 0;
}