#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define MAXN 5000 
#define MAXM 5000
using namespace std;

// 给定一个长度为 n 的序列 A 和一个长度为 m 的序列 B (n, m <= 5000), 求出一个最长的序列，使得该序列既是 A 的子序列，也是 B 的子序列

class Solution1 {
	int a[MAXN], b[MAXM], f[MAXN][MAXM];
	int n, m;
	
public:
	int dp(int n, int m) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (a[i] == b[j])
					f[i][j] = f[i-1][j-1] + 1;
				else
					f[i][j] = std::max(f[i-1][j], f[i][j-1]);
			}
		}
		return f[n][m];
	}
};
	
// 给定一个长度为 n 的序列 A (n <= 5000), 求出一个最长的 A 的子序列，满足该子序列的后一个元素不小于前一个元素

class Solution2 {
	int a[MAXN], d[MAXN];
	int n;
	
public:
	
	int dp() {
		d[1] = 1;
		int ans = 1;
		for (int i = 2; i <= n; i++) {
			d[i] = 1;
			for (int j = 1; j < i; j++) {
				d[i] = max(d[i], d[j] + 1);
				ans = max(ans, d[i]);
			}
		}
		return ans;
	}
};

class Solution3 {
	int a[MAXN], dp[MAXN];
	int n;
	
	int dp() {
		int mx;
		int ans;
		for (int i = 0; i < n; i++) scanf("%d", a + i);
		memset(dp, 0x1f, sizeof (dp));
		mx = dp[0];
		for (int i = 0; i < n; i++) {
			*std::upper_bound(dp, dp + n, a[i]) = a[i];
		}
		ans = 0;
		while (dp[ans] != mx) ++ans;
	}
};
