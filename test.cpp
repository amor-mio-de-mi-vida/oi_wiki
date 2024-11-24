#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
	vector<int>a1;
	vector<int>a2;
	
	a1.push_back(1);
	a1.push_back(2);
	a1.push_back(3);
	
	a2.push_back(1);
	a2.push_back(2);
	a2.push_back(3);
	
	set<vector<int>> b;
	
	b.insert(a1);
	b.insert(a2);
	
	cout << b.size() << endl;
	return 0;
	
}
