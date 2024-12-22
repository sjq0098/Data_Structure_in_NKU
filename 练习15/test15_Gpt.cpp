#include <iostream>
#include <vector>
#include <algorithm>

class MaxHeap {
public:
	MaxHeap(int maxElement, int minElement, int n) {
		heap.resize(2 * n + 2);  // 创建大小为 2n + 2 的堆数组
		heap[0] = maxElement;     // 最大元素存储在 heap[0]
		heap[n + 1] = minElement; // 最小元素存储在 heap[n + 1]
		size = 0;                 // 当前堆中的元素数量
		this->n = n;
	}
	
	// 获取父节点的索引
	int parent(int i) {
		return i / 2;
	}
	
	// 获取左子节点的索引
	int leftChild(int i) {
		return 2 * i;
	}
	
	// 获取右子节点的索引
	int rightChild(int i) {
		return 2 * i + 1;
	}
	
	// 交换堆中两个元素的位置
	void swap(int i, int j) {
		std::swap(heap[i], heap[j]);
	}
	
	// 向上调整堆以维护最大堆性质
	void heapifyUp(int i) {
		while (i > 1 && heap[parent(i)] < heap[i]) {
			swap(i, parent(i));
			i = parent(i);
		}
	}
	
	// 向下调整堆以维护最大堆性质
	void heapifyDown(int i) {
		int largest = i;
		int left = leftChild(i);
		int right = rightChild(i);
		
		if (left <= size && heap[left] > heap[largest]) {
			largest = left;
		}
		if (right <= size && heap[right] > heap[largest]) {
			largest = right;
		}
		if (largest != i) {
			swap(i, largest);
			heapifyDown(largest);
		}
	}
	
	// 插入新元素到堆中
	void push(int value) {
		if (size + 1 >= n) {
			std::cout << "Heap is full!" << std::endl;
			return;
		}
		
		heap[++size] = value;  // 将元素添加到堆的末尾
		heapifyUp(size);       // 调整堆
	}
	
	// 移除堆中的最大元素（根节点）
	int pop() {
		if (size == 0) {
			std::cout << "Heap is empty!" << std::endl;
			return -1;  // 堆为空时返回 -1
		}
		
		int root = heap[1];   // 最大元素是根节点
		heap[1] = heap[size];  // 将最后一个元素移到根节点
		size--;               // 堆的大小减 1
		heapifyDown(1);       // 调整堆以维护最大堆性质
		
		return root;          // 返回最大元素
	}
	
	// 打印堆中的所有元素
	void printHeap() {
		for (int i = 1; i <= size; ++i) {
			std::cout << heap[i] << " ";
		}
		std::cout << std::endl;
	}
	
private:
	std::vector<int> heap;  // 用于存储堆的数组
	int size;               // 堆中的元素数量
	int n;                  // 最大堆的容量
};

int main() {
	// 创建一个最大堆，最大元素为 100，最小元素为 0，堆的大小为 5
	MaxHeap maxHeap(100, 0, 5);
	
	maxHeap.push(10);
	maxHeap.push(20);
	maxHeap.push(30);
	maxHeap.push(40);
	maxHeap.push(50);
	
	std::cout << "Heap elements after push operations: ";
	maxHeap.printHeap();
	
	std::cout << "Popped element: " << maxHeap.pop() << std::endl;
	
	std::cout << "Heap elements after pop operation: ";
	maxHeap.printHeap();
	
	return 0;
}



