#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;

class bsTree {
public:
	virtual void ascend() = 0; // 按键值升序输出
	virtual bool find(int x)= 0;
	virtual void Insert(int x) = 0;
	virtual void Delete(int x) = 0;
};

struct RedBlackTreeNode{
	int data;
	RedBlackTreeNode*Left;
	RedBlackTreeNode*Right;
	RedBlackTreeNode*Parent;
	int num;//计数器
	bool Color;//红色为1，黑色为0
	RedBlackTreeNode(const int&d){
		data=d;
		Left=Right=Parent=nullptr;
		Color=1;
		num=1;
	}
	RedBlackTreeNode(){
		Left=Right=Parent=nullptr;
		num=0;
	}
};

class RedBlackTree:public bsTree {
public:
	RedBlackTreeNode* Root;
	RedBlackTreeNode*Leaf;//代指NULL
	
	
	
	void LeftRotate(RedBlackTreeNode*x){
		RedBlackTreeNode* y=x->Right;
		x->Right=y->Left;
		if(y->Left!=Leaf){
			y->Left->Parent=x;
		}
		y->Parent=x->Parent;
		if (x->Parent == Leaf){
			Root = y;
		}
		else if (x == x->Parent->Left){
			x->Parent->Left = y;
		}
		else{
			x->Parent->Right = y;
		}
		y->Left = x;
		x->Parent = y;	
	}
	
	void RightRotate(RedBlackTreeNode*x){
		RedBlackTreeNode* y=x->Left;
		x->Left=y->Right;
		if(y->Right!=Leaf){
			y->Right->Parent=x;
		}
		y->Parent=x->Parent;
		if (x->Parent == Leaf){
			Root = y;
		}
		else if (x == x->Parent->Left){
			x->Parent->Left = y;
		}
		else{
			x->Parent->Right = y;
		}
		y->Right = x;
		x->Parent = y;	
	}
	
	void InsertFix(RedBlackTreeNode*z){
		while(z->Parent->Color){
			if(z->Parent==z->Parent->Parent->Left){
				RedBlackTreeNode*y=z->Parent->Parent->Right;
				//叔叔节点为红色
				if(y->Color){
					z->Parent->Parent->Color=1;
					z->Parent->Color=0;
					y->Color=0;
					z=z->Parent->Parent;
				}
				else{//叔叔节点为黑色
					if(z==z->Parent->Right){//先左旋，后右旋
						z=z->Parent;
						LeftRotate(z);
					}
					z->Parent->Color = 0;
					z->Parent->Parent->Color = 1;
					RightRotate(z->Parent->Parent);
				}
			}
			else{
				RedBlackTreeNode*y=z->Parent->Parent->Left;
				//叔叔节点为红色
				if(y->Color){
					z->Parent->Parent->Color=1;
					z->Parent->Color=0;
					y->Color=0;
					z=z->Parent->Parent;
				}
				else{//叔叔节点为黑色
					if(z==z->Parent->Left){//先右旋，后左旋
						z=z->Parent;
						RightRotate(z);
					}
					z->Parent->Color = 0;
					z->Parent->Parent->Color = 1;
					LeftRotate(z->Parent->Parent);
				}
			}
		}
		Root->Color=0;
	}
	
	
	void DeleteFix(RedBlackTreeNode*x){
		while(x!=Root&&!x->Color){
			if(x==x->Parent->Left){
				RedBlackTreeNode*w=x->Parent->Right;
				if(w->Color){
					w->Color=0;
					x->Parent->Color=1;
					LeftRotate(x->Parent);
					w=x->Parent->Right;
				}
				if (!w->Left->Color&&! w->Right->Color) {
					w->Color = 1;
					x = x->Parent;
				}
				else{
					if (!w->Right->Color) {
						w->Left->Color = 0;
						w->Color = 1;
						RightRotate(w);
						w = x->Parent->Right;
					}
					w->Color = x->Parent->Color;
					x->Parent->Color = 0;
					w->Right->Color = 0;
					LeftRotate(x->Parent);
					x = Root;
				}	
			}
			else {
				RedBlackTreeNode* w = x->Parent->Left;
				if (w->Color ) {
					w->Color = 0;
					x->Parent->Color = 1;
					RightRotate(x->Parent);
					w = x->Parent->Left;
				}
				if (!w->Right->Color && !w->Left->Color) {
					w->Color = 1;
					x = x->Parent;
				} else {
					if (!w->Left->Color) {
						w->Right->Color = 0;
						w->Color = 1;
						LeftRotate(w);
						w = x->Parent->Left;
					}
					w->Color = x->Parent->Color;
					x->Parent->Color = 0;
					w->Left->Color = 0;
					RightRotate(x->Parent);
					x = Root;
				}
			}
		}
		x->Color = 0;
	}
	
	
	RedBlackTree(){
		Leaf =new RedBlackTreeNode();
		Leaf->Color=0;
		Root=Leaf;
		Leaf->Left = Leaf->Right = Leaf->Parent = Leaf;
	}
	
	
	void Insert(int data)override{
		if(!find(data)){
			RedBlackTreeNode* z=new RedBlackTreeNode(data);
			z->Left = z->Right = z->Parent = Leaf;
			
			RedBlackTreeNode* y = Leaf;
			RedBlackTreeNode* x = Root;
			
			// 标准BST插入
			while (x != Leaf) {
				y = x;
				if (z->data < x->data)
					x = x->Left;
				else
					x = x->Right;
			}
			
			z->Parent = y;
			if (y == Leaf)
				Root = z;
			else if (z->data < y->data)
				y->Left = z;
			else
				y->Right = z;
			
			z->Color = 1; // 新插入的节点为红色
			
			InsertFix(z);
		}
		else{
			RedBlackTreeNode* z=Search_Helper(Root,data);
			if(z!=Leaf){
				z->num++;
			}
			else{
				cout<<"不存在这个结点"<<endl;
				return;
			}	
		}
		
	}
	
