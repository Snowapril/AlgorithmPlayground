#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

/**
input file:
5
10010
01011
10100
00010
10111
output file:
NONE 또는 celebrity의 순서
**/

int main()
{
    ifstream in("celebrity.inp");
    ofstream out("celebrity.out");

    int numPeople;
    in >> numPeople;

    vector<vector<int>> relation(numPeople, vector<int>(numPeople));
    string temp;
    for (auto& row : relation)
    {
        in >> temp;
        transform(temp.begin(), temp.end(), row.begin(), [](char c){
            return c - '0';
        });
    }

    using iter = vector<int>::iterator;
    function<vector<int>(const vector<int>&)> solver;
    solver = [&relation, &solver](const vector<int>& people) -> vector<int> {
        if (people.size() <= 1)
            return people;
        else if (people.size() == 2)
        {
            int l = people[0], r = people[1];
            if (relation[l][r] == 1 &&
                relation[r][l] == 0)
                return { r };
            else if (relation[l][r] == 0 &&
                     relation[r][l] == 1)
                return { l };
            else
                return {};
        }

        const size_t middle_idx = people.size() >> 1;
        vector<int> left_celebs = solver(vector<int>(people.begin(), people.begin() + middle_idx));
        vector<int> right_celebs = solver(vector<int>(people.begin() + middle_idx, people.end()));

        vector<int> merged;
        merged.reserve(left_celebs.size() + right_celebs.size());
        merged.insert(merged.end(), left_celebs.begin(), left_celebs.end());
        merged.insert(merged.end(), right_celebs.begin(), right_celebs.end());

        return solver(merged);
    };

    vector<int> people(numPeople);
    iota(people.begin(), people.end(), 0);

    auto celebs = solver(people);
    if (celebs.empty())
        out << "NONE";
    else
        out << celebs[0] + 1;
    out.close();
    in.close();

    return 0;
}