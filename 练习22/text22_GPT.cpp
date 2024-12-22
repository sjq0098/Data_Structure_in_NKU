#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 图的邻接表表示
typedef vector<vector<int>> AdjList;

// 计算传递闭包的函数
vector<vector<int>> transitiveClosureBFS(const AdjList &graph) {
	int n = graph.size();
	vector<vector<int>> closure(n, vector<int>(n, 0));
	
	// 对于每个顶点，执行 BFS 并标记可到达的顶点
	for (int i = 0; i < n; ++i) {
		vector<bool> visited(n, false);
		queue<int> q;
		
		// 开始 BFS
		q.push(i);
		visited[i] = true;
		
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			closure[i][u] = 1; // 标记 i 可到达 u
			
			for (auto &v : graph[u]) {
				if (!visited[v]) {
					visited[v] = true;
					q.push(v);
				}
			}
		}
	}
	
	return closure;
}

// 辅助函数：打印矩阵
void printMatrix(const vector<vector<int>> &matrix) {
	for (const auto &row : matrix) {
		for (auto val : row) {
			cout << val << " ";
		}
		cout << endl;
	}
}

int main() {
	// 示例图的邻接表表示
	// 例如，图有4个顶点，边为：
	// 0 -> 1, 0 -> 2
	// 1 -> 2
	// 2 -> 0, 2 -> 3
	// 3 -> 3
	AdjList graph = {
		{1, 2},    // 顶点 0 的邻接顶点
		{2},       // 顶点 1 的邻接顶点
		{0, 3},    // 顶点 2 的邻接顶点
		{3}        // 顶点 3 的邻接顶点
	};
	
	cout << "传递闭包矩阵：" << endl;
	vector<vector<int>> closure = transitiveClosureBFS(graph);
	printMatrix(closure);
	
	return 0;
}

