#include <iostream>
#include <vector>

int a[10];
bool visited[10];
int n;

void factorial(int step) {
	if (step == n+1) {
		for (int i = 1; i <= n; i++) {
			printf("%d", a[i]);
		}
		printf("\n");
		return;
	}
	
	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			visited[i] = true;
			a[step] = i;
			factorial(step+1);
			visited[i] = false;
		}
	}
	return;
}

int main() {
	std::cin >> n;

	factorial(1);
	
	return 0;
}
