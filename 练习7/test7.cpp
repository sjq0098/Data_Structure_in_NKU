#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
struct SparseMatrixNode{
	int row;
	int col;
	int val;
	SparseMatrixNode* next;
};

class SparseMatrix {
public:
	int hang;
	int lie;
	SparseMatrixNode** rowlist;
public:
	SparseMatrix(int h,int l) {
		hang=h;
		lie=l;
		rowlist=new SparseMatrixNode*[hang];
		for(int i=0;i<h;i++){
			rowlist[i]=NULL;
		}
		
	}
	SparseMatrix() {	};
	void Add_element(int r,int c,int x){
		SparseMatrixNode* temp=new SparseMatrixNode{r,c,x};
		if(!rowlist[r]){
			rowlist[r]=temp;
		}
		else{
			SparseMatrixNode* curr=rowlist[r];
			if(c<curr->col){
				curr->next=rowlist[r]->next;
				rowlist[r]=curr;
			}
			else{
				while(curr->next&&curr->next->col<c){
					curr=curr->next;
				}
				temp->next=curr->next;
				curr->next=temp;
			}
		}
		
	}
	int Get_digit(int r,int c){
		int x;
		SparseMatrixNode* curr=rowlist[r];
		while(curr&&curr->col!=c){
			curr=curr->next;
		}
		if(!curr){
			cout<<"该位置没有非零元素"<<endl;
			return 0;
		}
		x=curr->val;
		return x;
	}
	void Print(){
		for(int i=0;i<hang;i++){
			SparseMatrixNode*curr=rowlist[i];
			for(int j=0;j<lie;j++){
				if(curr&&curr->col==j){
					cout<<curr->val<<" ";
					curr=curr->next;
				}
				else{
					cout<<0<<" ";
				}
			}
			cout<<endl;
		}
	}
};

SparseMatrix SparseMatrixMinus(SparseMatrix &A, SparseMatrix &B) {  
	if (A.hang == B.hang && A.lie == B.lie) {  
		SparseMatrix Result(A.hang, B.lie);  
		for (int i = 0; i < A.hang; i++) {  
			SparseMatrixNode* curr1 = nullptr; // 追踪新矩阵当前行的最后一个节点  
			SparseMatrixNode* curr2 = A.rowlist[i];  
			SparseMatrixNode* curr3 = B.rowlist[i];  
			while (curr2 || curr3) {  
				if (curr2 && curr3 && curr2->col == curr3->col) {  
					int sum = curr2->val - curr3->val;  
					if (sum != 0) {  
						SparseMatrixNode* temp = new SparseMatrixNode{i, curr2->col, sum};  
						if (!Result.rowlist[i]) {  
							Result.rowlist[i] = temp;  
							curr1 = temp; // 更新 curr1 为新添加的节点  
						} else {  
							curr1->next = temp;  
							curr1 = temp; // 更新 curr1 为新添加的节点  
						}  
					}  
					curr2 = curr2->next;  
					curr3 = curr3->next;  
				} else if (curr2 && (!curr3 || curr2->col < curr3->col)) {  
					SparseMatrixNode* temp = new SparseMatrixNode{i, curr2->col, curr2->val};  
					if (!Result.rowlist[i]) {  
						Result.rowlist[i] = temp;  
						curr1 = temp; // 更新 curr1 为新添加的节点  
					} else {  
						curr1->next = temp;  
						curr1 = temp; // 更新 curr1 为新添加的节点  
					}  
					curr2 = curr2->next;  
				} else if (curr3 && (!curr2 || curr3->col < curr2->col)) {  
					SparseMatrixNode* temp = new SparseMatrixNode{i, curr3->col, -curr3->val};  
					if (!Result.rowlist[i]) {  
						Result.rowlist[i] = temp;  
						curr1 = temp; // 更新 curr1 为新添加的节点  
					} else {  
						curr1->next = temp;  
						curr1 = temp; // 更新 curr1 为新添加的节点  
					}  
					curr3 = curr3->next;  
				}  
			}  
		}  
		Result.Print();
		return Result;  
	} else {  
		SparseMatrix Result(0, 0);  
		cout << "无法进行减法运算" << endl;  
		return Result;  
	}  
}


