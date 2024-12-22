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
int getheight(AVLNode*Node){
	if(!Node){
		return 0;
	}
	else{
		return max(getheight(Node->Left),getheight(Node->Right))+1;
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
// 优化递归计算高度函数，使用缓存
unordered_map<AVLNode*, int> heightCache;
int calculateAVLHeight(AVLNode* node, unordered_map<AVLNode*, int>& heightCache) {
	if (!node) return 0; // 空节点高度为0
	
	// 如果节点高度已缓存，直接返回
	if (heightCache.find(node) != heightCache.end()) {
		return heightCache[node];
	}
	
	// 递归计算左右子树的高度
	int leftHeight = calculateAVLHeight(node->Left, heightCache);
	int rightHeight = calculateAVLHeight(node->Right, heightCache);
	
	// 当前节点的高度为左右子树高度的最大值 + 1
	int height = max(leftHeight, rightHeight) + 1;
	
	// 缓存当前节点的高度
	heightCache[node] = height;
	O++;
	return height;
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
};
int main(){
	AVL_Tree AVL;
	// 插入节点构建以下AVL树：
	/*
		   50
	    /     \
	   30       70
	  /  \      /   \
	20   40    60    85
	/ \   / \  /  \  /  \
   10 25 35 45 55 65 80  90
         /           
         34        
	
	
	*/
   AVL.Insert(50);AVL.Insert(30);AVL.Insert(70);AVL.Insert(20);
	AVL.Insert(40);AVL.Insert(60);AVL.Insert(85);AVL.Insert(10);
	AVL.Insert(25);AVL.Insert(35);AVL.Insert(45);AVL.Insert(55);
	AVL.Insert(65);AVL.Insert(80);AVL.Insert(90);//AVL.Insert(34);
	cout << "树的高度: " << getheight(AVL.Root) << endl;
	AVL.preOrderPrint(AVL.Root);
	cout << endl << "getheight1的高度: " << calculateAVLHeight(AVL.Root, heightCache) << " 操作数O: " << O << endl;
	return 0;
}

	

