#include <iostream>
#include <functional>
#include <vector>

int main()
{
    std::cin.tie(NULL); std::ios_base::sync_with_stdio(false);

    int numNode, numEdge;
    std::cin >> numNode >> numEdge;

    std::vector<std::vector<bool>> graph(numNode, std::vector<bool>(numNode, false));
    std::vector<bool> visit(numNode, false);
    for (int i = 0; i < numEdge; ++i)
    {
        int p, q;
        std::cin >> p >> q;
        graph[p - 1][q - 1] = true;
        graph[q - 1][p - 1] = true;
    }

    std::function<void(int)> dfs;
    int numInfected = 0;
    dfs = [&](int cur) {
        visit[cur] = true;
        ++numInfected;
        for (int i = 0; i < numNode; ++i)
        {
            if (graph[cur][i] && !visit[i])
                dfs(i);
        }
    };

    dfs(0);
    std::cout << numInfected - 1;

    return 0;
}