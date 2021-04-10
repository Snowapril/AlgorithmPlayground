#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    ifstream in("deck.inp");
    ofstream out("deck.out");

    size_t N;
    in >> N;

    int temp;
    int sum = 0, squaredSum = 0;
    while (in >> temp)
    {
        sum += temp;
        squaredSum += temp * temp;
    }

    const int missingSum = ((N) * (N + 1)) / 2 - sum;
    const int missingSum2 = missingSum * missingSum;
    const int missingSquaredSum = ((N) * (N + 1) * (2 * N + 1)) / 6 - squaredSum;

    if (missingSum2 == missingSquaredSum)
    {
        out << missingSum;
    }
    else
    {
        const int sqrtElement = std::sqrt(8 * missingSquaredSum - 4 * missingSum2);
        int smallOne = (2 * missingSum - sqrtElement) / 4;
        int bigOne = missingSum - smallOne;
        out << smallOne << '\n' << bigOne;
    }
    
    out.close();
    in.close();

    return 0;
}