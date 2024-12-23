#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 图的定义（邻接矩阵表示）
class Graph {
public:
	int numVertices; // 顶点数量
	vector<vector<int>> adjMatrix; // 邻接矩阵
	
	// 构造函数
	Graph(int n) : numVertices(n), adjMatrix(n, vector<int>(n, 0)) {}
	
	// 添加无向边
	void addEdge(int i, int j){
		if(i >= 0 && i < numVertices && j >=0 && j < numVertices){
			adjMatrix[i][j] = adjMatrix[j][i] = 1;
		}
		else{
			cout << "Invalid edge (" << i << ", " << j << ")\n";
		}
	}
	
	// 计算传递闭包，返回传递闭包矩阵及操作数
	pair<vector<vector<int>>, int> tcClosure(){
		// 初始化传递闭包矩阵为全0
		vector<vector<int>> closure(numVertices, vector<int>(numVertices, 0));
		int O = 0; // 操作数统计
		
		for(int i = 0; i < numVertices; i++){
			// 每个顶点至少能到达自己
			closure[i][i] = 1;
			O++; // closure[i][i] 的赋值操作
			
			// 初始化访问标记
			vector<bool> isVisited(numVertices, false);
			queue<int> q;
			
			// 开始 BFS
			q.push(i);
			isVisited[i] = true;
			
			while(!q.empty()){
				int curr = q.front();
				q.pop();
				
				for(int j = 0; j < numVertices; j++){
					if(adjMatrix[curr][j] && !isVisited[j]){
						isVisited[j] = true;
						closure[i][j] = 1;
						O++; // closure[i][j] 的赋值操作
						q.push(j);
					}
				}
			}
		}
		return make_pair(closure, O);
	}
};

// 辅助函数：打印矩阵
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
	// 定义顶点数量
	int vertices = 4;
	Graph g(vertices);
	
	// 添加边（示例图）
	// 例如，图有4个顶点，边为：
	// 0 - 1, 0 - 2
	// 1 - 2
	// 2 - 0, 2 - 3
	// 3 - 3 (自环)
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3); // 自环
	
	// 打印邻接矩阵
	cout << "邻接矩阵：" << endl;
	printMatrix(g.adjMatrix);
	
	// 计算传递闭包
	pair<vector<vector<int>>, int> result = g.tcClosure();
	vector<vector<int>> closure = result.first;
	int O = result.second;
	
	// 打印传递闭包矩阵
	cout << "\n传递闭包矩阵：" << endl;
	printMatrix(closure);
	
	// 打印操作数
	cout << "\n操作数 O: " << O << endl;
	
	return 0;
}

