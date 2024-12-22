#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm> 
using namespace std;
class graph {
public:
	unordered_map<int,vector<int>> adjL;
	void addEdge(int u,int v){
		adjL[u].push_back(v);
		adjL[v].push_back(u);
	}
	vector<int> findPathBFS(int Source,int Destination){
		if (adjL.find(Source) == adjL.end() || adjL.find(Destination) == adjL.end()) {
			cout<<"要找的路线不合法";
			return {};
		}
		queue<int>BFSq;
		unordered_map<int, bool> isvisited;      
		unordered_map<int, int> predecessor; 
		isvisited[Source]=true;
		BFSq.push(Source);
		bool isFound=0;
		while(!BFSq.empty()){
			int curr=BFSq.front();
			BFSq.pop();
			for(int neigh:adjL[curr]){
				if(!isvisited[neigh]){
					isvisited[neigh]=1;
					predecessor[neigh]=curr;
					BFSq.push(neigh);
					if(Destination==neigh){
						isFound=1;
						break;
					}
				}	
			}
			if(isFound){
				break;
			}
		}
		if(!isFound){
			return {};
		}
		vector<int>Path;
		for(int at=Destination;at!=Source;at=predecessor[at]){
			Path.push_back(at);
		}
		Path.push_back(Source);
		reverse(Path.begin(),Path.end());
		return Path;
	}
	void printGraph() {
		for (auto& pair : adjL) {
			cout << "Node " << pair.first << ": ";
			for (int neighbor : pair.second) {
				cout << neighbor << " ";
			}
			cout << endl;
		}
	}
};
int main(){
	graph gra;
	gra.addEdge(1,2);
	gra.addEdge(1,3);
	gra.addEdge(2,4);
	gra.addEdge(3,5);
	gra.addEdge(5,6);
	gra.addEdge(4,6);
	gra.addEdge(7,1);
	gra.addEdge(7,2);
	gra.addEdge(7,3);
	gra.addEdge(7,4);
	gra.addEdge(7,5);
	gra.addEdge(7,6);
	gra.printGraph();
	vector<int>path;
	int So,De;
	So=1;
	De=6;
	path=gra.findPathBFS(So,De);
	if(!path.empty()){
		cout<<"from "<<So<<" to "<<De<<" :"<<endl;
		for(auto at:path){
			cout<<at<<" ";
		}
		cout<<endl;
	}
	else{
		cout<<"不存在"<<endl;
	}
	return 0;
	
}
