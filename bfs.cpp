#include <iostream>
#include <queue>

using namespace std;

vector<vector<int>> adj;
queue<int> Q;
vector<bool> vis;
vector<int> d;
vector<int> p;

void bfs(int u) {
	Q.push(u);
	vis[u] = true;
	d[u] = 0;
	p[u] = -1;
	
	while(!Q.empty()) {
		u = Q.front();
		Q.pop();
		
		for (int n : adj[u]) {
			if (!vis[n]) {
				Q.push(n);
				vis[n] = true;
				d[n] = d[u] + 1;
				p[n] = u;
			}
		}
	}
}
