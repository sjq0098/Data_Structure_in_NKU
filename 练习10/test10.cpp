#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
using namespace std;
struct hashnode{
	int key;
	bool occupied;
	bool neverused;
	hashnode() : key(0), occupied(false), neverused(true) {}
};
class Hashtable {
public:
	vector<hashnode> table;
	int Max;
	int Size;
	int hashfuc(int k){
		return (k)%Max;
	}
	Hashtable(int m){
		Max=m;
		table.resize(m);
	}
	void Insert(int k){
		int index=hashfuc(k);
		int originalIndex = index; 
		while (true) {
			if (table[index].neverused || !table[index].occupied) {
				table[index].key = k;
				table[index].occupied = true;
				table[index].neverused = false;
				Size++;
				check();
				return;
			}
			index = (index + 1) % Max;
			if (index == originalIndex) {
				break;
			}
		}
	}
	bool search(int k){
		int index=hashfuc(k);
		int originalIndex = index; 
		while (true) {
			if (table[index].neverused || !table[index].occupied) {
				return 0;
			}
			if(table[index].occupied){
				return 1;
			}
			index = (index + 1) % Max;
			if (index == originalIndex) {
				break;
			}
		}
		return 0;
	}
	void remove(int k){
		int index=hashfuc(k);
		int originalIndex = index; 
		while (true) {
			if (table[index].neverused || !table[index].occupied) {
				return;
			}
			if(table[index].occupied){
				table[index].occupied=0;
				Size--;
				check();
				return;
			}
			index = (index + 1) % Max;
			if (index == originalIndex) {
				break;
			}
		}
	}
	void reorgan() {
		vector<int> keys;
		for (auto& node : table) {
			if (node.occupied) {
				keys.push_back(node.key);
			}
		}
		table.clear();
		table.resize(Max);
		Size = 0;
		for (int i : keys) {
			Insert(i);
		}
	}
	
	void check() {
		int totalEmpty = 0;
		int usedEmpty = 0;
		for (auto& node : table) {
			if (!node.occupied) {
				totalEmpty++;
				if (!node.neverused) {
					usedEmpty++;
				}
			}
		}
		if (totalEmpty > 0 && (float)usedEmpty / totalEmpty >= 0.6) {
			reorgan(); 
		}
	}
	
	void print(){
		for(long long i=0;i<table.size();i++){
			cout<<i<<":";
			if(table[i].occupied){
				cout<<table[i].key<<endl;
			}
			else{
				cout<<"Empty"<<endl;
			}
		}
	}
};
int main(){
	Hashtable ht(10);
	for(int i=1;i<=9;i++){
		ht.Insert(i);
	}
	cout<<"Inserted"<<endl;
	ht.print();
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
	for(int i=1;i<=9;i++){
		ht.remove(i);
	}
	cout<<"Removed"<<endl;
	ht.print();
	return 0;
}
