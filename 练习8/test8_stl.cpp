#include <iostream>
#include<fstream>
#include <vector>
#include<queue>
using namespace std;

int main(){
	int n,m;
	ifstream in("input.txt");
	in>>n>>m;
	m=m%n;
	queue<int> Jose;
	for(int i=1;i<=n;i++){
		Jose.push(i);
	}
	while(!Jose.empty()){
		for(int i=0;i<m-1;i++){
			int temp=Jose.front();
			Jose.pop();
			Jose.push(temp);
		}
		cout<<Jose.front()<<" ";
		Jose.pop();
	}
	return 0;
}
