#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;

class Deque {
public:
	int MaxSize;
	vector<int>deque;
	int lenth=0;
	Deque(int m){
		MaxSize=m;
	}
	void addLeft(int m){
		if(isFull()){
			cout<<"isfull"<<endl;
			return;
		}
		deque.insert(deque.begin(),m);
		lenth++;
		Print();
	}
	void addRight(int m){
		if(isFull()){
			cout<<"isfull"<<endl;
			return;
		}
		deque.push_back(m);
		lenth++;
		Print();
	}
	void deleteLeft(){
		if(isEmpty()){
			cout<<"isempty"<<endl;
			return;
		}
		deque.erase(deque.begin());
		lenth--;
		Print();
	}
	void deleteRight(){
		if(isEmpty()){
			cout<<"isempty"<<endl;
			return;
		}
		deque.pop_back();
		lenth--;
		Print();
	}
	bool isFull(){
		return lenth==MaxSize;
	}
	bool isEmpty(){
		return lenth==0;
	}
	void Print(){
		if(isEmpty()){
			cout<<"isempty"<<endl;
			return;
		}
		for(int i=0;i<lenth-1;i++){
			cout<<deque[i]<<" ";
		}
		cout<<deque[lenth-1]<<endl;
	}
};
int main(){
	Deque dq(10);
	string command;
	while(cin>>command){
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
