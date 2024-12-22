#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
using namespace std;
template<typename T>
class Stack {
public:
	vector<T> s;
	int Max;
	int Length=0;
	Stack(int m){
		Max=m;
	}
	bool IsEmpty() const{
		return s.empty();
	}
	bool IsFull() const{
		return (Length == Max);
	}
	void push(T x){
		if(!IsFull()){
			s.push_back(x);
			Length++;
		}
	}
	T pop(){
		if(!IsEmpty()){
			T x=s.back();
			s.pop_back();
			Length--;
			return x;
		}
		else{
			return 0;
		}
	}
	T top(){
		T x=s[Length-1];
		return x;
	}
};

template<typename T>
void Delete_all(T&x,Stack<T>Stac){
	Stack<T> Temp(Stac.Length);
	while(!Stac.IsEmpty()){
		T temp=Stac.pop();
		if(temp!=x){
			Temp.push(temp);
		}
	}
	while(!Temp.IsEmpty()){
		T temp=Temp.pop();
		Stac.push(temp);
	}
	while(!Stac.IsEmpty()){
		cout<<Stac.pop()<<" ";
	}
}
int main(){
	ifstream in("input.txt");
	char x;
	in>>x;
	Stack<char> St(10);
	for(int i=0;i<7;i++){
		char temp;
		in>>temp;
		St.push(temp);
	}
	Delete_all(x,St);
	return 0;
}
