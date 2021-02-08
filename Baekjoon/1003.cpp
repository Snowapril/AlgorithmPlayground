#include <iostream>
#include <vector>

std::vector<long long> dp;

long long fibonacci(int n)
{
    if (dp[n] != -1) return dp[n];

    if (n == 0)
        return dp[0] = 0;
    else if (n == 1)
        return dp[1] = 1;
    else
        return dp[n] = fibonacci(n - 2) + fibonacci(n - 1);
}

void print_fibonacci_pair(int n)
{
    int zeroCnt = (n == 0) ? 1 : fibonacci(n - 1);
    int oneCnt = fibonacci(n);

    std::cout << zeroCnt << ' ' << oneCnt << std::endl;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    dp.assign(41, -1);

    int numCase, N;
    std::cin >> numCase;

    for (int i = 0; i < numCase; ++i)
    {
        std::cin >> N;
        print_fibonacci_pair(N);
    }

    return 0;
}