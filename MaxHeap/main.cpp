#include <iostream>
#include <vector>

using namespace std;

class MyMaxHeap {
private:
	vector<int> maxHeap;
	int size = 0;
	int capacity;

public:
	MyMaxHeap(int _capacity) : capacity(_capacity) {

	}

	void push(int num) {
		++size;
		maxHeap.emplace_back(num);
		up(size - 1);
		heapSort();
		if (size > capacity) {
			maxHeap.pop_back();
			--size;
		}
	}

	void pop() {
		if (size > 0) {
			swap(maxHeap[0], maxHeap[size - 1]);
			maxHeap.pop_back();
			--size;
			if (size > 1) {
				down(0);
			}
		}
		else {
			cout << "MaxHeap is empty!" << endl;
		}
	}

	void print() {
		if (size < 1) {
			cout << "MaxHeap is empty!" << endl;
			return;
		}
		for (int num : maxHeap) {
			cout << num << ' ';
		}
		cout << endl;
	}

private:
	void up(int index) {
		int temp = maxHeap[index];
		while (index > 0 && temp > maxHeap[(index - 1) / 2]) {
			maxHeap[index] = maxHeap[(index - 1) / 2];
			index = (index - 1) / 2;
		}
		maxHeap[index] = temp;
	}

	void down(int index) {
		int temp = maxHeap[index];
		index = index * 2 + 1;
		while (index < size) {
			if ((index + 1) < size && maxHeap[index] < maxHeap[index + 1]) {
				++index;
			}
			if (maxHeap[index] <= temp) {
				break;
			}
			else {
				maxHeap[(index - 1) / 2] = maxHeap[index];
				index = index * 2 + 1;
			}
		}
		maxHeap[(index - 1) / 2] = temp;
	}

	void heapSort() {
		vector<int> result;
		int n = size;
		for (int i = 0; i < n; ++i) {
			result.emplace_back(maxHeap[0]);
			pop();
		}
		maxHeap = result;
		size = n;
	}
};

int main()
{
	MyMaxHeap heap(5);
	int a[10] = { 9, 1, 2, 4, 10, 7, 12, 15, 30, 22 };
	for (int num : a) {
		heap.push(num);
		heap.print();
	}
	cout << endl;
	for (int i = 0; i < 5; ++i) {
		heap.pop();
		heap.print();
	}
	return 0;
}