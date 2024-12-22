#include<iostream>
#include<string>
using namespace std;

class Deque {
public:
	int MaxSize;
	int* deque;
	int front;
	int rear;
	int length;
	
	Deque(int m) {
		MaxSize = m;
		deque = new int[MaxSize];
		front = -1;
		rear = 0;
		length = 0;
	}
	
	~Deque() {
		delete[] deque;
	}
	
	void addLeft(int m) {
		if (isFull()) {
			cout << "FULL" << endl;
			return;
		}
		if (isEmpty()) {
			front = rear = 0;
		} else {
			front = (front - 1 + MaxSize) % MaxSize;
		}
		deque[front] = m;
		length++;
		Print();
	}
	
	void addRight(int m) {
		if (isFull()) {
			cout << "FULL" << endl;
			return;
		}
		if (isEmpty()) {
			front = rear = 0;
		} else {
			rear = (rear + 1) % MaxSize;
		}
		deque[rear] = m;
		length++;
		Print();
	}
	
	void deleteLeft() {
		if (isEmpty()) {
			cout << "EMPTY" << endl;
			return;
		}
		if (front == rear) {
			front = -1;
			rear = 0;
		} else {
			front = (front + 1) % MaxSize;
		}
		length--;
		Print();
	}
	
	void deleteRight() {
		if (isEmpty()) {
			cout << "EMPTY" << endl;
			return;
		}
		if (front == rear) {
			front = -1;
			rear = 0;
		} else {
			rear = (rear - 1 + MaxSize) % MaxSize;
		}
		length--;
		Print();
	}
	
	bool isFull() {
		return length == MaxSize;
	}
	
	bool isEmpty() {
		return length == 0;
	}
	
	void Print() {
		if (isEmpty()) {
			cout << "EMPTY" << endl;
			return;
		}
		int i = front;
		while (true) {
			cout << deque[i];
			if (i == rear) {
				break;
			}
			cout << " ";
			i = (i + 1) % MaxSize;
		}
		cout << endl;
	}
};

int main() {
	Deque dq(10);
	string command;
	while (cin >> command) {
		if (command == "End") {
			break;
		} else if (command == "AddLeft") {
			int value;
			cin >> value;
			dq.addLeft(value);
		} else if (command == "AddRight") {
			int value;
			cin >> value;
			dq.addRight(value);
		} else if (command == "DeleteLeft") {
			dq.deleteLeft();
		} else if (command == "DeleteRight") {
			dq.deleteRight();
		} else if (command == "IsFull") {
			cout << (dq.isFull() ? "Yes" : "No") << endl;
		} else if (command == "IsEmpty") {
			cout << (dq.isEmpty() ? "Yes" : "No") << endl;
		} else {
			cout << "WRONG" << endl;
		}
	}
	return 0;
}

