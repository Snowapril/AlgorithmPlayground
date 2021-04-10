#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    ifstream in("words.inp");
    ofstream out("words.out");

    size_t numWords;
    in >> numWords;
    const size_t majorityNum = (numWords >> 1) + 1;

    vector<string> words(numWords);
    size_t majorityIdx = 0, majorityCount = 1;
    in >> words[0];
    for (size_t i = 1; i < numWords; ++i)
    {
        in >> words[i];
        majorityCount = (words[i] == words[majorityIdx]) ? majorityCount + 1 : majorityCount - 1;

        if (majorityCount == 0)
        {
            majorityIdx = i;
            majorityCount = 1;
        }
    }

    const size_t candidateNum = std::count(words.cbegin(), words.cend(), words[majorityIdx]);
    if (candidateNum >= majorityNum)
        out << words[majorityIdx];
    else
        out << "NONE";

    out.close();
    in.close();
    
    return 0;
}