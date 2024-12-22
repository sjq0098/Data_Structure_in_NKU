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
	Node<T>* before;
	Node<T>(T x){data=x;before=next=NULL;};
};

template<typename T>
class List{
public:
	Node<T>*head;
	Node<T>*tail;
	int length;
	List() : head(new Node<T>(T())), tail(head), length(0) {    
		head->next = tail;    
		tail->before = head;    
	}
	~List(){
		Node<T>*curr=head->next;
		while(curr){
			delete curr;
			curr=curr->next;
		}
	}
	void append(T x){
		Node<T>*temp=new Node<T>(x);
		if(head==tail){
			head->next = temp;  
			temp->before = head;  
			temp->next = head;  
			tail = temp; 
			length++;
			
		}
		else{
			tail->next = temp;  
			temp->before = tail;  
			temp->next = head;   
			tail = temp;
			length++;
		}
		O++;
	}
	void output(){
		if(head==tail){
			cout<<"没有元素";
		}
		else{
			Node<T>*curr=head->next;
			while(curr!=head){
				cout<<curr->data<<" ";
				curr=curr->next;
			}
		}
	}
	bool isEmpty(){
		return tail==0;
		O++;
	}
	
	void Split(){
		Node<T>* head1 = head->next;
		Node<T>* head2 = head1->next;
		Node<T>* curr1 = head1;
		Node<T>* curr2 = head2;
		while (curr2 != head && curr2->next != head) {
			curr1->next = curr2->next;
			O++;
			curr1 = curr1->next;
			O++;
			curr2->next = curr1->next;
			O++;
			curr2 = curr2->next;
			O++;
		}
		curr1->next=head;
		O++;
		curr2->next=head;
		Node<T>* curr3 = head1;
		Node<T>* curr4 = head2;
		while(curr3!=head){
			cout<<curr3->data<<" ";
			curr3=curr3->next;
		}
		cout<<endl;
		while(curr4!=head){
			cout<<curr4->data<<" ";
			curr4=curr4->next;
		}
		cout<<endl;
		cout<<O/14<<endl;	
		Node<T>* curr5 = tail;
		while(curr5!=head){
			cout<<curr5->data<<" ";
			curr5=curr5->before;
		}
	}
};
template<typename T>
void split(List<T> lc){
	List<T>la,lb;
	Node<T>*curr=lc.head->next;
	bool jia=0;
	while(curr!=lc.head&&curr->next!=lc.head){
		if(!jia){
			T x=curr->data;
			O++;
			T y=curr->next->data;
			O++;
			la.append(x);
			lb.append(y);
			curr=curr->next;
			O++;
			jia=1;	
			O++;
		}
		else{
			curr=curr->next;
			O++;
			jia=0;
			O++;
		}
	}
	if(curr->next==lc.head&&jia==0){
		T x=curr->data;
		O++;
		la.append(x);
		O++;
	}
	la.output();
	cout<<endl;
	lb.output();
	cout<<endl;
	cout<<O/16;
}
int main(){
	List<int> L1;
	ifstream fin("input.txt");
	int x;
	for(int i=0;i<14;i++){
		fin>>x;
		L1.append(x);
	}
	L1.output();
	cout<<endl;
	L1.Split();
	return 0;
}
