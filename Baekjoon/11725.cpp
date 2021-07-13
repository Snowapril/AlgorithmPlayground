#include <iostream>
#include <vector>
#include <list>
#include <queue>

int main()
{
    std::cin.tie(NULL); std::ios_base::sync_with_stdio(false);
    int numNode;
    std::cin >> numNode;

    std::vector<std::list<int>> graph(numNode + 1);
    int p, q;
    while (std::cin >> p >> q)
    {
        graph[p].push_back(q);
        graph[q].push_back(p);
    }

    std::vector<int> rootedGraph(numNode + 1);
    std::vector<bool> visit(numNode + 1, false);
    std::queue<int> bfsQueue;
    bfsQueue.push(1);
    
    while (!bfsQueue.empty())
    {
        int node = bfsQueue.front();
        bfsQueue.pop();

        visit[node] = true;

        for (int target : graph[node])
        {
            if (!visit[target])
            {
                rootedGraph[target] = node;
                bfsQueue.push(target);
            }
        }
    }

    for (int i = 2; i < numNode + 1; ++i)
        std::cout << rootedGraph[i] << '\n';

    return 0;
}