#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(NULL); std::ios_base::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    int accumulate = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> matrix[i][j];
            matrix[i][j] += accumulate;
            accumulate = matrix[i][j];
        }
    }
    
    for (int i = 0; i < m; i++)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cout << matrix[x1][y1] - matrix[x2][y2] << std::endl;
    }

    return 0;
}