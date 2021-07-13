#include <iostream>
#include <array>
#include <vector>
#include <queue>

int main()
{
    std::cin.tie(NULL); std::ios_base::sync_with_stdio(false);

    constexpr int dx[4] = {0, 1, 0, -1};
    constexpr int dy[4] = {1, 0, -1, 0};

    int width, height;
    std::cin >> height >> width;

    std::array<std::array<int, 8>, 8> map;
    std::vector<std::pair<int,int>> bruteForce;
    std::queue<std::pair<int, int>> bfsQueue;
    bruteForce.reserve(width * height);
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
        {
            std::cin >> map[i][j];
            if (map[i][j] == 0) bruteForce.emplace_back(j, i);
            else if (map[i][j] == 2) bfsQueue.emplace(j, i);
        }
    
    const int numBruteForce = bruteForce.size();
    int maxNumSafeArea = -1;
    for (int i = 0; i < numBruteForce - 2; ++i)
    {
        for (int j = i + 1; j < numBruteForce - 1; ++j)
        {
            for (int k = j + 1; k < numBruteForce; ++k)
            {
                auto queueCopy = bfsQueue;
                auto mapCopy = map;
                mapCopy[bruteForce[i].second][bruteForce[i].first] = 1;
                mapCopy[bruteForce[j].second][bruteForce[j].first] = 1;
                mapCopy[bruteForce[k].second][bruteForce[k].first] = 1;
                
                int numSafeArea = numBruteForce - 3;
                while (!queueCopy.empty())
                {
                    auto node = queueCopy.front();
                    queueCopy.pop();

                    for (int i = 0; i < 4; ++i)
                    {
                        const std::pair<int,int> newNode = {node.first + dx[i], node.second + dy[i]};
                        if (newNode.first < 0 || newNode.first >= width ||
                            newNode.second < 0 || newNode.second >= height)
                            continue;
                        if (mapCopy[newNode.second][newNode.first] == 0)
                        {
                            mapCopy[newNode.second][newNode.first] = 2;
                            --numSafeArea;
                            queueCopy.push(newNode);
                        }
                    }
                }

                maxNumSafeArea = std::max(numSafeArea, maxNumSafeArea);
            }
        }
    }

    std::cout << maxNumSafeArea << '\n';

    return 0;
}