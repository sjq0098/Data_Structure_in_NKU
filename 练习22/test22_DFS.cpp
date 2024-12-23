#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int O = 0;

class Graph {
public:
	int num;
	vector<vector<int>> adjM;
	Graph(int n) {
		num = n;
		adjM = vector<vector<int>>(n, vector<int>(n, 0));
	}
	void addEdge(int i, int j){
		adjM[i][j] =adjM[j][i]= 1;
	}
	
	// Tarjan算法找强连通分量
	void tarjans(int u, int disc[], int low[], stack<int> &st, bool stackMember[], vector<vector<int>> &scc) {
		static int time_ = 0;
		disc[u] = low[u] = ++time_;
		st.push(u);
		stackMember[u] = true;
		
		for(int v = 0; v < num; v++) {
			if(adjM[u][v]) {
				if(disc[v] == -1) {
					tarjans(v, disc, low, st, stackMember, scc);
					low[u] = min(low[u], low[v]);
				}
				else if(stackMember[v]) {
					low[u] = min(low[u], disc[v]);
				}
			}
		}
		
		if(low[u] == disc[u]) {
			vector<int> component;
			while(st.top() != u) {
				int w = st.top();
				component.push_back(w);
				stackMember[w] = false;
				st.pop();
			}
			component.push_back(u);
			stackMember[u] = false;
			st.pop();
			scc.push_back(component);
		}
	}
	
	vector<vector<int>> getSCC() {
		int disc[num];
		int low[num];
		bool stackMember[num];
		stack<int> st;
		vector<vector<int>> scc;
		
		fill(disc, disc + num, -1);
		fill(low, low + num, -1);
		fill(stackMember, stackMember + num, false);
		
		for(int i = 0; i < num; i++) {
			if(disc[i] == -1)
				tarjans(i, disc, low, st, stackMember, scc);
		}
		return scc;
	}
	
	// 计算传递闭包
	vector<vector<int>> tcClosure() {
		vector<vector<int>> closure(num, vector<int>(num, 0));
		vector<vector<int>> scc = getSCC();
		
		// 初始化闭包，节点到自身可达
		for(int i = 0; i < num; i++) {
			closure[i][i] = 1;
			O++;
		}
		
		// 对于每个强连通分量，内部任意两点可达
		for(auto &component : scc){
			for(auto u : component){
				for(auto v : component){
					if(u != v && !closure[u][v]){
						closure[u][v] = 1;
						O++;
					}
				}
			}
		}
		
		// 构建分量图
		int scc_num = scc.size();
		vector<vector<int>> scc_adj(scc_num, vector<int>(scc_num, 0));
		// 映射每个节点到其所属的分量
		vector<int> node_to_scc(num);
		for(int i = 0; i < scc_num; i++) {
			for(auto node : scc[i]){
				node_to_scc[node] = i;
			}
		}
		// 构建分量图
		for(int u = 0; u < num; u++) {
			for(int v = 0; v < num; v++) {
				if(adjM[u][v]){
					int scc_u = node_to_scc[u];
					int scc_v = node_to_scc[v];
					if(scc_u != scc_v){
						scc_adj[scc_u][scc_v] = 1;
						O++;
					}
				}
			}
		}
		
		// 计算分量图的传递闭包（使用动态规划）
		for(int k = 0; k < scc_num; k++) {
			for(int i = 0; i < scc_num; i++) {
				for(int j = 0; j < scc_num; j++) {
					if(scc_adj[i][k] && scc_adj[k][j]){
						if(!scc_adj[i][j]){
							scc_adj[i][j] = 1;
							O++;
						}
					}
				}
			}
		}
		
		// 将分量图的闭包结果映射回原图
		for(int i = 0; i < scc_num; i++) {
			for(int j = 0; j < scc_num; j++) {
				if(scc_adj[i][j]){
					for(auto u : scc[i]){
						for(auto v : scc[j]){
							if(!closure[u][v]){
								closure[u][v] = 1;
								O++;
							}
						}
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
	Graph g(vertices);
	
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
	cout << "\n操作次数 O = " << O << endl;
	
	return 0;
}


