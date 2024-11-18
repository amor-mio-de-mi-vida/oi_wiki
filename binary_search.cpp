#include <iostream>

using namespace std;
#define CAPACITY 100

int arr[CAPACITY];

int binary_search(int start, int end, int key) {
	int ret = -1; 
	int mid;
	
	while (start <= end) {
		mid = start + ((end - start) >> 1);
		if (arr[mid] < key) {
			start = mid + 1;
		} else if (arr[mid] > key) {
			end = mid - 1;
		} else {
			ret = mid;
			break;
		}
	}
	return ret;
}

int compare(const void* p1, const void* p2) {
	if (*((int*)p1) > *((int*)p2)) {
		return 1;
	} else if (*((int*)p1) < *((int*)p2)){
		return -1;
	} else {
		return 0;
	}
}

int lower(const void *p1, const void *p2) {
	int *a = (int *)p1;
	int *b = (int *)p2;
	if ((b != arr || compare(a, b - 1) > 0) && compare(a, b) > 0)
		return 1;
	else if (b != arr && compare(a, b - 1) <= 0)
		return -1;
	else 
		return 0;
}

int upper(const void* p1, const void* p2) {
	int *a = (int *)p1;
	int *b = (int *)p2;
	if ((b == arr || compare(a, b - 1) >= 0) && compare(a, b) >= 0)
		return 1;
	else if (b != arr && compare(a, b - 1) < 0)
		return -1;
	else 
		return 0;
}
