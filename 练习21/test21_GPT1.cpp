#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <cstring>

using namespace std;

// BFS版本路径搜索
int* findPathBFS(int theSource, int theDestination, int n, vector<vector<int>>& adjList) {
	// 辅助数组
	int* path = new int[n + 1];  // 存储路径
	int* visited = new int[n + 1];  // 标记是否访问过
	int* predecessor = new int[n + 1];  // 记录每个节点的前驱
	memset(visited, 0, sizeof(int) * (n + 1));
	memset(predecessor, -1, sizeof(int) * (n + 1));
	
	queue<int> q;  // 队列，用于BFS
	q.push(theSource);
	visited[theSource] = 1;
	
	bool found = false;
	
	// BFS搜索
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		
		// 遍历当前节点的所有邻接节点
		for (int neighbor : adjList[current]) {
			if (!visited[neighbor]) {
				visited[neighbor] = 1;
				predecessor[neighbor] = current;  // 记录路径中的前驱节点
				q.push(neighbor);
				
				// 如果找到目标节点，停止搜索
				if (neighbor == theDestination) {
					found = true;
					break;
				}
			}
		}
		if (found) break;
	}
	
	// 如果没有找到路径，返回NULL
	if (!found) {
		delete[] path;
		delete[] visited;
		delete[] predecessor;
		return NULL;
	}
	
	// 反向回溯路径
	int length = 0;
	for (int at = theDestination; at != -1; at = predecessor[at]) {
		path[++length] = at;
	}
	path[0] = length - 1;  // 路径长度
	
	// 反转路径
	for (int i = 1; i <= length / 2; ++i) {
		swap(path[i], path[length - i + 1]);
	}
	
	delete[] visited;
	delete[] predecessor;
	return path;
}

int main() {
	int n = 5;  // 节点数
	vector<vector<int>> adjList(n + 1);  // 邻接表
	
	// 添加边
	adjList[1] = {2, 3};
	adjList[2] = {1, 4};
	adjList[3] = {1, 5};
	adjList[4] = {2};
	adjList[5] = {3};
	
	int theSource = 1, theDestination = 4;
	
	// 寻找路径
	int* path = findPathBFS(theSource, theDestination, n, adjList);
	
	// 输出路径
	if (path) {
		cout << "Path found: ";
		for (int i = 1; i <= path[0]; ++i) {
			cout << path[i] << " ";
		}
		cout << endl;
		delete[] path;
	} else {
		cout << "No path found!" << endl;
	}
	
	return 0;
}

