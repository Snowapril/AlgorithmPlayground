#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> sequence(N), dp(N);
    for (int i = 0; i < N; ++i)
        cin >> sequence[i];

    for (int i = 0; i < N; ++i)
    {
        dp[i] = sequence[i];
        for (int j = 0; j < i; ++j)
        {
            if (sequence[i] > sequence[j])
                dp[i] = max(dp[i], dp[j] + sequence[i]);
        }
    }

    cout << *max_element(dp.begin(), dp.end());
    return 0;
}