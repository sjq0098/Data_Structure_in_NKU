#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
using namespace std;
struct NodeOfHash {
	int key;
	NodeOfHash* next;
	
	NodeOfHash(int k) : key(k), next(nullptr) {};
};
struct Bucket{
	NodeOfHash* head;
	NodeOfHash*tail;
	Bucket():head(nullptr),tail(nullptr){};
};
class HashTableWithChain {
public:
	int Max;
	vector<Bucket>table;
	NodeOfHash* sharedtail=nullptr;
	HashTableWithChain(int m){
		Max=m;
		table.resize(m);
	}
	int hashfuc(int k){
		return k%Max;
	}
	
	void Insert(int k){
		int index=hashfuc(k);
		NodeOfHash*curr=table[index].head;
		while(curr){
			if(curr->key==k){
				return;
			}
			curr=curr->next;	
		}
		NodeOfHash* temp=new NodeOfHash(k);
		if(table[index].head==nullptr){
			table[index].head=table[index].tail=temp;
		}
		else{
			table[index].tail->next=temp;
			table[index].tail=temp;
		}
	}
	
	void remove(int k){
		int index=hashfuc(k);
		NodeOfHash*curr=table[index].head;
		NodeOfHash*pre=nullptr;
		while(curr){
			if(curr->key==k){
				if(curr==table[index].head){
					table[index].head=curr->next;
				}
				if(curr==table[index].tail){
					table[index].tail=pre;	
				}
				if(curr!=table[index].head&&curr!=table[index].tail){
					pre->next=curr->next;
				}
				delete curr;
				return;
			}
			pre=curr;
			curr=curr->next;	
		}
		if(!curr){
			cout<<"No Such element"<<endl;
			return;
		}
	}
	
	bool search(int k){
		int index=hashfuc(k);
		NodeOfHash*curr=table[index].head;
		while(curr){
			if(curr->key==k){
				return 1;
			}
			curr=curr->next;	
		}
		return 0;
	}
	
	void Print(){
		for(int i=0;i<Max;i++){
			cout<<"Bucket"<<i<<":   ";
			NodeOfHash*curr=table[i].head;
			while(curr){
				cout<<curr->key<<"->";
				curr=curr->next;	
			}
			if(!curr){
				cout<<"nullptr"<<endl;
			}
		}
	}
};
int main(){
	HashTableWithChain ht(5);
	ht.Insert(1);
	ht.Insert(11);
	ht.Insert(21);
	ht.Insert(31);
	for(int i=1;i<=9;i++){
		ht.Insert(i);
	}
	cout << "Hash Table after insertions:\n";
	ht.Print();
	if(ht.search(1)){
		cout<<"In"<<endl;
	}
	else{
		cout<<"Not In"<<endl;
	}
	if(ht.search(10)){
		cout<<"In"<<endl;
	}
	else{
		cout<<"Not In"<<endl;
	}
	ht.remove(21);
	cout << "\nHash Table after deleting 21:\n";
	ht.Print();
	return 0;
}
