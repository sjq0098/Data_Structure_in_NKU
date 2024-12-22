#include<iostream>
#include<fstream>
using namespace std;
double O=0;
template<typename T>
class upperTriangularMatrix;

template<typename T>
class lowerTriangularMatrix {
	int n;
	T*LM;
public:
	lowerTriangularMatrix(int sz) {
		n=sz;
		LM=new T[n*(n+1)/2];
		for(int i=0;i<n*(n+1)/2;i++){
			LM[i]=i+1;
		}
	}
	~lowerTriangularMatrix(){
		delete[] LM;
	}
	lowerTriangularMatrix<T> LMstore(int i,int j,int x){
		LM[((i-1)*(i-1)+(i-1))/2+j-1]=x;
		return *this;
	}
	void output(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				cout<<LM[((i-1)*(i-1)+(i-1))/2+j-1]<<" ";
			}
			for(int j=1;j<=n-i;j++){
				cout<<0<<" ";
			}
			cout<<endl;
		}
		return;
	}
	void Tran(){
		upperTriangularMatrix<T> um(n);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				um.UMstore(j,i,LM[((i-1)*(i-1)+(i-1))/2+j-1]);
				O++;
			}
		}
		cout<<endl;
		cout<<O<<endl;
		um.output();
	}
};
template<typename T>
class upperTriangularMatrix {
public:
	int n;
	T*UM;
public:
	upperTriangularMatrix(int sz) {
		n=sz;
		UM=new T[n*(n+1)/2];
		for(int i=0;i<n*(n+1)/2;i++){
			UM[i]=i+1;
		}
	}
	~upperTriangularMatrix(){
		delete[] UM;
	}
	void UMstore(int i,int j,int x){
		UM[((j-1)*(j-1)+(j-1))/2+i-1]=x;
	}
	void UMstore1(int j,int i,int x){
		UM[((j-1)*(j-1)+(j-1))/2+i-1]=x;
	}
	void output(){
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (j >= i) {
					cout << UM[(j * (j - 1) / 2) + i - 1] << " ";
				} else {
					cout << 0 << " ";
				}
			}
			cout << endl;
		}
		return;
	}
	T* Tran(){
		
	}
	void Print(int i,int j){
		cout<<UM[n*(n+1)/2-((n-i+1)*(n-i+1)+(n-i+1))/2+j-i]<<endl;		
	}
};
int main(){
	lowerTriangularMatrix<int>L(4);
	L.output();
	L.Tran();
	cout<<endl;
	upperTriangularMatrix<int>U(4);
	int a=1;
	for(int i=1;i<=4;i++){
		for(int j=i;j<=4;j++){
			U.UMstore(i,j,a);
			a++;
		}
	}
	U.output();
	return 0;
}
