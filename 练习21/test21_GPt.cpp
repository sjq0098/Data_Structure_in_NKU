#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

// 图类，邻接表表示法
class Graph {
public:
	unordered_map<int, vector<int>> adjList;
	
	// 添加边
	void addEdge(int u, int v) {
		adjList[u].push_back(v);
		adjList[v].push_back(u);  // 无向图
	}
	
	// 广度优先搜索（BFS）算法
	void BFS(int start, int goal) {
		// 队列存储待访问的节点
		queue<int> q;
		// 存储节点的访问状态
		unordered_map<int, bool> visited;
		// 存储路径的前驱节点
		unordered_map<int, int> predecessor;
		
		// 初始化
		q.push(start);
		visited[start] = true;
		predecessor[start] = -1;  // 源点没有前驱节点
		
		// BFS过程
		while (!q.empty()) {
			int current = q.front();
			q.pop();
			
			// 如果找到了目标节点
			if (current == goal) {
				cout << "Path found from " << start << " to " << goal << ": ";
				printPath(predecessor, start, goal);
				return;
			}
			
			// 遍历当前节点的所有邻居
			for (int neighbor : adjList[current]) {
				if (!visited[neighbor]) {
					visited[neighbor] = true;
					predecessor[neighbor] = current;
					q.push(neighbor);
				}
			}
		}
		
		cout << "No path found from " << start << " to " << goal << endl;
	}
	
	// 打印从源点到终点的路径
	void printPath(const unordered_map<int, int>& predecessor, int start, int goal) {
		if (goal == -1) {
			cout << "No path exists" << endl;
			return;
		}
		
		vector<int> path;
		for (int at = goal; at != -1; at = predecessor.at(at)) {
			path.push_back(at);
		}
		
		// 反转路径
		for (int i = path.size() - 1; i >= 0; --i) {
			cout << path[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	Graph g;
	
	// 创建一个简单的图
	// 图的结构：节点 0 - 1 - 2
	//             |   |
	//             3 - 4
	g.addEdge(0, 1);
	g.addEdge(0, 3);
	g.addEdge(1, 2);
	g.addEdge(1, 4);
	g.addEdge(3, 4);
	
	int start = 0;
	int goal = 4;
	
	// 执行BFS从start到goal
	g.BFS(start, goal);
	
	return 0;
}

