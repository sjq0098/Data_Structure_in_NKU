#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
int O=0;
struct SparseMartixTriple{
	int row;
	int col;
	int val;
};

class SparseMartix{
public:
	int hang;
	int lie;
	int feiling;
	vector<SparseMartixTriple> SM;
	SparseMartix(int h,int l){
		hang=h;
		lie=l;
		feiling=0;
	}
	
	void Print(){
		int **martix=new int*[hang];
		for(int i=0;i<hang;i++){
			martix[i]=new int[lie];
			for(int j=0;j<lie;j++){
				martix[i][j]=0;
			}
		}
		for(int i=0;i<feiling;i++){
			martix[SM[i].row][SM[i].col]=SM[i].val;
		}
		for(int i=0;i<hang;i++){
			for(int j=0;j<lie;j++){
				cout<<martix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	void append(SparseMartixTriple t){
		SM.push_back(t);
		feiling++;
	}
};
SparseMartix SparseMartixMutiply(SparseMartix A,SparseMartix B){
	if(A.lie!=B.hang){
		SparseMartix Result(0,0);
		cout<<"Worng"<<endl;
		return Result;
	}
	else{
		SparseMartix Result(A.hang,B.lie);
		for(int i=0;i<A.feiling;i++){
			for(int j=0;j<B.feiling;j++){
				if(B.SM[j].row==A.SM[i].col){
					int value=A.SM[i].val*B.SM[j].val;
					if(value!=0){
						O++;
						SparseMartixTriple temp={A.SM[i].row,B.SM[j].col,value};
						Result.SM.push_back(temp);
						Result.feiling++;
					}
				}
			}
		}
		return Result;
	}
}
int main(){

	SparseMartix A(3, 3);
	SparseMartixTriple t1 = { 0, 0, 2 };
	SparseMartixTriple t2 = { 1, 1, 3 };
	SparseMartixTriple t3 = { 2, 2, 4 };
	A.append(t1);
	A.append(t2);
	A.append(t3);
	A.Print();
	cout<<endl;
	

	SparseMartix B(3, 3);
	SparseMartixTriple t4 = { 0, 1, 5 };
	SparseMartixTriple t5 = { 1, 2, 6 };
	SparseMartixTriple t6 = { 2, 0, 7 };
	B.append(t4);
	B.append(t5);
	B.append(t6);
	B.Print();
	cout<<endl;
	
	SparseMartixMutiply(A, B).Print();
	
	
	return 0;
}
