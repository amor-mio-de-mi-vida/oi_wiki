#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Khan algorithm
#define MAXN 1000
int n, m;
vector<int> G[MAXN];
int in[MAXN];

bool toposort_khan() {
	vector<int> L;
	queue<int> S;
	
	for (int i = 0; i < n; i++) {
		if (in[i] == 0)
			S.push(i);
	}
	
	while (!S.empty()) {
		int u = S.front();
		S.pop();
		L.push_back(u);
		
		for (auto v: G[u]) {
			if (--in[v] == 0) {
				S.push(v);
			}
		}
	}
	if (L.size() == n) {
		for (auto i : L) cout << i << " ";
		return true;
	}
	return false;
}

// dfs algorithm
using Graph = vector<vector<int>>;

struct TopoSort {
	enum class Status : uint8_t {to_visit, visiting, visited};
	
	const Graph& graph;
	const int n;
	vector<Status> status;
	vector<int> order;
	vector<int>::reverse_iterator it;
	
	TopoSort(const Graph& graph) 
	: graph(graph),
	n(graph.size()),
	status(n, Status::to_visit),
	order(n),
	it(order.rbegin()) {}
	
	bool sort() {
		for (int i = 0; i < n; i++) {
			if (status[i] == Status::to_visit && !dfs(i))
				return false;
		}
		return true;
	}
	
	bool dfs(const int u) {
		status[u] = Status::visiting;
		for (const int v : graph[u]) {
			if (status[v] == Status::visiting) return false;
			if (status[v] == Status::to_visit && !dfs(v)) return false;
		}
		status[u] = Status::visited;
		*it++ = u;
		return true;
	}
};