SparseMatrix SparseMatrixPlus(SparseMatrix &A,SparseMatrix &B){
	if(A.hang==B.hang&&A.lie==B.lie){
		SparseMatrix Result(A.hang,B.lie);
		for(int i=0;i<A.hang;i++){
			SparseMatrixNode*curr1=nullptr;
			SparseMatrixNode*curr2=A.rowlist[i];
			SparseMatrixNode*curr3=B.rowlist[i];
				while(curr3||curr2){
					if(curr2&&curr3&&curr3->col==curr2->col){
						int sum=curr2->val+curr3->val;
						if(sum!=0){
							SparseMatrixNode*temp=new SparseMatrixNode{i,curr3->col,sum};
							if(!Result.rowlist[i]){
								Result.rowlist[i]=temp;
							}
							else{
								curr1->next=temp;
							}
							curr1=temp;
							curr3=curr3->next;
							curr2=curr2->next;
						}
					}
					else if(curr2&&(!curr3||curr3->col>curr2->col)){
						SparseMatrixNode*temp=new SparseMatrixNode{i,curr2->col,curr2->val};
						if(!Result.rowlist[i]){
							Result.rowlist[i]=temp;
						}
						else{
							curr1->next=temp;
						}
						curr1=temp;
						curr2=curr2->next;
					}
					else if(curr3&&(!curr2||curr2->col>curr3->col)){
						SparseMatrixNode*temp=new SparseMatrixNode{i,curr3->col,curr3->val};
						if(!Result.rowlist[i]){
							Result.rowlist[i]=temp;				
						}
						else{
							curr1->next=temp;
						}
						curr1=temp;
						curr3=curr3->next;
					}
				}
			}
		Result.Print();
		return Result;
		}
	else{
		SparseMatrix Result(0,0);
		cout<<"无法进行加法运算"<<endl;
		return Result;
	}
};
SparseMatrix SparseMatrixMutiply(SparseMatrix A,SparseMatrix B){
	if(A.lie==B.hang){
		SparseMatrix Result(A.hang,B.lie);
		for (int i = 0; i < A.hang; i++) {
			if (A.rowlist[i]) {
				SparseMatrixNode* curr1 = A.rowlist[i];
				while (curr1) {
					int Bh = curr1->col;
					SparseMatrixNode* curr2 = B.rowlist[Bh];
					while (curr2) {
						int sum = 0;
						sum += curr1->val * curr2->val;
						if (sum!= 0) {
							Result.Add_element(i, curr2->col, sum);
						}
						curr2 = curr2->next;
					}
					
					curr1 = curr1->next;
				}
			}
		}
		Result.Print();
		return Result;
	}
	else{
		SparseMatrix Result(0,0);
		cout<<"无法进行乘法运算"<<endl;
		return Result;
	}
}
istream& operator>>(istream &in,SparseMatrix &X){
	int nums;
	cerr<<"输入规格";
	in>>X.hang>>X.lie>>nums;
	X.rowlist=new SparseMatrixNode*[X.hang];
	for(int i=0;i<X.hang;i++){
		X.rowlist[i]=NULL;
	}
	int preR=-1,preC=-1;
	for(int i=0;i<nums;i++){
		cerr<<"输入数据";
		int r,c,v;
		in>>r>>c>>v;
		if(r<0||c<0||r>=X.hang||c>=X.lie){
			 cerr << "Invalid row or column" << endl;
		}
		if (preR!= -1 && (r < preR || (r== preR && c <= preC))) {
			cerr << "Invalid order" << endl;
		}
		
		// 验证输入元素是否非0
		if (v == 0) {
			cerr << "Non-zero " << endl;
		}
		
		preR = r;
		preC = c;
		X.Add_element(r,c,v);	
	}
		return in;
}

int main(){
	SparseMatrix T(3,4),X(3,4),U;
	cin>>U;
	U.Print();
	cout<<endl;
	cout<<endl;
	T.Add_element(1,2,5);
	T.Add_element(2,1,5);
	T.Print();
	cout<<endl;
	cout<<endl;
	X.Add_element(1,1,5);
	X.Add_element(2,2,5);
	X.Print();
	
	cout<<endl;
	cout<<endl;
	SparseMatrixPlus(T,X);
	cout<<endl;
	cout<<endl;
	SparseMatrixMinus(T,X);
	
	cout<<endl;
	cout<<endl;
	SparseMatrix matrixA(3, 3);
	matrixA.Add_element(0, 1, 2);
	matrixA.Add_element(0, 2, 3);
	matrixA.Add_element(1, 0, 4);
	matrixA.Add_element(2, 1, 5);
	matrixA.Print();
	cout<<endl;
	cout<<endl;
	SparseMatrix matrixB(3, 3);
	matrixB.Add_element(0, 0, 1);
	matrixB.Add_element(0, 1, 2);
	matrixB.Add_element(1, 0, 3);
	matrixB.Add_element(1, 2, 4);
	matrixB.Add_element(2, 1, 5);
	matrixB.Print();
	cout<<endl;
	cout<<endl;
	SparseMatrixMutiply(matrixA,matrixB);
	return 0;
}
