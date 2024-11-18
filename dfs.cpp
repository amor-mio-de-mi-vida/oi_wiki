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

// optimize dfs


/*  记忆化搜索
 *
 *  int ans = 最坏情况, now;  // now 为当前答案
 *
 *  void dfs(传入数值) {
 *  if (到达目的地) ans = 从当前解与已有解中选最优;
 *  for (遍历所有可能性)
 * 		if (可行) {
 *  		进行操作;
 *  		dfs(缩小规模);
 * 			撤回操作;
 * 		}
 *	}
 */


/*

最优性剪枝

int g[MAXN];  // 定义记忆化数组
int ans = 最坏情况, now;

void dfs f(传入数值) {
	if (g[规模] != 无效数值) return;  // 或记录解，视情况而定
	if (到达目的地) ans = 从当前解与已有解中选最优;  // 输出解，视情况而定
	for (遍历所有可能性)
		if (可行) {
			进行操作;
			dfs(缩小规模);
			撤回操作;
		}
}

int main() {
	// ...
	memset(g, 无效数值, sizeof(g));  // 初始化记忆化数组
	// ...
}

*/

/*

可行性剪枝

int ans = 最坏情况, now;

void dfs(传入数值) {
	if (当前解已不可用) return;
	if (到达目的地) ans = 从当前解与已有解中选最优;
	for (遍历所有可能性)
		if (可行) {
		进行操作;
		dfs(缩小规模);
		撤回操作;
	}
}

*/


