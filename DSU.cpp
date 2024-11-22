#include <iostream>

#define MAXSIZE 1000

int pre[MAXSIZE];
int rank[MAXSIZE];

void init(int n) {
	for (int i = 0; i < n; i++) {
		pre[i] = i;
		rank[i] = 1;
	}
}

int find(int x) {
	if (pre[x] == x) return x;
	return find(pre[x]);
}

bool isSame(int x, int y) {
	return find(x) == find(y);
}

//void join(int x, int y) {
//	int fx = find(x), fy = find(y);
//	if (fx != fy)
//		pre[fx]=fy;
//}

bool join(int x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return false;
	else {
		if (rank[x] == rank[y])
			rank[y]++;
		pre[x] = y; 
	}
	return true;
}

