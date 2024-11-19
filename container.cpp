#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


int main() {
	/**************** vector *******************/
	
	// 1. 创建空vector; 常数复杂度 
	vector<int> v0; 
	// 1+. 这句代码可以使得向vector中插入前3个元素时，保证常数时间复杂度 
	v0.reserve(3); 
	// 2. 创建一个初始空间为3的vector，其元素的默认值是0; 线性复杂度 
	vector<int> v1(3); 
	// 3. 创建一个初始空间为3的vector，其元素的默认值是2; 线性复杂度 
	vector<int> v2(3, 2); 
	// 4. 创建一个初始空间为3的vector，其元素的默认值是1， 并且使用v2的空间配置器; 线性复杂度 
	vector<int> v3(3, 1, v2.get_allocator()); 
	// 5. 创建一个v2的拷贝vector v4， 其内容元素和v2一样; 线性复杂度 
	vector<int> v4(v2); 
	// 6. 创建一个v4的拷贝vector v5，其内容是{v4[1], v4[2]}; 线性复杂度 
	vector<int> v5(v4.begin() + 1, v4.begin() + 3); 
	// 7. 移动v2到新创建的vector v6，不发生拷贝; 常数复杂度; 需要 C++11 
	vector<int> v6(std::move(v2)); // 或者 v6 = std::move(v2);
	
	v0.push_back(10);
	int* p0 = v0.data();
	cout << "the dirst data of v0 is " << *p0 << endl;
	// *p is 10
	
	v0.insert(v0.begin(),2);
	int* p1 = v0.data();
	cout << "the dirst data of v0 is " << *p1 << endl;
	
	auto t = v0.erase(v0.begin());
	cout  << *t << endl;
	
	
	vector<int> src = {1, 2, 3, 4, 5};
	vector<int> dst(5);
	
	partial_sum(src.begin(), src.end(), dst.begin());
	for (unsigned int i = 0; i < dst.size(); i++) 
		cout << dst[i] << " ";
	cout << endl;
	
	
	int N = 10, a[] = {1, 3, 3, 7, 2, 5, 1, 2, 4, 6}, k=3;
	sort(a, a + N);
	int cnt = unique(a, a + N) - a;
	cout << "array size is " << cnt << " The 3th element is " << a[k-1];
	
	return 0;
}
