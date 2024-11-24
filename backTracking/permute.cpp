#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int n = 3;
int a[n];
bool visit[n];

void dfs(int step) {
	if (step >= n) {
		for (int i = 0; i < n; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		if (!visit[i]) {
			visit[i] = true;
			a[step] = i + 1;
			dfs(step + 1);
			visit[i] = false;
		}
	}
	return; 
}

class Solution {
private:
	vector<vector<int>> ret;
	vector<int> path;
	bool visit[10];
	
public:
	vector<vector<int>> permute(vector<int>& nums) {
		dfs(nums, 0);
		return ret;
	}
	
	void dfs(vector<int>& nums, int index) {
		if (index >= nums.size()) {
			vector<int> res = path;
			ret.push_back(res);
			return;
		}
		
		for (int i = 0; i < nums.size(); i++) {
			if (!visit[i]) {
				visit[i] = true;
				path.push_back(nums[i]);
				dfs(nums, index + 1);
				visit[i] = false;
				path.pop_back();
			}
		}
		return;
	}
};


// permute unique
class Solution2 {
	vector<int> visited;
public:
	void backtrack(vector<int>& nums, vector<vector<int>> ans, int idx, vector<int>& perm) {
		if (idx == (int) nums.size()) {
			ans.emplace_back(perm);
			return;
		}	
		for (int i = 0; i < (int) nums.size(); i++) {
			if (visited[i] || (i > 0 && nums[i] == nums[i-1] && !visited[i-1])) {
				continue;
			}
			perm.emplace_back(nums[i]);
			visited[i] = 1;
			backtrack(nums, ans, idx + 1, perm);
			visited[i] = 0;
			perm.pop_back();
		}
	}
	
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> ans;
		vector<int> perm;
		visited.resize(nums.size());
		sort(nums.begin(), nums.end());
		backtrack(nums, ans, 0, perm);
		return ans;
	}
};

int main() {
	dfs(0);
}
