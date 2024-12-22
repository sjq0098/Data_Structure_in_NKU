#include <iostream>
#include <vector>
using namespace std;

int O1 = 0; // 比较次数
int O2 = 0; // 交换次数

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
	O2++; 
}

class maxheap {
public:
	int Size;         
	vector<int> heap; 
	
	maxheap(int capacity = 0) {

		heap.resize(capacity+1);  
		Size = 0;
	}
	
	void heapifyUp(int i) {
		while (i > 1) {
			int parent = i / 2;
			O1++; 
			if (heap[parent] < heap[i]) {
				swap(heap[parent], heap[i]);
				i = parent;
			} else {
				break;
			}
		}
	}
	
	void heapifyDown(int i) {
		while (true) {
			int left = 2 * i;
			int right = 2 * i + 1;
			int largest = i;
			

			if (left <= Size) {
				O1++; 
				if (heap[left] > heap[largest]) {
					largest = left;
				}
			}

			if (right <= Size) {
				O1++; 
				if (heap[right] > heap[largest]) {
					largest = right;
				}
			}
			
			if (largest != i) {
				swap(heap[i], heap[largest]);
				i = largest;
			} else {
				break;
			}
		}
	}
	
	void push(int k) {
		heap[++Size] = k;
		heapifyUp(Size);
	}
	
	int pop() {
		if (Size == 0) {
			cout << "Heap is empty!" << endl;
			return -1;
		}
		int rootValue = heap[1];
		heap[1] = heap[Size];
		Size--;
		if (Size > 0) {
			heapifyDown(1);
		}
		return rootValue;
	}
	
	void Print() {
		for (int i = 1; i <= Size; i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	maxheap mh;
	mh.Print();
	mh.push(15);
	mh.push(20);
	mh.push(10);
	mh.Print();
	mh.pop();
	mh.Print();
	
	cout << "Number of comparisons (O1): " << O1 << endl;
	cout << "Number of swaps (O2): " << O2 << endl;
	
	return 0;
}


