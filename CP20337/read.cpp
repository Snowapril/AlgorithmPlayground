#include <algorithm>
#include <fstream>
#include <array>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <tuple>

using namespace std;
#include <iostream>
#include <chrono>
vector<string> strings;

struct metadata {
    vector<string>::iterator first, last;
    size_t base;
};
tuple<metadata, metadata, metadata, metadata> InplaceRadixSort(vector<string>::iterator first, vector<string>::iterator last, size_t base);

int main()
{
    ifstream in("input.inp", ios::ate);
    ofstream out("read.out");
    
    //! 1. Read inputs
    auto st = chrono::high_resolution_clock::now();

    const size_t size = in.tellg();
    vector<char> dnaCache(size);
    in.seekg(ios::beg);
    in.read(dnaCache.data(), size);

    strings.reserve(200000);
    char* p = strtok(dnaCache.data(), "\n");
    do {
        strings.emplace_back(p);
    } while ((p = strtok(NULL, "\n")) != NULL);

    cout << "read : " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - st).count() << "(ms)" << endl;

    //! 2. Radix sorting
    const size_t numStrings = strings.size();
    array<size_t, 4> targets{ numStrings / 5.0f, 2 * numStrings / 5.0f, 3 * numStrings / 5.0f, 4 * numStrings / 5.0f };

    list<metadata> radixCache;
    radixCache.push_back({ strings.begin(), strings.end(), 0 });
    metadata a, c, g, t;
    list<metadata>::iterator radixIter = radixCache.begin();
    size_t targetIdx = 0;
    while (targetIdx != targets.size())
    {
        st = chrono::high_resolution_clock::now();
        tie(a, c, g, t) = InplaceRadixSort(radixIter->first, radixIter->last, radixIter->base);
        radixIter = radixCache.erase(radixIter);
        radixCache.insert(radixIter, { a, c, g, t });
        cout << "radix sort : " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - st).count() << "(ms)" << endl;

        size_t accmulated = 0;
        for (auto iter = radixCache.begin(); iter != radixCache.end();)
        {
            const size_t length = iter->last - iter->first;
            if (length == 0)
                iter = radixCache.erase(iter);
            else
            {
                if (accmulated + length < targets[targetIdx])
                {
                    accmulated += length;
                }
                else if (accmulated + length == targets[targetIdx])
                {
                    cout << *(iter->last) << ' ';
                    targetIdx++;
                    radixIter = next(iter, 1);
                    break;
                }
                else
                {
                    radixIter = iter;
                    break;
                }

                ++iter;
            }
        }
    }

    out.close();
    in.close();
    return 0;
}

tuple<metadata, metadata, metadata, metadata> InplaceRadixSort(vector<string>::iterator first, vector<string>::iterator last, size_t base)
{
    metadata a, c, g, t;
    vector<string>::iterator aPos = first, tPos = last;
    a.first = aPos; t.last = tPos;
    for (auto iter = aPos; iter != tPos;)
    {
        if (iter->size() <= base || iter->at(base) == 'a')
        {
            swap(*iter, *(aPos++));
            ++iter;
        }
        else if (iter->at(base) == 't')
            swap(*iter, *(--tPos));
        else
            ++iter;
    }
    a.last = aPos; t.first = tPos;

    vector<string>::iterator cPos = aPos;
    c.first = cPos; g.last = tPos;
    for (auto iter = cPos; iter != tPos; ++iter)
    {
        if (iter->at(base) == 'c')
            swap(*iter, *(cPos++));
    }
    c.last = g.first = cPos;

    a.base = c.base = g.base = t.base = base + 1;
    return make_tuple(a, c, g, t);
}