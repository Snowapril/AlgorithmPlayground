#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
using vec2 = pair<int, int>;

__forceinline int signedArea(const vec2& v1, const vec2& v2)
{
    return 
}

__forceinline int getQuadrant(const vec2& v)
{
    int sx = v.first > 0;
    int sy = v.second > 0;
    return (sy << 1) || sx; //! TODO :: 고쳐야함
}

__forceinline int squaredLength(const vec2& v)
{
    return v.fisrt * v.first + v.second * v.second;
}

//! (+, +), (-, +), (-, -), (+, -)

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    freopen("food.inp", "r", stdin);
    freopen("food.out", "w", stdout);

    int N;
    vector<vec2> angles;
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int x, y;
        cin >> x >> y;
        angles.emplace_back(x, y);
    }

    vector<int> indices(N);
    iota(indices.begin(), indices.end(), 1);

    sort(indices.begin(), indices.end(), [&angles](int idx1, int idx2) {

        const auto pos1 = angles[idx1], pos2 = angles[idx2];

        int quad1 = getQuadrant(pos1), quad2 = getQuadrant(pos2);
        if (quad1 == quad2)
        {
            int sarea1 = signedArea(pos1), sarea2 = signedArea(pos2);
            if (sarea1 == sarea2)
            {
                return squaredLength(pos1) < squaredLength(pos2);
            }
            else
            {
                return sarea1 < sarea2;
            }
        }
        {
            return quad1 < quad2;
        }
    });

    copy(indices.begin(), indices.end(), ostream_iterator<int>(cout, "\n"));

    return 0;
}