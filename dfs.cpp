#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// stack implementation
vector<vector<int>> adj; 
vector<bool> vis;

void dfs_stack(int s) {
	stack<int> st;
	st.push(s);
	vis[s] = true;
	
	while(!st.empty()) {
		int u = st.top();
		st.pop();
		// do something
		
		for (int v: adj[u]) {
			if (!vis[v]) {
				vis[v] = true;
				st.push(v);
			}
		}
	}
}

// recursion implementation
void dfs_recursion(const int u, int d) {
	vis[u] = true;
	for (int v : adj[u]) {
		if (!vis[v]) 
			dfs_recursion(v, d + 1);
	}
	return;
}

