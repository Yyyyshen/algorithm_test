// data_struct_cpp_08.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
/**
 * 堆
 * 是具有两个特殊属性的常规二叉树：
 * 堆必须是完整的二叉树
 * 必须根据堆顺序属性对节点进行排序，
 * 根据属性分为：
 * 最大堆，每个节点值大于所有孩子节点值，根节点是最大的值
 * 最小堆，与最大值相反
 *
 * 由最大最小堆特性，取数据最大最小值时间复杂度为O(1)
 */
using namespace std;
/**
 * 堆表现形式
 * 可以使用vector
 *
 * 建立最大堆
 */
template < typename T >
class MaxHeap {
private:
	void percolateUp(int i) {
		if (i <= 0)
			return;
		else if (h[parent(i)] < h[i]) {
			swap(h[i], h[parent(i)]);
			percolateUp(parent(i));
		}
	}
	void maxHeapify(int i) {
		int lc = lchild(i);
		int rc = rchild(i);
		int imax = i;

		if (lc < size() && h[lc] > h[imax])
			imax = lc;
		if (rc < size() && h[rc] > h[imax])
			imax = rc;
		if (i != imax) {
			swap(h[i], h[imax]);
			maxHeapify(imax);
		}
	}

public:
	vector < T > h;

	inline int parent(int i) {
		return (i - 1) / 2;
	}
	inline int lchild(int i) {
		return i * 2 + 1;
	}
	inline int rchild(int i) {
		return i * 2 + 2;
	}
	MaxHeap() {
		h.resize(0);
	}
	int size() {
		return h.size();
	}
	T getMax() {
		if (size() <= 0) {
			return -1;
		}
		else
			return h[0];
	}
	void insert(const T& key) {
		// Push elements into vector from the back
		h.push_back(key);
		// Store index of last value of vector in  variable i
		int i = size() - 1;
		// Restore heap property
		percolateUp(i);
	}
	void removeMax() {
		if (size() == 1) {
			// Built-in function in STL which swaps the value of two variables
			h.pop_back();
		}
		else if (size() > 1) {
			swap(h[0], h[size() - 1]);
			// Deletes last element
			h.pop_back();
			// Restore heap property
			maxHeapify(0);
		}
		else
			return;
	}
	void buildHeap(T arr[], int size) {
		// Copy elements of array into vector h 
		copy(&arr[0], &arr[size], back_inserter(h));
		for (int i = (size - 1) / 2; i >= 0; i--) {
			maxHeapify(i);
		}
	}
	void printHeap() {
		for (int i = 0; i <= size() - 1; i++) {
			cout << h[i] << " ";
		}
		cout << endl;
	}
};
/**
 * 最小堆
 */
template <typename T>
class MinHeap {
private:
	vector<T> h;

	inline int parent(int i) {
		return (i - 1) / 2;
	}
	inline int lchild(int i) {
		return i * 2 + 1;
	}
	inline int rchild(int i) {
		return i * 2 + 2;
	}

	void minHeapify(int i) {
		int lc = lchild(i);
		int rc = rchild(i);
		int imin = i;

		if (lc < size() && h[lc] < h[imin])
			imin = lc;
		if (rc < size() && h[rc] < h[imin])
			imin = rc;
		if (i != imin) {
			swap(h[i], h[imin]);
			minHeapify(imin);
		}
	}

	//percolateUp(): It is meant to restore the 
	//heap property going up from a node to the root.
	void percolateUp(int i) {
		if (i <= 0)
			return;
		else if (h[parent(i)] > h[i]) {
			swap(h[i], h[parent(i)]);
			percolateUp(parent(i));
		}
	}

public:

	MinHeap() {
		h.resize(0);
	}

	int size() {
		return h.size();
	}

	T getMin() {
		if (size() <= 0) {
			return -1;
		}
		else {
			return h[0];
		}
	}

	void insert(const T& key) {
		h.push_back(key);
		int i = size() - 1;

		percolateUp(i);
	}

	void removeMin() {
		if (size() == 1) {
			h.pop_back();
		}
		else if (size() > 1) {
			swap(h[0], h[size() - 1]);
			h.pop_back();
			minHeapify(0);
		}
		else
			return;
	}

	void buildHeap(T arr[], int size) {
		// Copy elements of array into vector h 
		copy(&arr[0], &arr[size], back_inserter(h));
		for (int i = (size - 1) / 2; i >= 0; i--) {
			minHeapify(i);
		}
	}
	//Bonus function: printHeap()
	void printHeap() {
		for (int i = 0; i <= size() - 1; i++) {
			cout << h[i] << " ";
		}
		cout << endl;
	}
};
/**
 * 最大堆转为最小堆
 */
void minHeapify(vector<int>& h, int i) {
	int lc = i * 2 + 1;
	int rc = i * 2 + 2;
	int imin = i;

	if (lc <= h.size() - 1 && h[lc] < h[imin])
		imin = lc;
	if (rc <= h.size() - 1 && h[rc] < h[imin])
		imin = rc;
	if (i != imin) {
		swap(h[i], h[imin]);
		minHeapify(h, imin);
	}
}

vector<int> buildMinHeap(vector<int> heapList) {
	for (int i = (heapList.size() - 1) / 2; i > -1; i--) {
		minHeapify(heapList, i);
	}
	return heapList;
}

string convertMax(vector<int> maxHeap) {
	string result = "";

	maxHeap = buildMinHeap(maxHeap);
	for (int i = 0; i < maxHeap.size(); i++) {
		if (i == maxHeap.size() - 1)
			result += to_string(maxHeap[i]);
		else
			result += to_string(maxHeap[i]) + ",";
	}
	return result;
}
/**
 * 第k个最小值
 */
vector<int> findKSmallest(int  arr[], int size, int k) {
	MinHeap<int> heap;
	//使用最小堆
	heap.buildHeap(arr, size);

	vector<int> output;

	for (int i = 0; (i < k) && (i < size); i++) {
		output.push_back(heap.getMin());
		heap.removeMin();
	}

	return output;
}
//第k个最大值
vector<int> findKLargest(int arr[], int size, int k) {
	MaxHeap<int> heap;
	//最大堆
	heap.buildHeap(arr, size);

	vector<int> output;
	for (int i = 0; (i < k) && (i < size); i++) {
		output.push_back(heap.getMax());
		heap.removeMax();
	}

	return output;
}

int main()
{
	std::cout << "Hello World!\n";
}

