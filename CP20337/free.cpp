#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <tuple>

using namespace std;

using clean_work = tuple<int, int, int>;
using cost_term = tuple<int, int>;

cost_term get_cost_term(const clean_work& work);

int main()
{
    ifstream in("free.inp");
    ofstream out("free.out");

    int num_work;
    in >> num_work;

    vector<clean_work> works(num_work);
    for (auto& work : works)
        in >> get<0>(work) >> get<1>(work) >> get<2>(work);

    sort(works.begin(), works.end(), [](const clean_work& w1, const clean_work& w2) {
        return get<1>(w1) < get<1>(w2);
        });

    auto find_latest_overlapped = [&works](int idx) {
        auto iter = lower_bound(works.begin(), next(works.begin(), idx), works[idx], [](const clean_work& work, const clean_work& val) {
            return get<1>(work) < get<0>(val);
            });
        if (iter == works.end())
            return -1;
        else
            return static_cast<int>(iter - works.begin()) - 1;
    };

    vector<cost_term> dp(num_work);
    dp[0] = get_cost_term(works[0]);

    for (size_t i = 1; i < works.size(); ++i)
    {
        cost_term current_max_profit = get_cost_term(works[i]);

        int latest_overlapped = find_latest_overlapped(i);
        if (latest_overlapped != -1)
        {
            get<0>(current_max_profit) += get<0>(dp[latest_overlapped]) - 10;
            get<1>(current_max_profit) += get<1>(dp[latest_overlapped]);
        }

        cost_term prev_max_profit = dp[i - 1];
        if (get<0>(current_max_profit) < get<0>(prev_max_profit) ||
            (get<0>(current_max_profit) == get<0>(prev_max_profit) && get<1>(current_max_profit) > get<1>(prev_max_profit)))
        {
            swap(current_max_profit, prev_max_profit);
        }

        dp[i] = current_max_profit;
    }

    out << get<0>(dp.back()) << ' ' << get<1>(dp.back());

    out.close();
    in.close();

    return 0;
}

cost_term get_cost_term(const clean_work& work)
{
    return make_tuple(get<2>(work), get<1>(work) - get<0>(work) + 1);
}