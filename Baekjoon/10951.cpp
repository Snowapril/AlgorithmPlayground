#include <iostream>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int a, b;
    while (std::cin >> a >> b)
    {
        std::cout << a + b << '\n';
    }

    return 0;
}