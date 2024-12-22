#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm> 
using namespace std;
int O=0;
class graph {
public:
	int num;
	vector<vector<int>>adjM;
	graph(int n) {
		num = n;
		adjM = vector<vector<int>>(n, vector<int>(n, 0));
	}
	void addEdge(int i,int j){
		adjM[i][j]=adjM[j][i]=1;
	}
	vector<vector<int>> tcClosure(){
		vector<vector<int>>closure=adjM;
		for(int i=0;i<num;i++){
			closure[i][i]=1;
			vector<bool>isvisited(num,0);
			queue<int> q;
			q.push(i);
			isvisited[i]=1;
			while(!q.empty()){
				int curr=q.front();
				q.pop();
				for(int j=0;j<num;j++){
					if(adjM[curr][j]&&!isvisited[j]){
						isvisited[j] = true;
						closure[i][j] = 1;
						O++;
						q.push(j);
					}
				}
			}
		}
		return closure;
	}
};
void printMatrix(const vector<vector<int>> &matrix) {
	int n = matrix.size();
	cout << "    ";
	for(int j = 1; j <= n; ++j){
		cout << j << " ";
	}
	cout << endl;
	cout << "   ";
	for(int j = 0; j < n; ++j){
		cout << "--";
	}
	cout << endl;
	for(int i = 1; i <= n; ++i){
		cout << i << " | ";
		for(int j = 0; j < n; ++j){
			cout << matrix[i-1][j] << " ";
		}
		cout << endl;
	}
}
int main(){

	graph g(7);

	for(int i=0;i<5;i++){
		for(int j=i+1;j<5;j++){
			g.addEdge(i,j);
		}
	}

	cout << "邻接矩阵：" << endl;
	printMatrix(g.adjM);
	
	// 计算传递闭包
	vector<vector<int>> closure = g.tcClosure();
	
	cout << "\n传递闭包矩阵：" << endl;
	printMatrix(closure);
	cout<<O;
	return 0;
}
