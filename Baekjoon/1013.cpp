#include <iostream>
#include <string>

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int state_machine[8][2]{
        {1, 2}, {-1, 0}, {3, -1}, {4, -1},
        {4, 5}, {1, 6}, {7, 6}, {4, 0}
    };

    std::string pattern;
    int numCase;
    std::cin >> numCase;

    for (int i = 0; i < numCase; ++i)
    {
        std::cin >> pattern;
        int current_state = 0, next_state = 0;
        for (char inp : pattern)
        {
            inp -= 48;
            next_state = state_machine[current_state][inp];

            if (next_state == -1)
            {
                std::cout << "NO" << std::endl;
                break;
            }

            current_state = next_state;
        }

        if (next_state == -1)
            continue;

        if (current_state == 0 || current_state == 5 || current_state == 6)
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;

    }


    return 0;
}