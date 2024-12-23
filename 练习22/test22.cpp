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
	
	
	
	vector<vector<int>> tcClosure() {
		vector<vector<int>> closure(num, vector<int>(num, 0));
		unordered_map<int, bool> componentLabel;
		
		for(int i = 0; i < num; i++){
			if (componentLabel.find(i)!= componentLabel.end() && componentLabel[i]) {
				continue; 
			}
			
			
			vector<bool> isvisited(num, false);
			queue<int> q;
			q.push(i);
			isvisited[i] = true;
			O++;
			while(!q.empty()){
				int curr = q.front();
				q.pop();
				for(int j = 0; j < num; j++){
					if(adjM[curr][j] && !isvisited[j]){
						isvisited[j] = true;
						O++;
						q.push(j);
					}
				}
			}
			
			
			vector<int> component;
			for(int k = 0; k < num; k++) {
				if(isvisited[k]) {
					component.push_back(k);
					componentLabel[k] = true; 
				}
			}
			
			
			for(auto &k : component){
				for(auto &j : component){
					closure[k][j] = 1;
				}
			}
		}
		return closure;
	}
	
};
void printMatrix(const vector<vector<int>> &matrix) {
	int n = matrix.size();
	cout << "    ";
	for(int j = 0; j < n; ++j){
		cout << (j+1) << " ";
	}
	cout << endl;
	cout << "   ";
	for(int j = 0; j < n; ++j){
		cout << "--";
	}
	cout << endl;
	for(int i = 0; i < n; ++i){
		cout << (i+1) << " | ";
		for(int j = 0; j < n; ++j){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
// 定义顶点数量
	int vertices = 4;
	graph g(vertices);

	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);
	
	cout << "邻接矩阵：" << endl;
	printMatrix(g.adjM);
	
	// 计算传递闭包
	vector<vector<int>> closure = g.tcClosure();
	
	cout << "\n传递闭包矩阵：" << endl;
	printMatrix(closure);
	cout<<O;
	return 0;
}
