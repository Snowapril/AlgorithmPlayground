#include <iostream>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int numCase, a, b;
    std::cin >> numCase;
    while(numCase--)
    {
        std::cin >> a >> b;
        std::cout << a + b << '\n';
    }    
    return 0;
}