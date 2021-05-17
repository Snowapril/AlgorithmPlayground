#include <fstream>
#include <bitset>
#include <stack>
#include <queue>
#include <array>
#include <algorithm>
#include <vector>
#include <limits>
#include <numeric>

using namespace std;

#define ATOI(a) ((a) - 'a')
#define ITOA(i) (static_cast<char>((i) + 'a'))
constexpr int MAX_NODES = 26;


int main()
{
	ifstream in("iron.inp");
	ofstream out("iron.out");

	int N, M;
	in >> N >> M;
	array<int, MAX_NODES* MAX_NODES> graph{ 0, };
	array<int, MAX_NODES> maxWeights{ 0, };
	for (int i = 0, weight; i < M; ++i)
	{
		char c1, c2;
		in >> c1 >> c2 >> weight;
		graph[ATOI(c1) * MAX_NODES + ATOI(c2)] = weight;
		graph[ATOI(c2) * MAX_NODES + ATOI(c1)] = weight;
		
		if (maxWeights[ATOI(c1)] < weight)
			maxWeights[ATOI(c1)] = weight;
		if (maxWeights[ATOI(c2)] < weight)
			maxWeights[ATOI(c2)] = weight;
	}

	int localOptima = -1;
	int localOptimaDepth = -1;

	struct queue_node {
		int index{ 0 };
		int prevIndex{ 0 };
		int curDist{ 0 };
		int expectedDist{ 0 };
		string path;
		bitset<MAX_NODES> visit{ 0 };
	};

	auto cmp = [](const queue_node& node1, const queue_node& node2) -> bool {
		return (node1.curDist + node1.expectedDist) < (node2.curDist + node2.expectedDist);
	};

	priority_queue<queue_node, vector<queue_node>, decltype(cmp)> pq(cmp);
	pq.emplace(ATOI('a'),
			  0,
			  0, 
			  accumulate(maxWeights.begin(), maxWeights.end(), 0),
			  "a",
			  bitset<MAX_NODES>() 
	);

	string optimalPath;

	while (!pq.empty())
	{

		auto candidate = pq.top();
		pq.pop();

		if (candidate.curDist + candidate.expectedDist < localOptima)
			continue;

		const int baseAddr = MAX_NODES * candidate.index;
		for (int i = 0; i < MAX_NODES; ++i)
		{
			if (graph[baseAddr + i] && i != candidate.prevIndex && !candidate.visit.test(i))
			{
				queue_node node = candidate; 
				node.curDist += graph[baseAddr + i];
				if (i == 0)
				{
					if (node.curDist > localOptima)
					{
						localOptima = node.curDist;
						localOptimaDepth = node.path.length();
						optimalPath = move(node.path);
					}
					else if (node.curDist == localOptima && (node.path.length() > localOptimaDepth || node.path < optimalPath))
					{
						localOptimaDepth = node.path.length();
						optimalPath = move(node.path);
					}
					continue;
				}
				node.expectedDist -= maxWeights[i];
				if (node.curDist + node.expectedDist < localOptima)
					continue;
				node.prevIndex = node.index;
				node.index = i;
				node.path.push_back(ITOA(i));
				node.visit.set(i);
				pq.emplace(move(node));
			}
		}
	}

	out << localOptima << '\n';
	for (char c : optimalPath)
		out << c << ' ';

	out.close();
	in.close();
}