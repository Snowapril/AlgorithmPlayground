#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;
#include <iostream>
#include <iomanip>

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
        cin >> score;

    string music;
    cin >> music;

    using Coord = pair<size_t, size_t>;
    using Node = pair<Coord, int>;
    const size_t musicLength = music.length() + 1;
    vector<vector<Node>> DP(musicLength, vector<Node>(musicLength));
    vector<Coord> localMaxNodes;

    //! Bottom-top DP - Smith Waterman algorithm
    for (size_t i = 1; i < musicLength/2; ++i) {

        for (size_t j = i + 2; j < musicLength; ++j) {
            const int matchScore = music[i - 1] == music[j - 1] ? scores[MATCH] : scores[MISMATCH];
            vector<Node> candidates = {
                make_pair(make_pair(i - 1, j - 1), DP[i - 1][j - 1].second + matchScore),//! LEFT-TOP
                make_pair(make_pair(i - 1,   j  ), DP[i - 1][j].second + scores[GAP]   ),//! TOP
                make_pair(make_pair(i  , j - 1  ), DP[i][j - 1].second + scores[GAP]   ),//! LEFT
                make_pair(make_pair(  0  ,   0  ),                    0                ) //! NONE
            };
            auto maxNode = *max_element(candidates.begin(), candidates.end(), [](Node node1, Node node2) {
                return node1.second < node2.second;
                });
            if (maxNode.second > 0)
                swap(DP[i][j], maxNode);
            if (localMaxNodes.empty())
                localMaxNodes.push_back(make_pair(i, j));
            else
            {
                Coord localMaxCoord = localMaxNodes.front();
                if (DP[localMaxCoord.first][localMaxCoord.second].second < DP[i][j].second)
                    localMaxNodes = { make_pair(i,j) };
                else if (DP[localMaxCoord.first][localMaxCoord.second].second == DP[i][j].second)
                    localMaxNodes.emplace_back(i, j);
            }
        }
    }

    //! Debugging
    cout << "      ";
    for (size_t i = 0; i < musicLength; ++i)
        cout << setw(3) << music[i];
    cout << endl;
    for (size_t i = 0; i < musicLength/2; ++i) {
        if (i == 0) cout << "   ";
        else cout << setw(3) << music[i - 1];
        for (size_t j = 0; j < musicLength; ++j) {
            cout << setw(3) << DP[i][j].second;
        }
        cout << endl;
    }

    size_t cost = 0;
    string answer_str1, answer_str2;
    Coord beginCoord = { numeric_limits<size_t>::max() , numeric_limits<size_t>::max() };
    for (Coord currentCoord : localMaxNodes)
    {
        cost = DP[currentCoord.first][currentCoord.second].second;
        string substr1, substr2;
        size_t substr1_idx, substr2_idx;
        substr1_idx = substr2_idx = numeric_limits<size_t>::max();
        while (DP[currentCoord.first][currentCoord.second].second > 0)
        {
            substr1_idx = currentCoord.first; substr2_idx = currentCoord.second;
            Coord prevCoord = DP[currentCoord.first][currentCoord.second].first;
            if (currentCoord.first - prevCoord.first == 1)
                substr1.push_back(music[currentCoord.first - 1]);
            if (currentCoord.second - prevCoord.second == 1)
                substr2.push_back(music[currentCoord.second - 1]);
            currentCoord = prevCoord;
        }

        if (beginCoord.first > substr1_idx || (beginCoord.first == substr1_idx && beginCoord.second > substr2_idx))
        {
            answer_str1 = substr1; answer_str2 = substr2;
            beginCoord.first = substr1_idx; beginCoord.second = substr2_idx;
        }
    }

    reverse(answer_str1.begin(), answer_str1.end());
    reverse(answer_str2.begin(), answer_str2.end());

    cout << answer_str1 << endl;
    cout << answer_str2 << endl;
    cout << cost;

    out.close();
    in.close();

    return 0;
}