#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    
    ifstream in("palin.inp");
    ofstream out("palin.out");

    int numCase;
    string sentence;

    in >> numCase;
    for (int i = 0; i < numCase; ++i)
    {
        in >> sentence;

        const int length = static_cast<int>(sentence.length());
        int answer = 1;
        for (int beg = 0, ate = length - 1; answer < 3 && beg < ate; ++beg, --ate)
        {
            if (sentence[beg] != sentence[ate])
            {
                if (sentence[beg] == sentence[ate - 1])
                {
                    ate = ate - 1;
                    ++answer;
                }
                else if (sentence[beg + 1] == sentence[ate])
                {
                    beg = beg + 1;
                    ++answer;
                }
                else
                {
                    answer = 3;
                }
            }
        }

        out << answer << '\n';
    }

    out.close();
    in.close();
    
    return 0;
}