#include<iostream>
#include<fstream>
using namespace std;

double O=0;
template<typename T>
class List;

template<typename T>
class Node {
friend List<T>;
public:
	T data;
	Node<T>* next;
	Node(T x){data=x;next=NULL;};
};

template<typename T>
class List{
public:
	Node<T>*head;
	int length;
	List(){head=0;length=0;}
	~List(){
		while(head){
			delete head;
			head=head->next;
		}
	}
	void append(T x){
		Node<T>*temp=new Node(x);
		if(!head){
			head=temp;
			length++;
		}
		else{
			Node<T>*curr=head;
			while(curr->next){
				curr=curr->next;
			}
			curr->next=temp;
			length++;
		}
		O++;
	}
	void output(){
		if(!head){
			cout<<"没有元素";
		}
		else{
			Node<T>*curr=head;
			while(curr){
				cout<<curr->data<<" ";
				curr=curr->next;
			}
		}
		cout<<endl;
		cout<<O/8;
		return;
	}
	T deletefirst(){
		T y;
		y=head->data;
		Node<T>*curr=head;
		head=head->next;
		delete curr;
		length--;
		O++;
		return y;
	}
	
	bool isEmpty(){
		return head==0;
		O++;
	}
};
template<typename T>
void meld(List<T> La,List<T> Lb){
	List<T> Lc;
	int ll=La.length+Lb.length;
	O++;
	bool A=La.isEmpty();
	bool B=Lb.isEmpty();
	if(A&&!B){
		Lb.output();
		return;
	}
	else if(!A&&B){
		La.output();
		return;
	}
	else if(A&&B){
		cout<<"Wrong";
	}
	else{
		for(int i=1;i<=ll;i++){
			if(i%2==1&&!La.isEmpty()){
				T x=La.deletefirst();
				Lc.append(x);
			}
			else if(i%2==0&&!Lb.isEmpty()){
				T x=Lb.deletefirst();
				Lc.append(x);
			}
			O++;
		}
		Lc.output();
	}
	return;
}
int main(){
	List<int> La,Lb;
	ifstream fin("input.txt");
	int x;
	for(int i=0;i<4;i++){
		fin>>x;
		La.append(x);
	}
	for(int i=0;i<4;i++){
		fin>>x;
		Lb.append(x);
	}
	fin.close();
	meld(La,Lb);
	return 0;
}
