#include <iostream>

int main()
{
    int h, m;
    std::cin >> h >> m;

    m -= 45;
    if (m < 0)
    {
        m = 60 + m;
        --h;
    }
    if (h < 0)
    {
        h = 24 + h;
    }
    std::cout << h << " " << m << std::endl;
    return 0;
}