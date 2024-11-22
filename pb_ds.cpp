#include <algorithm>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>

using namespace __gnu_pbds;
using pair_heap = __gnu_pbds::priority_queue<int>;
pair_heap q1; // 大根堆，配对堆
pair_heap q2; 
pair_heap::point_iterator id; // 一个迭代器

int main() {
	id = q1.push(1);
	// 堆中元素：[1];
	for (int i = 2; i <= 5; i++) q1.push(i);
	// 堆中元素：[1, 2, 3, 4, 5];
	std::cout << q1.top() << std::endl;
	// 输出结果：5;
	q1.pop();
	// 堆中元素：[1, 2, 3, 4];
	id = q1.push(10);
	// 堆中元素：[1, 2, 3, 4, 10];
	q1.modify(id, 1);
	// 堆中元素：[1, 1, 2, 3, 4];
	std::cout << q1.top() << std::endl;
	// 输出结果：4
	q1.pop();
	// 堆中元素 [1, 1, 2, 3];
	id = q1.push(7);
	// 堆中元素 [1, 1, 2, 3, 7];
	q1.erase(id);
	// 堆中元素 [1, 1, 2, 3];
	q2.push(1), q2.push(3), q2.push(5);
	// q1中元素：[1, 1, 2, 3], q2中元素：[1, 3, 5];
	q2.join(q1);
	// q1中无元素，q2中元素：[1, 1, 1, 2, 3, 3, 5];
	return 0;
}