	RedBlackTreeNode* Search_Helper(RedBlackTreeNode*Node,int x){
		if(Node==Leaf||Node->data==x){
			return Node;
		}
		else{
			if(x<Node->data){
				return Search_Helper(Node->Left,x);
			}
			else{
				return Search_Helper(Node->Right,x);
			}
		}
	}
	
	bool find(int data)override {
		RedBlackTreeNode*res=Search_Helper(Root,data);
		return(res!=Leaf);
	}
	
	RedBlackTreeNode* MinNode(RedBlackTreeNode* Node){
		RedBlackTreeNode* Curr = Root;
		while(Curr->Left != Leaf){
			Curr = Curr->Left;
		}
		return Curr;
	}
	
	
	void Transplant(RedBlackTreeNode* u, RedBlackTreeNode* v) {
		if (u->Parent == Leaf)
			Root = v;
		else if (u == u->Parent->Left)
			u->Parent->Left = v;
		else
			u->Parent->Right = v;
		v->Parent= u->Parent;
	}
	
	void Delete(int x)override{
		if(find(x)){
			RedBlackTreeNode* z=Search_Helper(Root,x);
			if(z!=Leaf){
				if(z->num>1){
					z->num--;
				}
				else{
					Delete_Helper(z);
				}
			}
			else{
				cout<<"不存在这个结点"<<endl;
				return;
			}	
		}
		else{
			cout<<"不存在这个结点"<<endl;
			return;
		}	
	}
	
	void Delete_Helper(RedBlackTreeNode* z) {
		RedBlackTreeNode* y = z;
		RedBlackTreeNode* x;
		bool y_original_color = y->Color;
		if (z->Left == Leaf) {
			x = z->Right;
			Transplant(z, z->Right);
		}
		else if (z->Right == Leaf) {
			x = z->Left;
			Transplant(z, z->Left);
		}
		else {
			y = MinNode(z->Right);
			y_original_color = y->Color;
			x = y->Right;
			if (y->Parent == z)
				x->Parent = y;
			else {
				Transplant(y, y->Right);
				y->Right = z->Right;
				y->Right->Parent = y;
			}
			Transplant(z, y);
			y->Left = z->Left;
			y->Left->Parent = y;
			y->Color = z->Color;
		}
		delete z;
		if (y_original_color == false)
			DeleteFix(x);
	}
	
	void ascend()override{
		InoderPre(Root);
		cout<<endl;
	}
	
	void InoderPre(RedBlackTreeNode*Node){
		if(Node!=Leaf){
			InoderPre(Node->Left);
			for(int i=0;i<Node->num;i++){
				cout<<Node->data<<" ";
			}
			InoderPre(Node->Right);
		}
	}
};
int main(){
	RedBlackTree tree;
	int keys[] = {10, 20, 20, 30, 10, 10, 40};
	for(auto key : keys){
		tree.Insert(key);
	}
	int value;
	cout << "红黑树的升序输出: ";
	tree.ascend();
	// 测试查找
	cout << "请输入要查找的值: ";
	cin >> value;
	if(tree.find(value))
		cout << "找到值 " << value << " 在树中.\n";
	else
		cout << "未找到值 " << value << " 在树中.\n";
	
	// 测试删除
	cout << "请输入要删除的值: ";
	cin >> value;
	tree.Delete(value);
	cout << "删除后红黑树的升序输出: ";
	tree.ascend();
	return 0;
}


