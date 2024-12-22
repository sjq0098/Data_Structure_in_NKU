#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;

int O1=0; // 比较操作次数
int O2=0; // 交换操作次数

void swap(int &a,int &b){
	int temp=a;
	a=b;
	b=temp;
	O2++; 
}

class maxheap{
public:
	int Size;
	int MaxElement;
	int MinElement;
	int n;
	vector<int> heap;
	maxheap(int num,int ma,int mi){
		heap.resize(2*num+2);
		Size=0;
		n=num;
		MaxElement=ma;
		MinElement=mi;
		heap[0]=MaxElement;
		heap[n+1]=MinElement;
	}
	
	maxheap(vector<int>& arr){
		heap=arr;
		Size=(int)arr.size();
		for(int i=(Size/2)-1;i>=0;i--){
			heapifydown(i);
		}
	}
	
	void heapifydown(int i){
		int s=(int)heap.size();
		while (2 * i + 1 < s && i>0) { // 有左子节点
			int left = 2 * i;
			int right = 2 * i + 1;
			int largest = i;
			
			O1++; 
			if (heap[left] > heap[largest]) {
				largest = left;
			}
			
			if (right < s) {
				O1++; 
				if (heap[right] > heap[largest]) {
					largest = right;
				}
			}
			
			if (largest != i) {
				swap(heap[i], heap[largest]);
				i = largest;
			} else {
				break;
			}
		}
	}
	
	void heapifyUp(int i) {
		while (heap[i/2] < heap[i]) {
			O1++; 
			swap(heap[i/2], heap[i]);
			i = i/2;
		}
	}
	
	void push(int k){
		if(k>MaxElement||k<MinElement){
			cout<<"WRONG INPUT"<<endl;
			return;
		}
		if(Size>=n-1){
			cout<<"FULL"<<endl;
		}
		heap[++Size]=k;
		heapifyUp(Size);
	}
	
	int pop(){
		if (Size == 0) {
			cout << "Heap is empty!" << std::endl;
			return -1;  // 堆为空时返回 -1
		}
		int Root=heap[1];
		heap[1]=heap[Size];
		Size--;
		return Root;
	}
	
	void Print(){
		for(int i=1;i<=Size;i++){
			cout<<heap[i]<<" ";
		}
		cout<<endl;
	}
};

int main(){
	int maxElement = 100;
	int minElement = 0;
	int heapSize = 5;
	maxheap mh(heapSize,maxElement,minElement);
	mh.Print();
	mh.push(15);
	mh.push(20);
	mh.push(10);
	mh.Print();
	mh.pop();
	mh.Print();
	
	cout << "Number of comparisons (O1): " << O1 << endl;
	cout << "Number of swaps (O2): " << O2 << endl;
	
	return 0;
}

