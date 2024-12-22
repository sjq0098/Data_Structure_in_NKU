#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;
int O=0;
struct AVLNode{
	int val;
	int height;
	AVLNode *Left;
	AVLNode*Right;
	AVLNode(int v){
		val=v;
		Left=Right=nullptr;
		height=1;
	}
};
struct LeafNode{
	int val;
	int depth;
};
int getheight(AVLNode*Node){
	if(!Node){
		return 0;
	}
	else{
		return max(getheight(Node->Left),getheight(Node->Right))+1;
	}
}
int getheight1(AVLNode*Node){
	if(!Node){
		return 0;
	}
	else{
		O++;
		return max(getheight1(Node->Left),getheight1(Node->Right))+1;
	}
}
int getBalanceFactor(AVLNode*Node){
	if(!Node){
		return 0;
	}
	else{
		return getheight(Node->Left)-getheight(Node->Right);
	}
}

AVLNode* RightRotate(AVLNode*Node){
	AVLNode* LL=Node->Left;
	AVLNode* LR=LL->Right;
	LL->Right=Node;
	Node->Left=LR;
	Node->height=getheight(Node);
	LL->height=getheight(LL);
	Node->height=max(getheight(Node->Left),getheight(Node->Right))+1;
	LL->height=max(getheight(LL->Left),getheight(LL->Right))+1;
	return LL;
}

AVLNode* LeftRotate(AVLNode*Node){
	AVLNode* RR=Node->Right;
	AVLNode* RL=RR->Left;
	RR->Left=Node;
	Node->Right=RL;
	Node->height=getheight(Node);
	RR->height=getheight(RR);
	Node->height=max(getheight(Node->Left),getheight(Node->Right))+1;
	RR->height=max(getheight(RR->Left),getheight(RR->Right))+1;
	return RR;
}

class AVL_Tree {
public:
	AVLNode*Root=nullptr;
	AVLNode* Insert_Helper(AVLNode* node, int data) {
		if (node == nullptr)
			return new AVLNode(data);
		
		if (data < node->val)
			node->Left = Insert_Helper(node->Left, data);
		else if (data > node->val)
			node->Right = Insert_Helper(node->Right, data);
		else 
			return node;
		
		node->height =  max(getheight(node->Left), getheight(node->Right))+1;
		int balance = getBalanceFactor(node);
		
		
		if (balance > 1 && data < node->Left->val)
			return RightRotate(node);
		if (balance < -1 && data > node->Right->val)
			return LeftRotate(node);
		if (balance > 1 && data > node->Left->val) {
			node->Left = LeftRotate(node->Left);
			return RightRotate(node);
		}
		if (balance < -1 && data < node->Right->val) {
			node->Right = RightRotate(node->Right);
			return LeftRotate(node);
		}
		return node;
	}
	
	void Insert(int data){
		Root=Insert_Helper(Root,data);
	}
	
	void preOrderPrint(AVLNode* Root){
		if(!Root){
			return;
		}
		preOrderPrint(Root->Left);
		cout<<Root->val<<"<"<<Root->height<<">"<<" ";
		preOrderPrint(Root->Right);
	}
	
	LeafNode GetNearestLeaf_Helper(AVLNode* Node,int CurrentDepth){
		if(!Node){
			LeafNode Result;
			Result.val=-998244353;
			Result.depth=INT32_MAX;
			return Result;
		}
		if(!Node->Left&&!Node->Right){
			LeafNode Result;
			Result.val=Node->val;
			Result.depth=CurrentDepth;
			return Result;
		}
		LeafNode LeftLeafNode=GetNearestLeaf_Helper(Node->Left,CurrentDepth+1);
		LeafNode RightLeafNode=GetNearestLeaf_Helper(Node->Right,CurrentDepth+1);
		if(LeftLeafNode.depth<=RightLeafNode.depth){
			return LeftLeafNode;
		}
		else{
			return RightLeafNode;
		}
	}
	void getClosestLeafNode() {
		if (!Root) {
			cout<<"树为空"<<endl;
			return;
		}
		LeafNode result = GetNearestLeaf_Helper(Root, 1); // 根节点深度为1
		if (result.val == -998244353) {
			cout<<"无叶节点"<<endl;
		}
		else{
			cout<<result.val<<endl;
		}
	}
	
};
int main(){
	AVL_Tree AVL;
	AVL.Insert(30);
	AVL.Insert(20);
	AVL.Insert(40);
	AVL.Insert(10);
	AVL.Insert(25);
	AVL.Insert(50);
	AVL.Insert(5);
	AVL.Insert(2);
	/* 插入节点构建以下AVL树：
	30
	/   \
	20     40
	/  \     \
	5   25    50	
	/ \
	2  10
	*/
	AVL.getClosestLeafNode();
	return 0;
}
