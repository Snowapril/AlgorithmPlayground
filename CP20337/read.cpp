#include <algorithm>
#include <fstream>
#include <array>
#include <vector>
#include <iterator>
#include <string>
#include <tuple>

using namespace std;
#include <iostream>

vector<array<pair<vector<string>::iterator, vector<string>::iterator>, 4>> cache;
void radixSort(vector<string>::iterator first, vector<string>::iterator last, size_t radixIdx);

int main()
{
    ifstream in("read.inp");
    ofstream out("read.out");
    
    //! 1. Read whole input at once
    vector<string> strings;
    copy(istream_iterator<string>(in), istream_iterator<string>{}, back_inserter(strings));

    const size_t numStrings = strings.size();
    array<size_t, 4> targets{ numStrings / 5.f, 2 * numStrings / 5.f, 3 * numStrings / 5.f,4 * numStrings / 5.f };

    size_t targetIdx = 0;
    while (targetIdx == targets.size())
    {
        radixSort(strings.begin(), strings.end(), 0);

        //! Found targets[taretIdx]
        //! out << *iter << '\n';
        //! ++targetIdx;
    }

    out.close();
    in.close();
    return 0;
}

void radixSort(vector<string>::iterator first, vector<string>::iterator last, size_t radixIdx)
{
    vector<string> a, g, t, c;
    for (auto iter = first; iter != last; ++iter)
    {
        //! �̺κ� if �� �� ������ ���� �����ҵ�
        if (iter->size() <= radixIdx) 
            a.emplace_back(move(iter)); //! �� iter�� move�ϸ� ++iter ������ ���������� �ցٴ� �̰ŵ� ã�ƺ���
        else
        {
            char type = iter->at(radixIdx);
            switch (type)
            {
            case 'a':
                a.emplace_back(move(iter));
                break;
            case 'g':
                g.emplace_back(move(iter));
                break;
            case 't':
                t.emplace_back(move(iter));
                break;
            case 'c':
                c.emplace_back(move(iter));
                break;
            }
        }
    }
}