#include <iostream>
#include <vector>
using namespace std;

class hashChainsWithTail {
private:
	// Node 类表示链表中的节点
	struct Node {
		int key;
		Node* next;
		Node(int k) : key(k), next(nullptr) {}
	};
	
	// 每个桶是一个链表，维护链表的头和尾指针
	struct Bucket {
		Node* head;
		Node* tail;
		Bucket() : head(nullptr), tail(nullptr) {}
	};
	
	vector<Bucket> table;  // 哈希表，存储桶
	int Max;               // 哈希表的大小
	
	// 简单的哈希函数
	int hashfuc(int key) {
		return key % Max;
	}
	
public:
	hashChainsWithTail(int size) : Max(size) {
		table.resize(Max);
	}
	
	// 插入操作
	void Insert(int key) {
		int index = hashfuc(key);
		Node* current = table[index].head;
		
		// 检查是否已存在该元素
		while (current) {
			if (current->key == key) {
				cout << "Key " << key << " already exists.\n";
				return;
			}
			current = current->next;
		}
		
		// 插入新节点
		Node* newNode = new Node(key);
		if (table[index].head == nullptr) {
			// 如果链表为空，直接设置头和尾指针
			table[index].head = newNode;
			table[index].tail = newNode;
		} else {
			// 否则，添加到链表尾部并更新尾指针
			table[index].tail->next = newNode;
			table[index].tail = newNode;
		}
	}
	
	// 删除操作
	void Remove(int key) {
		int index = hashfuc(key);
		Node* current = table[index].head;
		Node* prev = nullptr;
		
		while (current) {
			if (current->key == key) {
				// 找到节点，进行删除
				if (prev == nullptr) {
					// 如果是链表头部节点
					table[index].head = current->next;
				} else {
					// 否则，跳过当前节点
					prev->next = current->next;
				}
				
				// 如果是链表尾部节点，更新尾指针
				if (current == table[index].tail) {
					table[index].tail = prev;
				}
				
				delete current;
				cout << "Key " << key << " removed.\n";
				return;
			}
			prev = current;
			current = current->next;
		}
		
		cout << "Key " << key << " not found.\n";
	}
	
	// 查找操作
	bool Search(int key) {
		int index = hashfuc(key);
		Node* current = table[index].head;
		
		while (current) {
			if (current->key == key) {
				return true;
			}
			current = current->next;
		}
		return false;
	}
	
	// 打印哈希表内容
	void Print() {
		for (int i = 0; i < Max; i++) {
			cout << "Bucket " << i << ": ";
			Node* current = table[i].head;
			while (current) {
				cout << current->key << " -> ";
				current = current->next;
			}
			cout << "nullptr\n";
		}
	}
};

int main() {
	hashChainsWithTail ht(10);
	
	// 插入一些元素
	ht.Insert(5);
	ht.Insert(15);
	ht.Insert(25);
	ht.Insert(35);
	
	cout << "After Insertions:\n";
	ht.Print();
	
	// 删除元素
	ht.Remove(15);
	cout << "\nAfter Removing 15:\n";
	ht.Print();
	
	// 查找元素
	cout << "\nSearching for 25: " << (ht.Search(25) ? "Found" : "Not Found") << endl;
	cout << "Searching for 15: " << (ht.Search(15) ? "Found" : "Not Found") << endl;
	
	return 0;
}

