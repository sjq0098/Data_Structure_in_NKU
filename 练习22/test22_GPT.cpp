#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// 图的定义
class graph {
public:
	unordered_map<int, vector<int>> adjL; // 邻接表
	
	// 添加边（无向图）
	void addEdge(int u, int v){
		adjL[u].push_back(v);
		adjL[v].push_back(u);
	}
};

// 计算传递闭包的函数，使用 BFS 和构件标记策略
vector<vector<int>> transitiveClosureBFS(const graph &g, const vector<int> &vertices) {
	int n = vertices.size();
	vector<vector<int>> closure(n, vector<int>(n, 0));
	
	// 对于每个顶点，执行 BFS 并标记可到达的顶点
	for(int i = 0; i < n; ++i){
		// 初始化访问标记
		vector<bool> visited(n, false);
		queue<int> q;
		
		// 当前顶点
		int current = vertices[i];
		q.push(current);
		visited[i] = true; // 标记自己为已访问
		
		while(!q.empty()){
			int u = q.front();
			q.pop();
			
			// 找到 u 在 vertices 中的索引
			auto it = find(vertices.begin(), vertices.end(), u);
			if(it == vertices.end()){
				continue; // 如果顶点不存在于列表中，跳过
			}
			int u_index = distance(vertices.begin(), it);
			
			// 标记传递闭包
			closure[i][u_index] = 1;
			
			// 遍历所有邻接顶点
			for(auto &v : g.adjL.at(u)){
				// 找到 v 在 vertices 中的索引
				auto it_v = find(vertices.begin(), vertices.end(), v);
				if(it_v == vertices.end()){
					continue;
				}
				int v_index = distance(vertices.begin(), it_v);
				
				if(!visited[v_index]){
					visited[v_index] = true;
					q.push(v);
				}
			}
		}
	}
	
	return closure;
}

// 辅助函数：打印矩阵
void printMatrix(const vector<vector<int>> &matrix, const vector<int> &vertices) {
	int n = vertices.size();
	// 打印表头
	cout << "    ";
	for(auto &v : vertices){
		cout << v << " ";
	}
	cout << endl;
	cout << "   ";
	for(int i = 0; i < n; ++i){
		cout << "--";
	}
	cout << endl;
	// 打印每一行
	for(int i = 0; i < n; ++i){
		cout << vertices[i] << " | ";
		for(int j = 0; j < n; ++j){
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	// 创建图的实例
	graph g;
	
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 3); // 自环
	
	// 提取所有顶点
	vector<int> vertices;
	for(auto &pair : g.adjL){
		vertices.push_back(pair.first);
	}
	// 去除重复顶点并排序
	sort(vertices.begin(), vertices.end());
	vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());
	
	cout << "图的邻接表：" << endl;
	for(auto &u : vertices){
		cout << u << ": ";
		for(auto &v : g.adjL[u]){
			cout << v << " ";
		}
		cout << endl;
	}
	
	// 计算传递闭包
	vector<vector<int>> closure = transitiveClosureBFS(g, vertices);
	
	cout << "\n传递闭包矩阵：" << endl;
	printMatrix(closure, vertices);
	
	return 0;
}

