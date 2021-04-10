#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("deck.inp");
    ofstream out("deck.out");

    size_t N;
    in >> N;

    vector<int> deck;
    deck.reserve(N);

    int temp, currentSum = 0;
    while (in >> temp)
    {
        deck.push_back(temp);
        currentSum += temp;
    }

    const int originalSum = ((N) * (N + 1)) / 2;
    const int missingNum = N - deck.size();
    int missingSum = originalSum - currentSum;
    //int currentSum;
    int currentMissingNum = missingNum;
    vector<int> missingDeck;
    for (int i = 0; i < missingNum; ++i)
    {
        int missingNumAvg = missingSum / currentMissingNum;
        int sumToMissingAvg = ((missingNumAvg) * (missingNumAvg + 1)) / 2;
        int currentSumToAvg = 0;
        for (int num : deck)
            if (num <= missingNumAvg)
                currentSumToAvg += num;
        const int foundMissingNum = sumToMissingAvg - currentSumToAvg;
        missingDeck.push_back(foundMissingNum);
        deck.push_back(foundMissingNum);
        --currentMissingNum;
        missingSum -= foundMissingNum;
    }

    for (int num : missingDeck)
        out << num << '\n';

    out.close();
    in.close();

    return 0;
}