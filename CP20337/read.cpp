#include <algorithm>
#include <fstream>
#include <array>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <string.h>

using namespace std;

struct metadata {
    vector<string>::iterator first;
    vector<string>::iterator last;
    size_t base;
};

int main()
{
    FILE* in = fopen("read.inp", "r");
    FILE* out = fopen("read.out", "w");

    //! ��ü ������ �ѹ��� �� �о�ɴϴ�.
    fseek(in, 0, SEEK_END);
    const size_t size = ftell(in);
    vector<char> dnaContents(size);
    fseek(in, 0, SEEK_SET);
    fread(dnaContents.data(), 1, size, in);

    //! �ѹ��� �о�� ������ \n token���� �� �и��س��ϴ�.
    vector<string> dnaStrings;
    dnaStrings.reserve(200000);
    char* p, * temp;
    p = strtok_s(dnaContents.data(), "\n", &temp);
    do {
        dnaStrings.emplace_back(p);
    } while ((p = strtok_s(NULL, "\n", &temp)) != NULL);

    const array<size_t, 4> targets{
        static_cast<size_t>(dnaStrings.size() * 0.2),
        static_cast<size_t>(dnaStrings.size() * 0.4),
        static_cast<size_t>(dnaStrings.size() * 0.6),
        static_cast<size_t>(dnaStrings.size() * 0.8)
    };

    //! �߰� �޸𸮸� �������� �ʰ� dnaStrings ���ο��� radix sort�ϴ� �Լ��Դϴ�.
    //! out-place radix sort�� �����ϸ� ���� ������ �� �����ѵ� �׳� inplace�� �����߽��ϴ�.
    auto InplaceRadixSort = [](vector<string>::iterator first, vector<string>::iterator last, size_t base)
    {
        metadata a, c, g, t;
        a.base = c.base = g.base = t.base = base + 1;

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

        return make_tuple(a, c, g, t);
    };

    list<metadata> radixTree{ { dnaStrings.begin(), dnaStrings.end(), 0 } };
    for (auto targetIter = targets.begin(); targetIter != targets.end(); ++targetIter)
    {
        size_t targetIndex = *targetIter + 1;

        for (auto iter = radixTree.begin(); iter != radixTree.end();)
        {
            const size_t length = distance(iter->first, iter->last);
            if (length == 0)
            {
                iter = radixTree.erase(iter);
                continue;
            }

            if (length < targetIndex)
            {
                targetIndex -= length;
                ++iter;
            }
            else
            {
                if (targetIndex <= length && (*(iter->first) == *(iter->last - 1)) ||
                    (targetIndex == length && length == 1))
                {
                    fprintf(out, "%s\n", iter->first->c_str());
                    break;
                }
                else
                {
                    metadata a, c, g, t;
                    tie(a, c, g, t) = InplaceRadixSort(iter->first, iter->last, iter->base);
                    iter = radixTree.erase(iter);
                    iter = radixTree.insert(iter, { a, c, g, t });
                }
            }
        }
    }

    fclose(out);
    fclose(in);
    return 0;
}