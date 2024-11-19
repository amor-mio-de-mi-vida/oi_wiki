#include <iostream>
#include <queue>

using namespace std;
#define DEFAULT_CAPACITY 30

template<class T>
class BinaryHeap {
private:
	vector<T> heap;
	
	void swim(T k) {
		while (k > 1 && heap[k/2] < heap[k]) {
			swap(heap[k/2], heap[k]);
			k /= 2;
		}
	}
	
	void sink(T k) {
		while(k * 2 <= heap.size()) {
			T t = k * 2;
			if (t+1 <= heap.size() && heap[t+1] > heap[t]) t++;
			if (heap[t] <= heap[k]) break;
			swap(heap[t], heap[k]);
			k = t;
		}
	}
	
public:
	void insert(T element) {
		heap.push_back(element);
		swim(heap.size());
	}
	
	T delMax() {
		if (heap.empty()) {
			throw out_of_range("Heap is empty");
		}
		
		T max = heap[0];
		swap(heap[0], heap.back());
		heap.pop_back();
		sink(1);
		return max;
	}

};
