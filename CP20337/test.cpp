#include <fstream>
#include <stack>
#include <array>
#include <bitset>
using namespace std;
int main() {
	ifstream in("marathon.inp");
	ofstream out("marathon.out");
	int numEdge;
	in >> numEdge >> numEdge;
	array<int, 28> graph[28]{ 0, };
	for (int i = 0; i < numEdge; ++i) {
		char n1;
		char n2;
		int weight;
		in >> n1 >> n2 >> weight;
		n1 = n1 - 'a';
		n2 = n2 - 'a';
		graph[n2][n1] = weight;
		graph[n1][n2] = weight;
	}
	using path_type = stack<pair<pair<char, char>, array<int, 28>>>;
	path_type path;
	bitset<28> visit(0);
	path.emplace(pair(0, 0), graph[0]);
	int curDist = 0;
	path_type maxPath;
	int maxPathLen = -1;
	while (path.empty() == false) {
		auto& curNode = path.top();
		curNode.second[curNode.first.first] = 0;
		int nextIdx = -1;
		int weight = 0;
		for (int i = 0; i < 28; ++i)
			if (curNode.second[i] != 0 && !visit.test(i)) {
				weight = curNode.second[i];
				curNode.second[i] = 0;
				curDist += weight;
				path.emplace(pair(curNode.first.second, i), graph[i]);
				visit.set(i);
				nextIdx = i;
				break;
			}
		if (nextIdx == 0) {
			path.pop();
			visit.set(nextIdx, 0);
			if (curDist == 42 && maxPathLen < static_cast<int>(path.size())) {
				maxPathLen = path.size();
				maxPath = path;
			}
			curDist -= weight;
		}
		else if (curDist >= 42) {
			path.pop();
			visit.set(nextIdx, 0);
			curDist -= weight;
		}
		else if (nextIdx == -1) {
			path.pop();
			visit.set(curNode.first.second, 0);
			curDist -= graph[curNode.first.second][curNode.first.first];
		}
	}
	out << maxPathLen << '\n';
	stack<char> temp;
	while (maxPath.empty() == false)
	{
		temp.push(maxPath.top().first.second + 'a');
		maxPath.pop();
	}
	while (temp.empty() == false)
	{
		out << temp.top();
		if (temp.size() > 1)
			out << ' ';
		temp.pop();
	}
	out.close();
	in.close();
	return 0;
}