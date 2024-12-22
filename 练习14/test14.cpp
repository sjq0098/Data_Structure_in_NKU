#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;
struct TreeNode{
	int val;
	TreeNode* Right;
	TreeNode*Left;
	TreeNode(int v):val(v),Right(nullptr),Left(nullptr){};
};

class BinaryTree {
public:
	TreeNode*Root;
	
	TreeNode* Insert_Helper(TreeNode*Node,int data){
		if(Node==nullptr){
			return new TreeNode(data);
		}
		if(data<Node->val){
			Node->Left=Insert_Helper(Node->Left,data);
		}
		else if(data>Node->val){
			Node->Right=Insert_Helper(Node->Right,data);
		}
		return Node;
	}
	
	void insert(int data){
		Root=Insert_Helper(Root,data);
	}
	
	BinaryTree():Root(nullptr){};
	
	TreeNode* Mirro_Helper(TreeNode*Node){
		if(Node==nullptr){
			return nullptr;
		}
		
		TreeNode* Temp;
		Temp=Node->Left;
		Node->Left=Node->Right;
		Node->Right=Temp;
		Mirro_Helper(Node->Left);
		Mirro_Helper(Node->Right);
		return Node;
	}
	void Mirro(){
		Mirro_Helper(Root);
	}
	
	void preorderTraversal(TreeNode* node) {
		if (node != nullptr) {
			cout << node->val << " ";  
			preorderTraversal(node->Left);  
			preorderTraversal(node->Right); 
		}
	}
	
	int CountLeafNode(TreeNode*Node){
		if(Node==nullptr){
			return 0;
		}
		else if(Node&&!Node->Left&&!Node->Right){
			return 1;
		}
		return CountLeafNode(Node->Left)+CountLeafNode(Node->Right);
	}
	
	void Level_Order_Travel(){
		if(!Root){
			return;
		}
		queue<TreeNode*>Q;
		Q.push(Root);
		while(!Q.empty()){
			if(Q.front()->Left){
				Q.push(Q.front()->Left);
			}
			if(Q.front()->Right){
				Q.push(Q.front()->Right);
			}
			cout<<Q.front()->val<<" ";
			Q.pop();
		}
		
	}
	
	int Calculate_Width(){
		if(!Root){
			return 0;
		}
		queue<TreeNode*>Q;
		Q.push(Root);
		int levelsize=Q.size();
		int max=levelsize;
		while(!Q.empty()){
			levelsize=Q.size();
			if(max<levelsize){
				max=levelsize;
			}
			for(int i=0;i<levelsize;i++){
				if(Q.front()->Left){
				Q.push(Q.front()->Left);
				}
				if(Q.front()->Right){
				Q.push(Q.front()->Right);
				}
				Q.pop();
			}
		}
		return max;
	}
};


int main(){
	BinaryTree tree;
	
	// 插入节点
	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	tree.insert(10);
	
	
	cout<<tree.CountLeafNode(tree.Root)<<endl;
	
	tree.preorderTraversal(tree.Root);
	cout<<endl;
	
	tree.Level_Order_Travel();
	cout<<endl;
	
	cout<<tree.Calculate_Width()<<endl;
	
	tree.Mirro();
	tree.preorderTraversal(tree.Root);
	cout<<endl;
	
	tree.Level_Order_Travel();
	return 0;
}
