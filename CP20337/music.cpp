#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

enum {
    MATCH = 0,
    MISMATCH = 1,
    GAP = 2,
    LAST = 3
};  

int main() {
    ifstream in("music.inp");
    ofstream out("music.out");
    
    int scores[LAST];
    for (int& score : scores) 
        in >> score;

    string music;
    in >> music;
    
    using Coord = pair<size_t, size_t>;
    using Node = pair<Coord, int>;
    const size_t musicLength = music.length() + 1;
    vector<vector<Node>> DP(musicLength, vector<Node>(musicLength));

    //! Bottom-top DP - Smith Waterman algorithm
    for (size_t i = 1; i < musicLength; ++i) {
        for (size_t j = 1; j < musicLength; ++j) {
            const int matchScore = music[i - 1] == music[j - 1] ? scores[MATCH] : scores[MISMATCH];
            vector<Node> candidates = {
                make_pair(Coord(i - 1, j - 1), DP[i - 1][j - 1].second + matchScore ),//! LEFT-TOP
                make_pair(Coord(i - 1,   j  ), DP[i - 1][  j  ].second + scores[GAP]),//! TOP
                make_pair(Coord(  i  , j - 1), DP[i][j - 1].second     + scores[GAP]),//! LEFT
                make_pair(Coord(  0  ,   0  ),                    0                 ) //! NONE
            };
            auto maxNode = *max_element(candidates.begin(), candidates.end(), [](Node node1, Node node2) {
                return node1.second < node2.second;
            });
            if (maxNode.second > 0)
                swap(DP[i][j], maxNode);
        }
    }

    //! Fill the coordinates vector from (0, 0) to (N, N)
    vector<Coord> sortedCoords;
    sortedCoords.reserve(musicLength * musicLength);
    for (size_t i = 0; i < musicLength; ++i)
    for (size_t j = 0; j < musicLength; ++j)
        sortedCoords.emplace_back(i, j);
    
    //! Sort coordinates with it's matched DP table score.
    sort(sortedCoords.begin(), sortedCoords.end(), [&DP](Coord c1, Coord c2) {
        return DP[c1.first][c1.second].second > DP[c2.first][c2.second].second;
    });

    size_t max_cost = numeric_limits<size_t>::min();
    string max_substr1, max_substr2;
    Coord beginCoord = make_pair(numeric_limits<size_t>::max(), numeric_limits<size_t>::max());
    //! Back-trace for all coordinates
    for (Coord currentCoord : sortedCoords)
    {
        if (DP[currentCoord.first][currentCoord.second].second == 0)
            continue;

        Coord startCoord = currentCoord;
        string substr1, substr2;
        bool overlapped = false;
        while (!overlapped && DP[currentCoord.first][currentCoord.second].second > 0)
        {
            Coord prevCoord = DP[currentCoord.first][currentCoord.second].first;
            if (currentCoord.first - prevCoord.first == 1)
                substr1.push_back(music[currentCoord.first - 1]);
            if (currentCoord.second - prevCoord.second == 1)
                substr2.push_back(music[currentCoord.second - 1]);
            currentCoord = prevCoord;
            //! two substring overlapped detection
            if ((currentCoord.first <= currentCoord.second && currentCoord.second <= startCoord.first) ||
                (currentCoord.first <= startCoord.second && startCoord.second <= startCoord.first))
                overlapped = true;
        }

        //! Overlapped 인 경우 처리하는게없다

        if (DP[startCoord.first][startCoord.second].second < DP[currentCoord.first][currentCoord.second].second)
            continue;

        const size_t cost = DP[startCoord.first][startCoord.second].second - DP[currentCoord.first][currentCoord.second].second;
        if (max_cost < cost || (max_cost == cost && (beginCoord.first > currentCoord.first ||
            (beginCoord.first == currentCoord.first && beginCoord.second > currentCoord.second))))
        {
            if (currentCoord.first > currentCoord.second)
            {
                swap(currentCoord.first, currentCoord.second);
                swap(substr1, substr2);
            }

            max_cost = cost;
            max_substr1 = substr1;
            max_substr2 = substr2;
            beginCoord = currentCoord;
        }
    }

    reverse(max_substr1.begin(), max_substr1.end());
    reverse(max_substr2.begin(), max_substr2.end());

    out << max_substr1 << endl;
    out << max_substr2 << endl;
    out << max_cost;

    out.close();
    in.close();

    return 0;
}